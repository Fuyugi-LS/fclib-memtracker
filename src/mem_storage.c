/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_storage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsongsit <nsongsit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:35:52 by nsongsit          #+#    #+#             */
/*   Updated: 2025/11/15 18:02:10 by nsongsit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memtracker.h"
#include "memtracker_utils.h"

/**
 * mem_storage() - Retrieves the singleton instance of the memory tracker.
 *
 * This function manages a static, persistent array (@memory) used as the
 * global storage for the memory tracker.
 *
 * It uses a static flag (@start_state) to ensure that the storage
 * is initialized only once. On the first call, it iterates through
 * the array up to MAX_TRACKER, setting all slots to NULL. On all
 * subsequent calls, it immediately returns the pointer to the
 * already-initialized storage.
 *
 * The array is declared with size MAX_TRACKER + 1 to provide a
 * boundary-safe sentinel value.
 *
 * Return: A pointer to the static t_memory storage array.
 */
t_memory	*mem_storage(void)
{
	static t_memory	memory[MAX_TRACKER + 1];
	static int32_t	start_state;
	int64_t			i;

	if (start_state != 0)
		return (memory);
	i = 0;
	while (i < MAX_TRACKER)
	{
		memory[i] = NULL;
		i++;
	}
	start_state = 1;
	return (memory);
}
