/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:08:51 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/07 13:08:01 by qdegraev         ###   ########.fr       */
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
	zone = ((((size + sizeof(t_meta) - 1) * 100) / page) * page) + page;
	return (zone);
}

void	create_memory(size_t size, t_meta *block)
{
	DEBUG
	if (size <= TINY)
		g_memory.tiny = block;
	else if (size <= SMALL)
		g_memory.small = block;
	else
		g_memory.large = block;
}

void	add_to_heap(t_meta *zone, size_t size)
{
	t_heap	*heap;
	t_heap	*new;

	heap = g_memory.heap;
	new = NULL;
	new->size = size;
	new->zone = zone;
	new->next = NULL;
	while (heap && heap->next)
		heap = heap->next;
	if (heap)
		heap->next = new;
	else
		g_memory.heap = new;
}

t_meta	*alloc_zone(t_meta *last, size_t size)
{
	t_meta	*new;
	size_t	zone_size;

	DEBUG
	zone_size = get_zone_size(size);
	new = mmap(0, zone_size, FLAG_PROT, FLAG_MAP, 0, 0);
	if (!new)
		return (NULL);
	new->size = zone_size - META_SIZE;
	new->free = 0;
	new->next = NULL;
	printf("new->size == %lu\n", new->size);
	printf("new->next->size == %lu\n", new->next ? new->next->size : 0);
	if (size < zone_size)
		adjust_zone(new, size);
	printf("new->size == %lu\n", new->size);
	printf("new->next->size == %lu\n", new->next->size);
	if (last)
		last->next = new;
	else
		create_memory(size, new);
	printf("adresse de tiny == %p\n", g_memory.tiny);
	printf("adresse de new == %p\n", new);
	add_to_heap(new, zone_size);
	return (new);
}

t_meta	*find_space(t_meta **last_block, size_t size)
{
	t_meta	*block;

	DEBUG
	block = zone_list(size);
	if (block)
		printf("block->size == %lu\n", block->size);
	while (block && !(block->size >= size && block->free))
	{
		DEBUG
		*last_block = block;
		block = block->next;
	}

	if (block)
		printf("block->size == %lu\n", block->size);
	if (block && block->size > size)
		adjust_zone(block, size);
	return (block);
}

void	adjust_zone(t_meta *block, size_t size)
{
	t_meta	*new;

	DEBUG
	printf("size == %lu\n*block->size == %lu\nMETA_SIZE == %lu\n", size, block->size, META_SIZE);
	new = (t_meta*)((char*)block + size + META_SIZE);
	new->size = (block->size - (size + META_SIZE));
	new->free = 1;
	new->next = block->next;
	block->size = size;
	block->next = new;
	printf("new->size == %lu\n", new->size);
	printf("block->size == %lu\n", block->size);
	printf("adresse de block == %p\n", block);
	printf("adresse de new == %p\n", new);

}
