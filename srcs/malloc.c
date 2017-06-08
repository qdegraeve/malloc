/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:44:56 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/09 01:38:29 by qdegraev         ###   ########.fr       */
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
	if (block && (block->size  > size + META_SIZE))
		adjust_zone(block, size);
	return (block);
}

void	*malloc(size_t size)
{
	t_meta	*zone;
	t_meta	*block;

	zone = zone_list(size);
	if (size <= 4096 && zone && (block = find_space(&zone, size)))
		block->free = 0;
	else
		block = alloc_zone(zone, size);
	if (!block)
		return (NULL);
	return((void*)block->data);
}
