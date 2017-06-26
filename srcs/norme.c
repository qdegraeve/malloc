/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:14:19 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/26 14:14:23 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*mutex_unlock(void *return_value, pthread_mutex_t *mutex)
{
	pthread_mutex_unlock(mutex);
	return (return_value);
}
