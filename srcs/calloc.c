/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:14:30 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/26 14:14:32 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*new;

	if (pthread_mutex_lock(&g_safe.mut_calloc) == EINVAL)
	{
		pthread_mutex_init(&g_safe.mut_calloc, NULL);
		pthread_mutex_lock(&g_safe.mut_calloc);
	}
	new = malloc(count * size);
	ft_bzero(new, count * size);
	pthread_mutex_unlock(&g_safe.mut_calloc);
	return (new);
}
