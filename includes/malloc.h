/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:39:23 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/07 12:55:19 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MALLOC_H__
# define __MALLOC_H__

# include <stdio.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/resource.h>
# include "../libft/include/ft_printf.h"
# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"

# define TINY 256
# define SMALL 4096
# define META_SIZE sizeof(t_meta)
# define FLAG_PROT (PROT_READ | PROT_WRITE)
# define FLAG_MAP (MAP_ANON | MAP_PRIVATE)

typedef struct s_memory	t_memory;
typedef struct s_meta	t_meta;
typedef struct s_heap	t_heap;

struct	s_memory
{
	t_meta		*tiny;
	t_meta		*small;
	t_meta		*large;
	t_heap		*heap;
};

struct	s_meta
{
	int			free;
	int			heap_start;
	size_t		size;
	t_meta		*next;
	char		data[1];
};

struct	s_heap
{
	size_t		size;
	t_meta		*zone;
	t_heap		*next;
};

t_memory	g_memory;

void	show_alloc_mem();
void	ft_free(void *ptr);
void	*ft_malloc(size_t size);
void	*realloc(void *ptr, size_t size);
t_meta	*zone_list(size_t size);
int		get_zone_size(size_t size);
t_meta	*alloc_zone(t_meta *last, size_t size);
t_meta	*find_space(t_meta **last_block, size_t size);
void	adjust_zone(t_meta *block, size_t size);

# endif
