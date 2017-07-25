/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 18:25:29 by frmarinh          #+#    #+#             */
/*   Updated: 2017/07/04 18:29:32 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Get the file stat structure
*/
static struct stat		*get_file_stat(char *file)
{
	struct stat		*tmp;

	if (!(tmp = malloc(sizeof(struct stat))))
		return (NULL);
	if (stat(file, tmp) < 0)
		return (NULL);
	return (tmp);
}

/*
**	Check if the file is readable
*/
static bool				check_if_readable(struct stat *file_stat, t_famine *famine)
{
	return (file_stat->st_mode & S_IRUSR);
}

/*
**	Return the file_stat structure if readable && is a file
*/
struct stat				*check_access_file(char *file, t_famine *famine)
{
	struct stat		*file_stat;

	file_stat = NULL;
	if ((file_stat = get_file_stat(file)) != NULL)
	{
		if (!check_if_readable(file_stat, famine))
			return (NULL);
		if (!S_ISREG(file_stat->st_mode))
			return (NULL);
		return (file_stat);
	}
	else
		print_message(famine, strerror(errno), true);
	return (NULL);
}
