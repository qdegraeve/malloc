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

t_meta		*defragment_blocks(t_meta *block1, t_meta *block2)
{
	if (block1 != block2)
	{
		block1->size += (block2->size + META_SIZE);
		block1->next = block2->next;
		if (block1->next)
			block1->next->prev = block1;
		block2 = block1;
	}
	if (block2->next && !block2->next->heap_start && block2->next->free)
	{
		block2->size += (block2->next->size + META_SIZE);
		block2->next = block2->next->next;
		if (block2->next)
			block2->next->prev = block2;
	}
	return (block2);
}

void		munmap_heap(t_heap *prev, t_heap *heap, size_t size)
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
	munmap(heap, heap->size);
}

void		find_and_free(void *ptr, t_meta *block)
{
	t_meta	*tmp;
	size_t	size;

	size = 0;
	tmp = block;
	while (block && (void*)block->data != ptr)
	{
		tmp = block;
		block = block->next;
		if (!block || block->heap_start)
			return ;
	}
	size = block->size;
	block->free = 1;
	tmp = (tmp->free && !block->heap_start) ? tmp : block;
	block = defragment_blocks(tmp, block);
}

static void	ft_norminette(t_meta *block, void *ptr, t_heap *heap, t_heap *prev)
{
	if (block->data == ptr && block->size > SMALL)
		munmap_heap(prev, heap, block->size);
	else
		find_and_free(ptr, block);
}

void		free(void *ptr)
{
	t_heap	*heap;
	t_heap	*prev;

	if (pthread_mutex_lock(&g_safe.mut_free) == EINVAL)
	{
		pthread_mutex_init(&g_safe.mut_free, NULL);
		pthread_mutex_lock(&g_safe.mut_free);
	}
	heap = g_memory.heap;
	prev = heap;
	if (!ptr)
	{
		pthread_mutex_unlock(&g_safe.mut_free);
		return ;
	}
	while (heap && !((void*)heap < ptr && (void*)(heap) + heap->size > ptr))
	{
		prev = heap;
		heap = heap->next;
	}
	if (heap)
		ft_norminette((t_meta*)heap->block, ptr, heap, prev);
	debug_show_actions(FREE_FCT, ptr);
	pthread_mutex_unlock(&g_safe.mut_free);
}
