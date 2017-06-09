/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:45:32 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/09 19:17:31 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta	*defragment_blocks(t_meta *block1, t_meta *block2)
{
	if (block1 != block2 && block2->next->free && !block2->next->heap_start)
	{
		block1->size += (block2->size + block2->next->size + (2 * META_SIZE));
		block1->next = block2->next->next;
		return (block1);
	}
	else if (block1 != block2)
	{
		block1->size += (block2->size + META_SIZE);
		block1->next = block2->next;
		return (block1);
	}
	else if (block2->next->free && !block2->next->heap_start)
	{
		block2->size += (block2->next->size + META_SIZE);
		block2->next = block2->next->next;
	}
	block2->free = 1;
	return (block2);
}

void	munmap_heap(t_heap *prev, t_heap *heap, size_t size)
{
	t_meta	*block_prev;

	block_prev = ((t_meta*)(heap->block))->prev;
	if (block_prev)
	{
		block_prev->next = ((t_meta*)(heap->block))->next;
		if (block_prev->next)
			block_prev->next->prev = block_prev;
	}
	else
	{
		if (size <= TINY)
			g_memory.tiny = ((t_meta*)(heap->block))->next;
		else if (size <= SMALL)
			g_memory.small = ((t_meta*)(heap->block))->next;
		else
			g_memory.large = ((t_meta*)(heap->block))->next;
	}
	if (prev != heap)
		prev->next = heap->next;
	else
		g_memory.heap = heap->next;
}

void	find_and_free(void *ptr, t_meta *block, t_heap *prev, t_heap *heap)
{
	t_meta	*tmp;
	size_t	size;

	tmp = block;
	size = 0;
	while (block && (void*)block->data != ptr)
	{
		tmp = block;
		block = block->next;
		if (block->heap_start || !block)
			return ;
	}
	size = block->size;
	tmp = tmp->free ? tmp : block;
	block = defragment_blocks(tmp, block);
	if (block->heap_start && block->size + META_SIZE == heap->size)
	{
		munmap_heap(prev, heap, size);
	}
}

void	free(void *ptr)
{
	t_heap	*heap;
	t_heap	*prev;

	heap = g_memory.heap;
	prev = heap;
	if (!ptr)
		return ;
	while (heap && !((void*)heap < ptr && (void*)(heap) + heap->size > ptr))
	{
		prev = heap;
		heap = heap->next;
	}
	if (heap)
	{
		if (((t_meta*)heap->block)->data == ptr \
				&& heap->size == META_SIZE + ((t_meta*)heap->block)->size)
			munmap_heap(prev, heap, ((t_meta*)heap->block)->size);
		else
			find_and_free(ptr, (t_meta*)heap->block, prev, heap);
	}
	debug_show_actions(FREE_FCT, ptr);
}
