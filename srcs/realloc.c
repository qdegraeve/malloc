/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 18:48:56 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/08 18:33:40 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta	*check_ptr(void *ptr)
{
	t_heap	*heap;
	t_meta	*block;

	heap = g_memory.heap;
	write(1, "sortie realloc check\n", 21);
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

void	*move_pointer(void *ptr, size_t size)
{
	void	*new;

	new = NULL;
	write(1, "sortie realloc move\n", 20);
	new = malloc(size);
	write(1, "sortie realloc move\n", 20);
	ft_memcpy(new, ptr, size);
	free(ptr);
	write(1, "sortie realloc move\n", 20);
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

	write(1, "adresse a realloc : ", 18);
	ft_putbase((unsigned long)ptr, 16);
	write(1, "\n", 1);
	block = NULL;
	show_alloc_mem();
	if (!ptr)
		return (malloc(size));
	block = check_ptr(ptr);
	if (size == 0)
	{
		free(ptr);
		return (malloc(0));
	}
	if (!has_space_after(block->next, block->size, size))
		return (move_pointer(ptr, size));
	write(1, "sortie realloc0\n", 16);
	block->size += (block->next->size + META_SIZE);
	block->next = block->next->next;
	if (block->next)
		block->next->prev = block;
	if (block->size > size)
		adjust_zone(block, size);
	write(1, "sortie realloc\n", 15);
	return (ptr);
}
