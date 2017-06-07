/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:22:03 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/07 17:56:50 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"
#include <string.h>
#include "libft.h"

int main() {
	char *ptr = NULL;
	char *ptr2 = NULL;
	char *ptr3 = NULL;
	char *ptr4 = NULL;
	char *ptr5 = NULL;
	char *ptr6 = NULL;
	char ptr7[34];
	int size = 0;

	ptr3 = ft_malloc(10);
	ptr3 = ft_strcpy(ptr3, "et aussi\0");
	ptr = ft_malloc(50);
	ptr = strcpy(ptr, "jesuistresbeau\0");
	ptr2 = ft_malloc(100);
	ptr2 = strcpy(ptr2, "et aussi tres intelligent\0");
	ptr4 = ft_malloc(100);
	ptr5 = ft_malloc(100);
	ptr6 = ft_malloc(5000);
	ft_malloc(250);
	size = getpagesize();
	printf("ptr == %s\nadresse de ptr = %p\n", ptr, ptr);
	printf("ptr2 == %s\nadresse de ptr2 = %p\n", ptr2, ptr2);
	printf("ptr3 == %s\nadresse de ptr3 = %p\n", ptr3, ptr3);
	show_alloc_mem();
	free(ptr);
	free(ptr2);
	free(ptr4);
	show_alloc_mem();
	ptr4 = ft_malloc(250);
	ptr2 = (char*)ft_malloc(60);
	show_alloc_mem();
	ptr2 = ft_strcpy(ptr, "test malloc de 60\0");
	printf("ptr2 == %s\nadresse de ptr2 = %p\n", ptr2, ptr2);
	show_alloc_mem();
	free(ptr3);
	free(ptr2);
	ptr2 = (char*)ft_malloc(60);
	ptr2 = ft_strcpy(ptr, "test malloc de 60 apres defragmentation\0");
	show_alloc_mem();
	free(ptr6);
	show_alloc_mem();
	printf("ptr2 == %s\nadresse de ptr2 = %p\n", ptr3, ptr3);
	free(ptr);
	free(ptr2);
	free(ptr4);
	free(ptr5);
	show_alloc_mem();
	free(ptr7);
}
