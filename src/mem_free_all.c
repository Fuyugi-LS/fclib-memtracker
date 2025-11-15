/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsongsit <nsongsit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:39:03 by nsongsit          #+#    #+#             */
/*   Updated: 2025/11/15 17:56:43 by nsongsit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memtracker.h"
#include "memtracker_utils.h"

/**
 * mem_register() - Registers one or more pointers to the memory tracker.
 * @size: The total number of pointers to be registered.
 * @addr: The first pointer to register.
 * @...:  The subsequent (size - 1) pointers to register.
 *
 * This function adds 'size' number of pointers to the global memory
 * tracker. It takes the first pointer as a named argument and the
 * remaining (size - 1) pointers as variadic arguments.
 *
 * If the tracker is full and a pointer cannot be added, this
 * function will call mem_perror() with a BUFFER_OVERFLOW error
 * and free the pointer that failed to be assigned.
 *
 * If @size is 0 or @addr is NULL, the function returns immediately.
 *
 * @return: This function returns no value.
 */
void	mem_free_all(void)
{
	t_memory *const	memory = mem_storage();
	uint64_t		i;

	i = 0;
	while (i < MAX_TRACKER)
	{
		if (memory[i])
		{
			free(memory[i]);
			memory[i] = NULL;
		}
		i++;
	}
}
