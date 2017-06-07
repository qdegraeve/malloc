/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:48:20 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/07 12:12:48 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	print_list(t_meta *list)
{
	int		size;

	size = 0;
		while(list)
		{
			if (!list->free)
			{
				ft_putbase((unsigned long)(list + META_SIZE), 16);
				write(1, " - ", 3);
				ft_putbase((unsigned long)(list + META_SIZE + list->size), 16);
				write(1, " : ", 3);
				ft_putnbr(list->size);
				write(1, " octets\n", 8);
				size += list->size;
			}
			list = list->next;
		}
	return (size);
}

void	show_alloc_mem()
{
	int		size;
	size = 0;
	write(1, "TINY : ", 7);
	ft_putbase((unsigned long)(g_memory.tiny), 16);
	write(1, "\n", 1);
	size += print_list(g_memory.tiny);
	write(1, "SMALL : ", 7);
	ft_putbase((unsigned long)(g_memory.small), 16);
	write(1, "\n", 1);
	size += print_list(g_memory.small);
	write(1, "LARGE : ", 7);
	ft_putbase((unsigned long)(g_memory.large), 16);
	write(1, "\n", 1);
	size += print_list(g_memory.large);
	write(1, "Total : ", 8);
	ft_putnbr(size);
	write(1, "\n", 1);
}
