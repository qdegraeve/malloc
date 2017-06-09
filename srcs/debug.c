/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 12:27:18 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/09 18:31:23 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	debug_show_actions(int src, void *ptr)
{
	static int	debug = -1;
	char		*str;

	if (debug < 0)
	{
		str = getenv("MALLOC_SHOW_ACTIONS");
		if (str && !ft_strcmp(str, "true"))
			debug = 1;
		else
			debug = 0;
	}
	if (debug > 0)
	{
		if (src == MALLOC_FCT)
			ft_putstr("\nmalloc() function called\n");
		else if (src == FREE_FCT)
		{
			ft_putstr("\nfree() function called\npointer address : ");
			ft_putbase((unsigned long)ptr, 16);
			write(1, "\n", 1);
		}
		show_alloc_mem();
	}
}

int		debug_show_free(void)
{
	static int	debug = -1;
	char		*str;

	if (debug >= 0)
		return (debug);
	str = getenv("MALLOC_SHOW_FREE");
	if (str && !ft_strcmp(str, "true"))
		debug = 1;
	else
		debug = 0;
	return (debug);
}

int		debug_show_mmap(void)
{
	static int	debug = -1;
	char		*str;

	if (debug >= 0)
		return (debug);
	str = getenv("MALLOC_SHOW_MMAP");
	if (str && !ft_strcmp(str, "true"))
		debug = 1;
	else
		debug = 0;
	return (debug);
}
