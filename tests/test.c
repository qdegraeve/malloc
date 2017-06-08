/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 10:22:03 by qdegraev          #+#    #+#             */
/*   Updated: 2017/06/08 17:21:20 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "malloc.h"
#include <string.h>

void	show()
{
	write(1, "\n", 1);
	show_alloc_mem();
	write(1, "\n", 1);
}

void	text(char *str)
{
	printf("\b\b--  %s  --\n", str);
}

int main() {
	char *ptr = NULL;
	char *ptr2 = NULL;
	char *ptr3 = NULL;
	char *ptr4 = NULL;
	char *ptr5 = NULL;
	char *ptr6 = NULL;
	char *ptr8 = NULL;
	char ptr9[10];
	text("allocation de 6 pointeurs de taille 10 50 100 100 100 250 et 5000");
	text("la zones TINY doit contenir 5 allocation et la zone LARGE doit en contenir une");
	ptr = malloc(10);
	ptr = strcpy(ptr, "caca pipi\0");
	ptr2 = malloc(50);
	ptr2 = strcpy(ptr2, "jesuistresbeau\0");
	ptr3 = malloc(100);
	ptr3 = strcpy(ptr3, "et aussi tres intelligent\0");
	ptr4 = malloc(100);
	ptr5 = malloc(250);
	ptr6 = malloc(5000);
	show();
	text("appel a free() sur les pointeurs 3 2 puis 4");
	free(ptr3);
	free(ptr2);
	free(ptr4);
	show();
	text("allocation d'un pointeur de 240 octets");
	text("celui ci doit s'inserer apres le premier pointeur de 10 octets et avant ceuil de 250");
	ptr2 = malloc(200);
	show();
	text("reallocation du pointeur 5 de 250 a 255 octets");
	text("son addresse doit rester identique");
	ptr5 = realloc(ptr5, 255);
	show();
	text("reallocation du pointeur 2 de 200 a 250 octets");
	text("son adresse doit rester identique");
	text("reallocation du pointeur 1 de 10 a 50 octets");
	text("son address doit etre differente mais son contenu identique");
	text("realloc d'un pointeur null sur ptr8 de 500 octets (zone SMALL)");
	ptr2 = realloc(ptr2, 250);
	printf("ptr before realloc == [%s]\n", ptr);
	ptr = realloc(ptr, 50);
	printf("ptr after realloc == [%s]\n", ptr);
	ptr8 = realloc(NULL, 500);
	show();
	text("appel a free sur le poiteur 8 de 500 octets");
	text("la zone SMALL doit a nouveau avoir une adresse a 0X0");
	free(ptr8);
	show();
	text("appel a free sur tous les pointeurs restant");
	text("toutes les zones doivent avoir une adress a 0x0");
	free(ptr);
	free(ptr2);
	free(ptr5);
	free(ptr6);
	show();
	text("appel a free sur un pointeur non malloc, le programme doit abort avec un message d'erreur");
	free(ptr9);
}
