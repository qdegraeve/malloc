/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:39:23 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/09 19:58:46 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/resource.h>
# include <pthread.h>
# include <errno.h>
# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"

# define TINY 124
# define SMALL 1060
# define META_SIZE sizeof(t_meta)
# define HEAP_META_SIZE sizeof(t_heap)
# define FLAG_PROT (PROT_READ | PROT_WRITE)
# define FLAG_MAP (MAP_ANON | MAP_PRIVATE)

enum	e_origin { MALLOC_FCT, FREE_FCT, REALLOC_FCT };

typedef struct s_memory	t_memory;
typedef struct s_safe	t_safe;
typedef struct s_meta	t_meta;
typedef struct s_heap	t_heap;

struct	s_memory
{
	t_meta		*tiny;
	t_meta		*small;
	t_meta		*large;
	t_heap		*heap;
};

struct	s_safe
{
	pthread_mutex_t mut_malloc;
	pthread_mutex_t mut_free;
	pthread_mutex_t mut_realloc;
	pthread_mutex_t mut_reallocf;
	pthread_mutex_t mut_calloc;
	pthread_mutex_t mut_show;
};

struct	s_meta
{
	char		free;
	char		heap_start;
	size_t		size;
	t_meta		*next;
	t_meta		*prev;
	char		data[1];
};

struct	s_heap
{
	size_t		size;
	t_heap		*next;
	char		block[1];
};

t_memory	g_memory;
t_safe		g_safe;

void	*malloc(size_t size);
void	*calloc(size_t count, size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	*reallocf(void *ptr, size_t size);
t_meta	*zone_list(size_t size);
size_t	get_zone_size(size_t size);
t_meta	*alloc_zone(t_meta *last, size_t size);
t_meta	*find_space(t_meta **last_block, size_t size);
void	adjust_zone(t_meta *block, size_t size);
int		debug_show_free(void);
int		debug_show_mmap(void);
void	debug_show_actions(int src, void *ptr);
void	show_alloc_mem(void);
void	*mutex_unlock(void *return_value, pthread_mutex_t *mutex);

#endif
