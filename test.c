/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:22:03 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/05 17:08:14 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
 #include "malloc.h"

int main() {
	char *ptr = NULL;
	char *ptr2 = NULL;
	int size = 0;

	ptr = malloc(TINY_ZONE);
	ptr2 = malloc(SMALL_ZONE);
	size = getpagesize();
	printf("adresse de ptr = %p\n", ptr);
	printf("taille des pages = %d\n", size);
	printf("TINY = %lu\n", TINY_ZONE);
	printf("SMALL = %lu\n", SMALL_ZONE);
	printf("128 << 0 == %d\n", 128 << 0);
	printf("128 >> 3 == %d\n", 128 >> 3);
	printf("129 >> 4 == %d\n", 128 >> 4);
	printf("t_metadata == %d\nint == %d\n meta_ptr == %d\nsize_t == %d\n", (int)sizeof(t_meta_data), (int)sizeof(int), (int)sizeof(t_meta_data*), (int)sizeof(size_t));
}
