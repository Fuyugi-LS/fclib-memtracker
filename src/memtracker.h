/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memtracker.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsongsit <nsongsit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:22:10 by nsongsit          #+#    #+#             */
/*   Updated: 2025/11/15 16:46:05 by nsongsit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMTRACKER_H
# define MEMTRACKER_H

# include <unistd.h>

# ifndef MAX_TRACKER
#  define MAX_TRACKER 1024
# endif

void	mem_register(size_t size, void *addr, ...);
void	mem_free_all(void);
void	mem_free_partial(size_t size, void *addr, ...);

#endif
