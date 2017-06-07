/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:45:32 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/07 12:58:06 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	defragment_blocks(t_meta *block1, t_meta *block2)
{
	block1->next = block2->next;
	block1->size += (block2->size + META_SIZE);
	block1->free = 1;
}

void	error()
{
	write(1, "Error\n", 6);
	exit(1);
}

void	find_and_free(void *ptr, t_meta *block)
{
	t_meta	*tmp;

	tmp = block;
	while(block && (void*)block->data != ptr)
	{
		tmp = block;
		block = block->next;
		if (block->heap_start || !block)
			error();
	}
	if (tmp->free && tmp != block)
		defragment_blocks(tmp, block);
	else if (block->next->free)
		defragment_blocks(block, block->next);
	else
		block->free = 1;
}

void	ft_free(void *ptr)
{
	t_heap	*heap;

	DEBUG
	heap = g_memory.heap;
	DEBUG
	while(heap && !((void*)heap < ptr && (void*)(heap + heap->size) > ptr))
	{
		DEBUG
		heap = heap->next;
	}
	if (heap)
	{
		DEBUG
		find_and_free(ptr, heap->zone);
	}
	else
		error();
}
