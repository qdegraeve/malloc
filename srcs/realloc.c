/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 18:48:56 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/09 17:26:08 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta	*check_ptr(void *ptr)
{
	t_heap	*heap;
	t_meta	*block;

	heap = g_memory.heap;
	while (heap && !((void*)heap < ptr && (void*)(heap) + heap->size > ptr))
		heap = heap->next;
	if (!heap)
		return (NULL);
	block = (t_meta*)heap->block;
	while (block && (void*)block->data != ptr)
	{
		block = block->next;
		if (block->heap_start || !block)
			return (NULL);
	}
	return (block);
}

void	*move_pointer(void *ptr, size_t size)
{
	void	*new;

	new = NULL;
	new = malloc(size);
	if (new)
		new = ft_memcpy(new, ptr, size);
	free(ptr);
	return (new);
}

int		has_space_after(t_meta *block, size_t block_size, size_t size)
{
	if (!block)
		return (0);
	if (block->heap_start || !block->free)
		return (0);
	if (block->free && block->size + block_size + META_SIZE <= size)
		return (0);
	return (1);
}

void	*realloc(void *ptr, size_t size)
{
	t_meta	*block;

	block = NULL;
	if (!ptr)
		return (malloc(size));
	if (!(block = check_ptr(ptr)))
		return (move_pointer(ptr, size));
	if (size == 0)
		return (move_pointer(ptr, size));
	if (!has_space_after(block->next, block->size, size))
		return (move_pointer(ptr, size));
	block->size += (block->next->size + META_SIZE);
	block->next = block->next->next;
	if (block->next)
		block->next->prev = block;
	if (block->size > size)
		adjust_zone(block, size);
	return (ptr);
}
