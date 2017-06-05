/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:39:23 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/05 17:39:55 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MALLOC_H__
# define __MALLOC_H__

# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/resource.h>
# include "../libft/include/ft_printf.h"
# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"

# define TINY 256
# define SMALL 4096
# define TINY_ZONE (((((TINY + sizeof(t_meta_data) - 1) * 100) / getpagesize()) * getpagesize()) + getpagesize())
# define SMALL_ZONE (((((SMALL + sizeof(t_meta_data) - 1) * 100) / getpagesize()) * getpagesize()) + getpagesize())

void	show_alloc_mem();
void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

typedef struct s_mem_starts	t_mem_starts;
typedef struct s_meta_data	t_meta_data;

struct	s_mem_starts
{
	t_meta_data	*tiny;
	t_meta_data *medium;
	t_meta_data *large;
};

struct	s_meta_data
{
	size_t		size;
	char		test;
	int			free;
	t_meta_data	*next;
};

t_mem_starts	g_memory;

# endif
