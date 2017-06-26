/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:44:56 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/09 19:18:36 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta	*find_space(t_meta **last_block, size_t size)
{
	t_meta	*block;

	block = *last_block;
	while (block && !(block->size >= size && block->free))
	{
		*last_block = block;
		block = block->next;
	}
	if (block && (block->size > size + META_SIZE))
		adjust_zone(block, size);
	return (block);
}

void	adjust_zone(t_meta *block, size_t size)
{
	t_meta	*new;

	new = (t_meta*)(block->data + size);
	new->size = block->size - size - META_SIZE;
	new->free = 1;
	new->heap_start = 0;
	new->next = block->next;
	if (new->next)
		new->next->prev = new;
	new->prev = block;
	block->size = size;
	block->next = new;
}

void	*malloc(size_t size)
{
	t_meta	*zone;
	t_meta	*block;

	if (pthread_mutex_lock(&g_safe.mut_malloc) == EINVAL)
	{
		pthread_mutex_init(&g_safe.mut_malloc, NULL);
		pthread_mutex_lock(&g_safe.mut_malloc);
	}
	zone = zone_list(size);
	if (size <= SMALL && zone && (block = find_space(&zone, size)))
		block->free = 0;
	else
		block = alloc_zone(zone, size);
	if (!block)
	{
		pthread_mutex_unlock(&g_safe.mut_malloc);
		return (NULL);
	}
	debug_show_actions(MALLOC_FCT, NULL);
	pthread_mutex_unlock(&g_safe.mut_malloc);
	return ((void*)block->data);
}
