/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whoareyou.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 03:45:43 by frmarinh          #+#    #+#             */
/*   Updated: 2017/08/03 03:50:22 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>


int		main(int argc, char **argv)
{
	char	name[1024];
	int		age;
	memset(&name, 0, 1024);

	printf("Hey, stop ! Tell me who are you, what's your name ?\n");
	scanf("%s", name);
	printf("Ok %s, now tell me your age !\n", name);
	scanf("%d", &age);
	printf("Hello %s, you're age is %d\n", name, age);
}
