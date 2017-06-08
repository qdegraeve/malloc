/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:08:51 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/09 01:19:12 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta	*zone_list(size_t size)
{
	if (size <= TINY)
		return (g_memory.tiny);
	else if (size <= SMALL)
		return (g_memory.small);
	else
		return (g_memory.large);
}

int		get_zone_size(size_t size)
{
	int		zone;
	int		page;

	page = getpagesize();
	if (size <= SMALL)
		zone = (((((size + META_SIZE) * 100) + HEAP_META_SIZE - 1) / page) \
				* page) + page;
	else
		zone = size + META_SIZE + HEAP_META_SIZE;
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
	new = mmap(0, size, FLAG_PROT, FLAG_MAP, 0, 0);
	new->size = size - HEAP_META_SIZE;
	new->next = NULL;
	while (heap && heap->next)
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
	if (size < (zone_size - META_SIZE - HEAP_META_SIZE))
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

void	adjust_zone(t_meta *block, size_t size)
{
	t_meta	*new;

	new = (t_meta*)(block->data + size);
	new->size = block->size - size - META_SIZE;
	new->free = 1;
	new->heap_start = 0;
	new->next = block->next;
	if (new->next)
		new->next->prev = new;
	new->prev = block;
	block->size = size;
	block->next = new;
}
