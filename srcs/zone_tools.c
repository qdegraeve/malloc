/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:08:51 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/09 19:36:34 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta	*zone_list(size_t size)
{
	t_meta	*block;

	if (size <= TINY)
		block = g_memory.tiny;
	else if (size <= SMALL)
		block = g_memory.small;
	else
		block = g_memory.large;
	while (block && block->next)
		block = block->next;
	return (block);
}

size_t	get_zone_size(size_t size)
{
	size_t	zone;
	int		page;

	page = getpagesize();
	if (size <= TINY)
		zone = (((((TINY + META_SIZE) * 100) + HEAP_META_SIZE) / page) \
				* page) + page;
	else if (size <= SMALL)
		zone = (((((SMALL + META_SIZE) * 100) + HEAP_META_SIZE) / page) \
				* page) + page;
	else
		zone = (((size + META_SIZE + HEAP_META_SIZE) / page) * page) + page;
	return (zone);
}

void	create_memory(size_t size, t_meta *block)
{
	if (size <= TINY)
		g_memory.tiny = block;
	else if (size <= SMALL)
		g_memory.small = block;
	else
		g_memory.large = block;
}

void	*new_heap(size_t size)
{
	t_heap	*heap;
	t_heap	*new;

	heap = g_memory.heap;
	if (!(new = mmap(0, size, FLAG_PROT, FLAG_MAP, -1, 0)))
		return (NULL);
	new->size = size - HEAP_META_SIZE;
	new->next = NULL;
	while (heap)
		heap = heap->next;
	if (heap)
		heap->next = new;
	else
		g_memory.heap = new;
	return ((void*)new->block);
}

t_meta	*alloc_zone(t_meta *last, size_t size)
{
	t_meta	*new;
	size_t	zone_size;

	zone_size = get_zone_size(size);
	new = new_heap(zone_size);
	if (!new)
		return (NULL);
	new->size = zone_size - HEAP_META_SIZE - META_SIZE;
	new->free = 0;
	new->next = NULL;
	new->prev = NULL;
	new->heap_start = 1;
	if (size <= SMALL && size < (zone_size - META_SIZE - HEAP_META_SIZE))
		adjust_zone(new, size);
	if (last)
	{
		last->next = new;
		new->prev = last;
	}
	else
		create_memory(size, new);
	return (new);
}
