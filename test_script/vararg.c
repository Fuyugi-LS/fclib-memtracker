/*
 * ===================================================================
 * TEST FILE: main.c (Dynamic Macro Overflow Test)
 * ===================================================================
 * This test uses the MAX_TRACKER value provided at compile time.
 * e.g., cc -Wall -Wextra -Werror -DMAX_TRACKER=5 *.c
 *
 * It focuses *only* on the variadic overflow edge case.
 */

// The *only* header from your project
#include "memtracker.h"

// Standard libraries
#include <stdio.h>
#include <stdlib.h>

// Fake PID
#define PID 80085

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
	void *p_fill;
	void *p_ok;
	void *p_fail;
	int  i;

	printf("==%d== Dynamic Variadic Overflow Test\n", PID);
	printf("==%d== Using compile-time MAX_TRACKER = %d\n", PID, MAX_TRACKER);
	printf("==%d== \n", PID);

	/*
	 * --- Test 1: Setup - Fill buffer to (MAX_TRACKER - 1) ---
	 * We leave exactly ONE slot open.
	 */
	printf("==%d== Test 1: Filling buffer to %d / %d slots...\n", 
		PID, MAX_TRACKER - 1, MAX_TRACKER);
	
	for (i = 0; i < (MAX_TRACKER - 1); i++)
	{
		p_fill = get_ptr(1);
		mem_register(1, p_fill);
		g_total_registered_spec++;
	}
	printf("==%d== ...Test 1 Complete\n", PID);
	printf("==%d== \n", PID);


	/*
	 * --- Test 2: The Edge Case - Trigger Overflow ---
	 * Buffer is at (MAX_TRACKER - 1) / MAX_TRACKER.
	 * We call mem_register(2, p_ok, p_fail).
	 *
	 * Spec:
	 * 1. p_ok registers successfully. (Buffer: MAX_TRACKER / MAX_TRACKER)
	 * 2. p_fail fails to register. mem_perror() is called.
	 */
	printf("==%d== Test 2: Trigger Overflow with mem_register(2, ...)\n", PID);
	printf("==%d== (This should produce one 'BUFFER_OVERFLOW' error)\n", PID);
	
	p_ok = get_ptr(1);
	p_fail = get_ptr(1);
	
	mem_register(2, p_ok, p_fail);
	
	// As innocent users, we assume p_ok succeeded
	g_total_registered_spec += 1; 
	// And we assume p_fail was not registered
	g_leaked_by_test++; 
	
	printf("==%d== ...Test 2 Complete\n", PID);
	printf("==%d== \n", PID);


	/*
	 * --- Final Cleanup ---
	 */
	printf("==%d== Final Cleanup: mem_free_all()\n", PID);
	mem_free_all(); 
	g_total_freed_spec = g_total_registered_spec;
	printf("==%d== ...All tests complete.\n", PID);
	printf("==%d== \n", PID);

	/*
	 * --- Final Summary (Based on SPEC) ---
	 */
	long blocks_in_use_spec = g_total_registered_spec - g_total_freed_spec;
	blocks_in_use_spec += g_leaked_by_test; // Add pointers we *knew* we leaked

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