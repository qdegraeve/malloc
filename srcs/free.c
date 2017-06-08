/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:45:32 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/08 16:43:43 by qdegraev         ###   ########.fr       */
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

void	error(void *ptr, int origin)
{
	ft_putstr("malloc: *** error for object ");
	ft_putbase((unsigned long)ptr, 16);
	ft_putstr(": pointer being ");
	if (origin == FREE_FCT)
		ft_putstr("freed");
	else if (origin == REALLOC_FCT)
		ft_putstr("realloc'd");
	ft_putstr(" was not allocated\n");
	abort();
}

void	munmap_heap(t_heap *prev, t_heap *heap, size_t size)
{
	if (((t_meta*)(heap->block))->prev)
	{
		((t_meta*)(heap->block))->prev->next = ((t_meta*)(heap->block))->next;
		((t_meta*)(heap->block))->prev->next->prev = ((t_meta*)(heap->block))->prev;
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
	munmap(heap, heap->size);
}

void	find_and_free(void *ptr, t_meta *block, t_heap *prev, t_heap *heap)
{
	t_meta	*tmp;
	size_t	size;

	tmp = block;
	size = 0;
	while(block && (void*)block->data != ptr)
	{
		tmp = block;
		block = block->next;
		if (block->heap_start || !block)
			error(ptr, FREE_FCT);
	}
	size = block->size;
	tmp = tmp->free ? tmp : block;
	block = defragment_blocks(tmp, block);
	if (block->heap_start && block->size + META_SIZE == heap->size)
		munmap_heap(prev, heap, size);
}

void	free(void *ptr)
{
	t_heap	*heap;
	t_heap	*prev;

	heap = g_memory.heap;
	prev = heap;
	while(heap && !((void*)heap < ptr && (void*)(heap) + heap->size > ptr))
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
	else
		error(ptr, FREE_FCT);
}
