/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:22:03 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/06 21:06:28 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"
#include <string.h>

int main() {
	char *ptr = NULL;
	char *ptr2 = NULL;
	char *ptr3 = NULL;
	int size = 0;

	ptr3 = ft_malloc(10);
	ptr3 = strcpy(ptr3, "et aussi tres intelligent\0");
	ptr = (char*)ft_malloc(50);
	ptr = strcpy(ptr, "jesuistresbeau\0");
	ptr2 = ft_malloc(100);
	ptr2 = strcpy(ptr2, "et aussi tres intelligent\0");
	size = getpagesize();
	printf("ptr == %s\nadresse de ptr = %p\n", ptr, ptr);
	printf("ptr2 == %s\nadresse de ptr2 = %p\n", ptr2, ptr2);
	printf("ptr3 == %s\nadresse de ptr3 = %p\n", ptr3, ptr3);
}
