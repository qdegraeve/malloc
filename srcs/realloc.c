/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 18:48:56 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/09 19:12:14 by qdegraev         ###   ########.fr       */
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
		if (!block || block->heap_start)
			return (NULL);
	}
	return (block);
}

void	*move_pointer(void *ptr, size_t size, int must_free)
{
	void	*new;

	new = NULL;
	new = malloc(size);
	if (new)
		new = ft_memcpy(new, ptr, size);
	if (new && must_free)
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

	if (pthread_mutex_lock(&g_safe.mut_realloc) == EINVAL)
	{
		pthread_mutex_init(&g_safe.mut_realloc, NULL);
		pthread_mutex_lock(&g_safe.mut_realloc);
	}
	block = NULL;
	if (!ptr)
		return (mutex_unlock(malloc(size), &g_safe.mut_realloc));
	if (!(block = check_ptr(ptr)) || size == 0 \
		|| !has_space_after(block->next, block->size, size))
		return (mutex_unlock(move_pointer(ptr, size, 1), &g_safe.mut_realloc));
	block->size += (block->next->size + META_SIZE);
	block->next = block->next->next;
	if (block->next)
		block->next->prev = block;
	if (block->size > size)
		adjust_zone(block, size);
	pthread_mutex_unlock(&g_safe.mut_realloc);
	return (ptr);
}

void	*reallocf(void *ptr, size_t size)
{
	t_meta	*block;

	if (pthread_mutex_lock(&g_safe.mut_reallocf) == EINVAL)
	{
		pthread_mutex_init(&g_safe.mut_reallocf, NULL);
		pthread_mutex_lock(&g_safe.mut_reallocf);
	}
	block = NULL;
	if (!ptr)
		return (mutex_unlock(malloc(size), &g_safe.mut_reallocf));
	if (!(block = check_ptr(ptr)) || size == 0 \
		|| !has_space_after(block->next, block->size, size))
		return (mutex_unlock(move_pointer(ptr, size, 0), &g_safe.mut_reallocf));
	block->size += (block->next->size + META_SIZE);
	block->next = block->next->next;
	if (block->next)
		block->next->prev = block;
	if (block->size > size)
		adjust_zone(block, size);
	pthread_mutex_unlock(&g_safe.mut_reallocf);
	return (ptr);
}
