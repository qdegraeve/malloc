/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:48:20 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/05 17:30:08 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	print_list(t_meta_data *list)
{
	int		size;

	size = 0;
	while(list)
	{
		list = list->next;
	}
	return (size);
}

void	show_alloc_mem()
{
	print_list(g_memory.tiny);
	print_list(g_memory.medium);
	print_list(g_memory.large);
}
