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
