/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_pe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/25 01:17:06 by frmarinh          #+#    #+#             */
/*   Updated: 2017/07/25 01:17:12 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Alloc and set the full path of the executable
*/
static char			*get_file_path(char *file_name, char *folder_path)
{
	char		*path	= NULL;

	if (!(path = ft_strnew((ft_strlen(folder_path) + ft_strlen(file_name) + 2))))
		return (NULL);
	ft_strcat(path, folder_path);
	ft_strcat(path, BACKSLASH);
	ft_strcat(path, file_name);
	return (path);
}

/*
**	Alloc PE custom structure
*/
static t_pe			*alloc_pe(char *file_name, char *file_path)
{
	t_pe			*pe_file	= NULL;

	if (!(pe_file = (t_pe*)malloc(sizeof(struct s_pe))))
		return (NULL);
	pe_file->name = file_name;
	pe_file->path = file_path;
	return (pe_file);
}

/*
** Open the PE file and read the content
*/
static void            open_pe_file(t_pe *pe, t_famine *famine)
{
    int     fd = 0;
    if ((fd = open(pe->path, O_RDONLY)) == -1)
		print_message(famine, strerror(errno), true);
	if ((pe->len = lseek(fd, 0, SEEK_END)) <= 0)
		print_message(famine, strerror(errno), true);
	if (!(pe->buffer = ft_strnew(pe->len)))
		print_message(famine, strerror(errno), true);
	if ((read(fd, pe->buffer, pe->len)) == -1)
		print_message(famine, strerror(errno), true);
}

/*
**	Read a PE file
*/
t_pe			*pe(t_famine *famine, char *folder_path, char *file_name)
{
	char		*file_path	= get_file_path(file_name, folder_path);
	t_pe		*pe_file	= alloc_pe(file_name, file_path);

	if (pe_file && pe_file->path) {
		open_pe_file(pe_file, famine);
		printf("File len : %d\n", pe_file->len);
		return (pe_file);
	} else {
		return (NULL);
	}
}
