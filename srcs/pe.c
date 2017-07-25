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
	pe_file->name	= file_name;
	pe_file->path	= file_path;
	pe_file->buffer = NULL;
	pe_file->len	= 0;
	return (pe_file);
}

/*
** Open the PE file and read the content
*/
static void            open_pe_file(t_pe *pe, t_famine *famine)
{
	int			bytes = 0;
    int			fd = 0;

	if ((fd = open(pe->path, O_RDONLY)) == -1)
		print_message(famine, strerror(errno), true);
	if ((pe->len = lseek(fd, 0, SEEK_END)) <= 0)
		print_message(famine, strerror(errno), true);
	if (!(pe->buffer = ft_strnew(pe->len)))
		print_message(famine, strerror(errno), true);
	if ((bytes = read(fd, pe->buffer, pe->len)) <= 0)
		print_message(famine, strerror(errno), false);
	printf("File descriptor: %d, file length: %d, bytes read: %d\n", fd, pe->len, bytes);
	/*HANDLE handle = CreateFile
        (
            "hello.exe",
            GENERIC_READ,
            0,
            0,
            OPEN_EXISTING,
            0,
            0
        );
	ReadFile(handle, pe->buffer, 1024, bytes, 0);
	printf("Byte read: %d, file path: %s\n", bytes, pe->path);*/
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
		//IMAGE_DOS_HEADER* pe_header = (IMAGE_DOS_HEADER*)pe_file->buffer;
		//printf("File len : %d\n", pe_file->len);
		//printf("magic value: %d\n", pe_header->e_magic);
		/*int i = 0;
		while(i < pe_file->len) {
			printf("%x", pe_file->buffer[i++]);
		}
		printf("\n");*/
		return (pe_file);
	} else {
		return (NULL);
	}
}
