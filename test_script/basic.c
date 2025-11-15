/*
 * ===================================================================
 * TEST FILE: main.c (Valgrind-Style Output)
 * ===================================================================
 * This file only includes memtracker.h and standard libraries.
 * It must be linked against your memtracker implementation.
 * (e.g., gcc main.c memtracker.c -o my_program)
 */

#include "memtracker.h"

// Standard libraries needed for a "user" to run tests
#include <stdio.h>  // For printf
#include <stdlib.h> // For malloc() and free()

// Fake PID for Valgrind-style output
#define PID 21771

int main(void)
{
	// --- Counters for the final summary ---
	long total_registered = 0;
	long total_freed = 0;
	long long total_bytes_registered = 0;
	int leaked_pointers = 0; // Pointers we alloc but fail to register

	void *p;
	void *ptr1;
	void *ptr2;
	int i;

	printf("==%d== Memtracker Test Runner\n", PID);
	printf("==%d== Using MAX_TRACKER = %d\n", PID, MAX_TRACKER);
	printf("==%d== \n", PID);

	/*
	 * 1. Normal allocation
	 */
	printf("==%d== Test 1: Normal Allocation\n", PID);
	ptr1 = malloc(10);
	if (ptr1) {
		printf("==%d==  Registering %p (%d bytes)\n", PID, ptr1, 10);
		mem_register(1, ptr1);
		total_registered++;
		total_bytes_registered += 10;
	}
	ptr2 = malloc(20);
	if (ptr2) {
		printf("==%d==  Registering %p (%d bytes)\n", PID, ptr2, 20);
		mem_register(1, ptr2);
		total_registered++;
		total_bytes_registered += 20;
	}
	printf("==%d== ...Test 1 Complete\n", PID);
	printf("==%d== \n", PID);

	/*
	 * 3. free all (for Test 1)
	 */
	printf("==%d== Test 2: Free All (Cleanup Test 1)\n", PID);
	mem_free_all();
	total_freed += 2; // We registered 2 pointers
	printf("==%d== ...Test 2 Complete\n", PID);
	printf("==%d== \n", PID);


	/*
	 * 2. up to 1024 times allocation
	 */
	printf("==%d== Test 3: 1024 Allocations (Fill Buffer)\n", PID);
	for (i = 0; i < MAX_TRACKER; i++)
	{
		p = malloc(1);
		if (!p) {
			printf("==%d==  MALLOC FAILED at iteration %d\n", PID, i);
			break;
		}
		mem_register(1, p);
		total_registered++;
		total_bytes_registered += 1;
	}
	printf("==%d== ...Test 3 Complete (Registered %d items)\n", PID, i);
	printf("==%d== \n", PID);


	/*
	 * 3. free all (for Test 3)
	 */
	printf("==%d== Test 4: Free All (Cleanup Test 3)\n", PID);
	mem_free_all();
	total_freed += i; // Free all pointers that were successfully alloc/reg
	printf("==%d== ...Test 4 Complete\n", PID);
	printf("==%d== \n", PID);


	/*
	 * 4. up to 1025 times allocation
	 */
	printf("==%d== Test 5: 1025 Allocations (Test Overflow)\n", PID);
	printf("==%d== (This test should produce one 'BUFFER_OVERFLOW' error)\n", PID);
	for (i = 0; i < MAX_TRACKER + 1; i++)
	{
		p = malloc(1);
		if (!p) {
			printf("==%d==  MALLOC FAILED at iteration %d\n", PID, i);
			break;
		}
		
		mem_register(1, p);

		if (i < MAX_TRACKER) {
			total_registered++;
			total_bytes_registered += 1;
		} else {
			printf("==%d==  Leaking pointer %p (untracked)\n", PID, p);
			leaked_pointers++;
		}
	}
	printf("==%d== ...Test 5 Complete\n", PID);
	printf("==%d== \n", PID);


	/*
	 * 3. free all (for Test 5)
	 */
	printf("==%d== Test 6: Free All (Cleanup Test 5)\n", PID);
	mem_free_all();
	total_freed += MAX_TRACKER; // Should free the 1024 it tracked
	printf("==%d== ...Test 6 Complete\n", PID);
	printf("==%d== \n", PID);


	/*
	 * --- Final Summary ---
	 */
	long blocks_in_use = total_registered - total_freed;

	printf("==%d== HEAP SUMMARY:\n", PID);
	printf("==%d==    in use at exit: %lld bytes in %ld blocks\n", 
		PID, (long long)leaked_pointers, blocks_in_use + leaked_pointers);
	printf("==%d==  total heap usage: %ld allocs, %ld frees, %lld bytes allocated\n",
		PID, total_registered, total_freed, total_bytes_registered);
	printf("==%d== \n", PID);
	
	if (leaked_pointers > 0) {
		printf("==%d== LEAK SUMMARY:\n", PID);
		printf("==%d==    definitely lost: %d bytes in %d blocks\n", 
			PID, leaked_pointers, leaked_pointers);
	} else {
		printf("==%d== All heap blocks were freed -- no leaks are possible\n", PID);
	}

	return 0;
}