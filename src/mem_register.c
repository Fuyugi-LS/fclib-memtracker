/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_register.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsongsit <nsongsit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:37:27 by nsongsit          #+#    #+#             */
/*   Updated: 2025/11/15 18:00:57 by nsongsit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memtracker.h"
#include "memtracker_utils.h"

/**
 * mem_integrity() - Checks the integrity of the tracker's configuration.
 *
 * Verifies that the compile-time constant MAX_TRACKER is set to a
 * usable value. If MAX_TRACKER is less than the minimum
 * requirement (16), this function will call mem_perror() with the
 * TOO_SMALL_MAX_TRACKER flag.
 *
 * This check ensures the tracker has a reasonable minimum capacity
 * to operate.
 *
 * Return: This function returns no value.
 */
static void	mem_integrity(void)
{
	if (MAX_TRACKER < 16)
		mem_perror(TOO_SMALL_MAX_TRACKER);
}

/**
 * mem_assign() - Assigns a pointer to the next available slot in the tracker.
 * @memory: The global memory tracker storage array.
 * @addr:   The pointer to be added to the tracker.
 *
 * Scans the @memory array to find the first NULL (empty) slot,
 * respecting the MAX_TRACKER boundary.
 *
 * If an empty slot is found (last_mem < MAX_TRACKER), @addr is
 * assigned to that slot.
 *
 * If the tracker is full, this function frees @addr and calls
 * mem_perror() with the BUFFER_OVERFLOW flag.
 *
 * @return: This function returns no value.
 */
static void	mem_assign(t_memory	*memory, void *addr)
{
	uint64_t	last_mem;

	last_mem = 0;
	while (memory[last_mem] && last_mem < MAX_TRACKER)
		last_mem++;
	if (last_mem < MAX_TRACKER)
		memory[last_mem] = addr;
	else
	{
		free(addr);
		mem_perror(BUFFER_OVERFLOW);
	}
}

/**
 * mem_register() - Registers one or more pointers to the memory tracker.
 * @size: The total number of pointers to be registered.
 * @addr: The first pointer to register.
 * @...:  The subsequent (size - 1) pointers to register.
 *
 * This function first performs an integrity check of the tracker via
 * mem_integrity(). It then adds 'size' number of pointers to the
 * global memory tracker. It takes the first pointer as a named
 * argument (@addr) and the remaining (size - 1) pointers as
 * variadic arguments.
 *
 * Each pointer is added to the tracker by calling mem_assign().
 *
 * If @size is 0 or @addr is NULL, the function returns immediately.
 *
 * @return: This function returns no value.
 */
void	mem_register(size_t size, void *addr, ...)
{
	t_memory *const	memory = mem_storage();
	va_list			va_lst;
	uint64_t		i;

	mem_integrity();
	if (size < 1 || !addr)
		return ;
	mem_assign(memory, addr);
	if (size < 2)
		return ;
	va_start(va_lst, addr);
	i = 0;
	while (i < size - 1)
	{
		mem_assign((t_memory *)memory, va_arg(va_lst, void *));
		i++;
	}
	va_end(va_lst);
}
