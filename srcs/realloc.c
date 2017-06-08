/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 18:48:56 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/08 16:41:35 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta	*check_ptr(void *ptr)
{
	t_heap	*heap;
	t_meta	*block;

	heap = g_memory.heap;
	while(heap && !((void*)heap < ptr && (void*)(heap) + heap->size > ptr))
		heap = heap->next;
	if (!heap)
		error(ptr, REALLOC_FCT);
	block = (t_meta*)heap->block;
	while(block && (void*)block->data != ptr)
	{
		block = block->next;
		if (block->heap_start || !block)
			error(ptr, REALLOC_FCT);
	}
	return (block);
}

void	*realloc(void *ptr, size_t size)
{
	t_meta	*block;
	void	*new;

	printf("entree\n");
	block = NULL;
	new = NULL;
	if (!ptr)
		return (malloc(size));
	block = check_ptr(ptr);
	if (size == 0)
	{
		free(ptr);
		return (malloc(0));
	}
	if (!block->next || (block->next && (block->next->heap_start || !block->next->free || (block->next->free && block->size + block->next->size + META_SIZE <= size))))
	{
		new = malloc(size);
		ft_memcpy(new, ptr, size);
		free(ptr);
		return (new);
	}
	block->size += (block->next->size + META_SIZE);
	block->next = block->next->next;
	if (block->next)
		block->next->prev = block;
	if (block->size > size)
		adjust_zone(block, size);
	return (ptr);
}
