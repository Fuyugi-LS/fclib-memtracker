/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_perror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsongsit <nsongsit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:38:09 by nsongsit          #+#    #+#             */
/*   Updated: 2025/11/15 17:58:17 by nsongsit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memtracker.h"
#include "memtracker_utils.h"

static void	print_small_max_tracker(void)
{
	write(2, "Errors exist in memory tracker: ", 32);
	write(2, "Too small \"MAX_TRACKER\"\n", 24);
	write(2, "NOTE: The least \"MAX_TRACKER\" acceptable size is: 16\n", 53);
	write(2, "Error ID: 301\n", 14);
	exit(301);
}

static void	print_overflow(void)
{
	write(2, "Errors exist in memory tracker: Buffer Overflow\n", 48);
	write(2, "Error ID: 300\n", 14);
	exit(300);
}

/**
 * mem_perror() - Handles and reports memory tracker errors.
 * @flag: An enum e_error_types specifying the error to report.
 *
 * This function is the central error handler for the memory tracker.
 * It first performs a full cleanup by calling mem_free_all() to
 * free all currently tracked pointers, preventing memory leaks
 * upon error.
 *
 * Based on the @flag provided, it then calls a specific helper
 * function (e.g., print_overflow()) to write the corresponding
 * error message to the output.
 *
 * @return: This function returns no value.
 */
void	mem_perror(enum e_error_types flag)
{
	mem_free_all();
	if (flag == BUFFER_OVERFLOW)
		print_overflow();
	if (flag == TOO_SMALL_MAX_TRACKER)
		print_small_max_tracker();
}
