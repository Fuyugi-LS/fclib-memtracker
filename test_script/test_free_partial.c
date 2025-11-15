/*
 * ===================================================================
 * TEST FILE: main.c (Overflow + Partial Free Test)
 * ===================================================================
 * This test is designed to be compiled with:
 * cc -D MAX_TRACKER=16 *.c
 *
 * It tests the overflow and then verifies mem_free_partial.
 */

// We assume MAX_TRACKER is set to 16 at compile time.
#include "memtracker.h"

// Standard libraries
#include <stdio.h>
#include <stdlib.h>

// Fake PID
#define PID 90001

// --- Global state for this test harness ---
static long g_total_registered_spec = 0; // Pointers *we think* we registered
static long g_total_freed_spec = 0;      // Pointers *we think* we freed
static long long g_total_bytes = 0;
static int g_leaked_by_test = 0; // Pointers *we* assume failed registration

// Helper to get a new pointer
void *get_ptr(size_t size)
{
	void *p = malloc(size);
	if (!p) {
		printf("==%d==  CRITICAL: malloc failed. Exiting.\n", PID);
		exit(1);
	}
	g_total_bytes += size;
	return p;
}


int main(void)
{
	// We MUST hardcode 15 pointers to test mem_free_partial(15, ...)
	void *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8;
	void *p9, *p10, *p11, *p12, *p13, *p14, *p15;
	void *p_ok;

	printf("==%d== Partial Free Overflow Test\n", PID);
	printf("==%d== Using compile-time MAX_TRACKER = %d\n", PID, MAX_TRACKER);
	printf("==%d== \n", PID);

	/*
	 * --- Test 1: Setup - Fill buffer to (MAX_TRACKER - 1) ---
	 * We register 15 pointers.
	 */
	printf("==%d== Test 1: Filling buffer to 15 / 16 slots...\n", PID);
	p1 = get_ptr(1); p2 = get_ptr(1); p3 = get_ptr(1); p4 = get_ptr(1);
	p5 = get_ptr(1); p6 = get_ptr(1); p7 = get_ptr(1); p8 = get_ptr(1);
	p9 = get_ptr(1); p10 = get_ptr(1); p11 = get_ptr(1); p12 = get_ptr(1);
	p13 = get_ptr(1); p14 = get_ptr(1); p15 = get_ptr(1);
	
	mem_register(15, p1, p2, p3, p4, p5, p6, p7, p8, p9,
					p10, p11, p12, p13, p14, p15);
	g_total_registered_spec += 15;
	
	printf("==%d== ...Test 1 Complete\n", PID);
	printf("==%d== \n", PID);


	/*
	 * --- Test 2: The Edge Case - Trigger Overflow ---
	 * Buffer is at 15/16. We call mem_register(2, p_ok, p_fail).
	 * p_ok registers (16/16), p_fail overflows.
	 */
	printf("==%d== Test 2: Trigger Overflow with mem_register(2, ...)\n", PID);
	printf("==%d== (This should produce one 'BUFFER_OVERFLOW' error)\n", PID);
	
	p_ok = get_ptr(1);

	mem_register(1, p_ok);

	g_total_registered_spec += 1;
	
	printf("==%d== ...Test 2 Complete\n", PID);
	printf("==%d== \n", PID);

	/*
	 * --- Test 3: Partial Free ---
	 * We free the *first* 15 pointers, leaving p_ok.
	 */
	printf("==%d== Test 3: Calling mem_free_partial(15, ...)\n", PID);
	mem_free_partial(15, p1, p2, p3, p4, p5, p6, p7, p8, p9,
						 p10, p11, p12, p13, p14, p15);
	g_total_freed_spec += 15;
	printf("==%d== ...Test 3 Complete\n", PID);
	printf("==%d== \n", PID);

	/*
	 * --- Test 4: Final Cleanup ---
	 * Only p_ok should be left. mem_free_all() should free it.
	 */
	printf("==%d== Test 4: Final Cleanup: mem_free_all()\n", PID);
	mem_free_all(); 
	g_total_freed_spec += 1; // We expect p_ok to be freed
	printf("==%d== ...All tests complete.\n", PID);
	printf("==%d== \n", PID);


	/*
	 * --- Final Summary (Based on SPEC) ---
	 */
	long blocks_in_use_spec = g_total_registered_spec - g_total_freed_spec;
	blocks_in_use_spec += g_leaked_by_test; // p_fail

	printf("==%d== HEAP SUMMARY (Based on Spec):\n", PID);
	printf("==%d==    in use at exit: %lld bytes in %ld blocks\n", 
		PID, (long long)g_leaked_by_test, blocks_in_use_spec);
	printf("==%d==  total heap usage: %ld allocs, %ld frees, %lld bytes allocated\n",
		PID, (g_total_registered_spec + g_leaked_by_test), g_total_freed_spec, g_total_bytes);
	printf("==%d== \n", PID);
	
	if (blocks_in_use_spec > 0) {
		printf("==%d== LEAK SUMMARY (Based on Spec):\n", PID);
		printf("==%d==    definitely lost: %d bytes in %d blocks\n", 
			PID, g_leaked_by_test, g_leaked_by_test);
	} else {
		printf("==%d== All heap blocks were freed -- no leaks are possible\n", PID);
	}

	return 0;
}