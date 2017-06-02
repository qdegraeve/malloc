/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:39:23 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/02 11:00:18 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MALLOC_H__
# define __MALLOC_H__

# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/resource.h>

# define TINY
# define SMALL
# define LARGE

void	show_alloc_mem();
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

# endif
