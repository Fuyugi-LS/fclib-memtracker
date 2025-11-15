/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free_partial.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsongsit <nsongsit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:38:46 by nsongsit          #+#    #+#             */
/*   Updated: 2025/11/15 17:58:24 by nsongsit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memtracker.h"
#include "memtracker_utils.h"

/**
 * mem_free() - Finds and frees a specific pointer from the tracker.
 * @memory: The global memory tracker storage array.
 * @addr:   The address of the pointer to find and free.
 *
 * Iterates through the @memory array up to MAX_TRACKER, searching for
 * an exact match for @addr.
 *
 * If a match is found, this function calls free() on the pointer and
 * then sets its slot in the @memory array to NULL. This action prevents
 * the pointer from being freed again by a subsequent call.
 *
 * The function continues searching the entire array even after a match,
 * ensuring that all duplicate entries of @addr (if any) are
 * also freed and nullified.
 *
 * @return: This function returns no value.
 */
static void	mem_free(t_memory *memory, void *addr)
{
	uint64_t	i;

	i = 0;
	while (i < MAX_TRACKER)
	{
		if (memory[i] == addr)
		{
			free(memory[i]);
			memory[i] = NULL;
		}
		i++;
	}
}

/**
 * mem_free_partial() - Frees one or more specific pointers from the tracker.
 * @size: The total number of pointers to be freed.
 * @addr: The first pointer to find and free.
 * @...:  The subsequent (size - 1) pointers to find and free.
 *
 * This function searches the global memory tracker for 'size' number
 * of pointers and frees them. It takes the first pointer as a named
 * argument and the remaining (size - 1) pointers as variadic arguments.
 *
 * It iterates through the variadic list and calls mem_free() for each
 * pointer. The mem_free() helper is responsible for locating the
 * pointer in the tracker, freeing it, and setting its slot to NULL.
 *
 * If @size is 0 or @addr is NULL, the function returns immediately.
 *
 * @return: This function returns no value.
 */
void	mem_free_partial(size_t size, void *addr, ...)
{
	t_memory *const	memory = mem_storage();
	va_list			va_lst;
	uint64_t		i;

	if (size < 1 || !addr)
		return ;
	mem_free(memory, addr);
	if (size < 2)
		return ;
	i = 0;
	va_start(va_lst, addr);
	while (i < size - 1)
	{
		mem_free(memory, va_arg(va_lst, void *));
		i++;
	}
	va_end(va_lst);
}
