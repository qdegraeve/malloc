/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:45:32 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/07 17:51:59 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	defragment_blocks(t_meta *block1, t_meta *block2)
{
	if (block1 != block2 && block2->next->free && !block2->next->heap_start)
	{
		block1->size += (block2->size + block2->next->size + (2 * META_SIZE));
		block1->next = block2->next->next;
	}
	else if (block1 != block2)
	{
		block1->size += (block2->size + META_SIZE);
		block1->next = block2->next;
	}
	else if (block2->next->free && !block2->next->heap_start)
	{
			block2->size += (block2->next->size + META_SIZE);
		block2->next = block2->next->next;
	}
	else
		block2->free = 1;
}

void	error()
{
	write(1, "Error\n", 6);
	exit(1);
}

void	munmap_heap(t_heap *prev, t_heap *heap)
{
		write(1, __FUNCTION__, 10);
		write(1, "\n", 1);
	if (prev != heap)
		prev->next = heap->next;
	else
		g_memory.heap = heap->next;
	munmap(heap, heap->size);
}

void	find_and_free(void *ptr, t_meta *block, t_heap *prev, t_heap *heap)
{
	t_meta	*tmp;

	tmp = block;
		write(1, __FUNCTION__, 10);
		write(1, "\n", 1);
	while(block && (void*)block->data != ptr)
	{
		tmp = block;
		block = block->next;
		if (block->heap_start || !block)
			error();
	}
	tmp = tmp->free ? tmp : block;
	defragment_blocks(tmp, block);
	if (block->heap_start && block->size + META_SIZE == heap->size)
		munmap_heap(prev, heap);
}

void	free(void *ptr)
{
	t_heap	*heap;
	t_heap	*prev;

	heap = g_memory.heap;
	prev = heap;
	while(heap && !((void*)heap < ptr && (void*)(heap + heap->size) > ptr))
	{
		prev = heap;
		heap = heap->next;
	}
	if (heap)
	{
		write(1, __FUNCTION__, 10);
		write(1, "\n", 1);
		if (((t_meta*)heap->block)->data == ptr && heap->size == META_SIZE + ((t_meta*)heap->block)->size)
			munmap_heap(prev, heap);
		else
			find_and_free(ptr, (t_meta*)heap->block, prev, heap);
	}
	else
		error();
}
