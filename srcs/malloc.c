/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:44:56 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/06 20:42:56 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_malloc(size_t size)
{
	t_meta	*zone;
	t_meta	*block;

	zone = zone_list(size);
	if (zone && (block = find_space(&zone, size)))
		block->free = 0;
	else
		block = alloc_zone(zone, size);
	if (!block)
		return (NULL);
	return(block + 1);
}
