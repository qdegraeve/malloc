/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 10:48:20 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/09 17:38:44 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static int	print_list(t_meta *list)
{
	int		size;

	size = 0;
	if (!list)
		write(1, "\n", 1);
	while (list)
	{
		if (!list->free || debug_show_free())
		{
			ft_putbase((unsigned long)(list->data), 16);
			write(1, " - ", 3);
			ft_putbase((unsigned long)(list->data + list->size), 16);
			write(1, " : ", 3);
			ft_putnbr(list->size);
			write(1, " octets", 8);
			if (list->free && debug_show_free())
				write(1, " utilisables", 12);
			size += list->size;
		}
		if (list->heap_start && debug_show_mmap())
			ft_putstr("  --   HEAD OF PAGE\n");
		write(1, "\n", 1);
		list = list->next;
	}
	return (size);
}

void		show_alloc_mem(void)
{
	int		size;

	if (pthread_mutex_lock(&g_safe.mut_show) == EINVAL)
	{
		pthread_mutex_init(&g_safe.mut_show, NULL);
		pthread_mutex_lock(&g_safe.mut_show);
	}
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
	write(1, "\nTotal : ", 9);
	ft_putnbr(size);
	write(1, "\n", 1);
	pthread_mutex_unlock(&g_safe.mut_show);
}
