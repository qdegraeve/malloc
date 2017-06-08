/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:48:20 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/08 18:42:13 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	print_list(t_meta *list)
{
	int		size;

	size = 0;
	while(list)
	{
		ft_putnbr(META_SIZE);
		write(1, "test\n", 5);
		if (!list->free)
		{
		write(1, "test2\n", 6);
			ft_putbase((unsigned long)(list->data), 16);
			write(1, " - ", 3);
			ft_putbase((unsigned long)(list->data + list->size), 16);
			write(1, " : ", 3);
			ft_putnbr(list->size);
			write(1, " octets\n", 8);
			size += list->size;
		}
		if (list->free && list->heap_start)
			write(1, "test3\n", 6);
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
	write(1, "SMALL : ", 8);
	ft_putbase((unsigned long)(g_memory.small), 16);
	write(1, "\n", 1);
	size += print_list(g_memory.small);
	write(1, "LARGE : ", 8);
	ft_putbase((unsigned long)(g_memory.large), 16);
	write(1, "\n", 1);
	size += print_list(g_memory.large);
	write(1, "Total : ", 8);
	ft_putnbr(size);
	write(1, "\n", 1);
}
