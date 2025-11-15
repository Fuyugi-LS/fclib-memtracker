/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memtracker_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsongsit <nsongsit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 17:35:05 by nsongsit          #+#    #+#             */
/*   Updated: 2025/11/15 17:35:38 by nsongsit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMTRACKER_UTILS_H
# define MEMTRACKER_UTILS_H

# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef void*	t_memory;

enum e_error_types
{
	BUFFER_OVERFLOW,
	TOO_SMALL_MAX_TRACKER
};

t_memory	*mem_storage(void);
void		mem_perror(enum e_error_types flag);

#endif
