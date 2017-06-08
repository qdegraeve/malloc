/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:44:56 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/08 18:43:23 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta	*find_space(t_meta **last_block, size_t size)
{
	t_meta	*block;

	block = zone_list(size);
	while (block && !(block->size >= size && block->free))
	{
		*last_block = block;
		block = block->next;
	}
	if (block && block->size > size)
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
	write(1, "adresse allouee : ", 18);
	ft_putbase((unsigned long)block->data, 16);
	write(1, "\n", 1);
	write(1, "size : ", 7);
	ft_putbase(size, 10);
	write(1, "\n", 1);
	show_alloc_mem();
	return((void*)block->data);
}
