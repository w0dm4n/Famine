/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 03:45:10 by frmarinh          #+#    #+#             */
/*   Updated: 2017/07/25 03:45:16 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
** Allocate size from a file descriptor
*/
/*void		*ft_mmap(int fd, size_t size)
{
	return (mmap(0, size, PROT_READ, MAP_SHARED, fd, 0));
}*/

uint32_t	swap_int32(uint32_t x)
{
	return ((uint32_t)((((uint32_t)(x) & 0xff000000) >> 24) | \
		(((uint32_t)(x) & 0x00ff0000) >> 8) | \
		(((uint32_t)(x) & 0x0000ff00) << 8) | \
		(((uint32_t)(x) & 0x000000ff) << 24)));
}

/*
**	Print the message if famine is on DEBUG_MODE
*/
void				print_message(t_famine *famine, char *message, bool leave)
{
	if (famine->debug == true) {
		printf("%s\n", message);
	}
	if (leave) {
		exit (EXIT_CODE);
	}
}
