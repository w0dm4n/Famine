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
	int			bytes	= 0;
    int			fd		= 0;
	HANDLE		file	= NULL;
	HANDLE		mapping	= NULL;

	if ((fd = open(pe->path, O_RDWR)) == -1) {
		print_message(famine, strerror(errno), false);
		return;
	}
	if ((pe->len = lseek(fd, 0, SEEK_END)) <= 0) {
		print_message(famine, strerror(errno), false);
		return;
	}
	close (fd);
	if ((file = CreateFile(pe->path, GENERIC_READ,
	FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0)) == NULL) {
		print_message(famine, strerror(errno), false);
	}
	if ((mapping = CreateFileMapping(file, 0, PAGE_READONLY, 0, 0, 0)) == NULL)
		print_message(famine, strerror(errno), false);
	pe->buffer = MapViewOfFile(mapping, FILE_MAP_READ, 0, 0, 0);
	CloseHandle(file);
}

/*
**	Get magic value from DOS Header in hex
*/
static char			*get_dos_magic(t_pe *pe)
{
	char	*value			= NULL;
	char	*save_pointer	= NULL;
	char	*magic			= NULL;
	int		i = 0;

	if (!(value = ft_strnew(MAGIC_LENGTH * 2)))
		return (NULL);
	if (!(magic = ft_strnew(MAGIC_LENGTH * 2)))
		return (NULL);
	save_pointer = value;
	while (i < MAGIC_LENGTH)
	{
		asprintf(&value, "%x", pe->buffer[i++]);
		ft_strncat((char*) magic, value, 2);
		value += 2;
	}
	free(save_pointer);
	return (ft_strtoupper(magic));
}

/*
**	Get PE Signature from PE Header in hex
*/
static char			*get_pe_signature(t_pe *pe)
{
	char	*value			= NULL;

	if (!(value = ft_strnew(MAGIC_LENGTH * 2)))
		return (NULL);
	if (pe->pe_header != NULL && pe->pe_header->Signature != 0)
		asprintf(&value, "%x", pe->pe_header->Signature);
	return (value);
}

/*
**	Check if the PE file is a 64bits executable
*/
static bool		check_architecture_64(t_pe *pe)
{
	char	*value			= NULL;

	if (!(value = ft_strnew(MAGIC_LENGTH * 2)))
		return (false);
	if (pe->pe_header != NULL && pe->pe_header->OptionalHeader.Magic != 0)
		asprintf(&value, "%x", pe->pe_header->OptionalHeader.Magic);
	return (ft_strcmp(value, ARCHITECTURE_64) == 0);
}

/*
**	Allocate and copy buffer content
*/
static void		alloc_copy_buffer(t_pe *pe)
{
	if (!(pe->new_buffer = ft_strnew(pe->len)))
		return ;
	ft_memcpy(pe->new_buffer, pe->buffer, pe->len);
}

/*
**	Read a section from a PE file and set the signature in .rdata section
*/
static void		replace_section(t_pe *pe)
{
	IMAGE_SECTION_HEADER	*section = (IMAGE_SECTION_HEADER*)((void*)pe->pe_header + sizeof(IMAGE_NT_HEADERS));
	int i = 0, len = 0, lcount = 0;
	alloc_copy_buffer(pe);
	while (i < pe->pe_header->FileHeader.NumberOfSections)
	{
		if (!ft_strcmp(section[i].Name, ".rdata")) {
			char *buffer = (char*)(pe->buffer + section[i].PointerToRawData);
			int c = 0;
			while (c < section[i].SizeOfRawData && len < ft_strlen(SIGNATURE)) {
				if (buffer[c] == 0)
				{
					if (lcount == ((section[i].PointerToRawData + c) - 1)) { len++; } else { len = 0; }
					lcount = section[i].PointerToRawData + c;
				}
				c++;
			}
			if (len >= ft_strlen(SIGNATURE) && lcount != 0) {
				printf("(%s) was hidden in file: %s at offset: %d\n", SIGNATURE, pe->name, ((section[i].PointerToRawData + c) - ft_strlen(SIGNATURE)));
				char *message = ft_strdup(SIGNATURE);
				ft_memcpy((pe->new_buffer + ((section[i].PointerToRawData + c) - ft_strlen(SIGNATURE))), message, ft_strlen(SIGNATURE));
			}
		}
		i++;
	}
}

/*
**	Save current PE file and replace it
*/
static bool		save_pe(t_pe *pe, t_famine *famine)
{
	HANDLE	file;
	DWORD	dwBytesToWrite = (DWORD)pe->len, dwBytesWritten;
	if ((file = CreateFile(pe->path, FILE_GENERIC_WRITE, 0, NULL, OPEN_EXISTING,
		 FILE_ATTRIBUTE_NORMAL, 0)) == NULL) {
		print_message(famine, "Can't open a file for saving", false);
		return (false);
	}
	WriteFile(file, pe->new_buffer, dwBytesToWrite, &dwBytesWritten, NULL);
	if (dwBytesWritten <= 0) {
		print_message(famine, "Can't replace a file content", false);
		return (false);
	}
	printf("File %s was succesfully replaced with new data !\n", pe->path);
	CloseHandle(file);
	return (true);
}

/*
**	Set and check the DOS && PE Header
*/
static bool		pe_header(t_pe *pe, t_famine *famine)
{
	pe->dos_header		= (IMAGE_DOS_HEADER*) pe->buffer;
	char *magic			= get_dos_magic(pe);

	if (!ft_strcmp(magic, DOS_MAGIC)) {
		pe->pe_header = (IMAGE_NT_HEADERS*)(pe->buffer + pe->dos_header->e_lfanew);
		if (!ft_strcmp(get_pe_signature(pe), PE_SIGNATURE) && check_architecture_64(pe)) {
			replace_section(pe);
			return (save_pe(pe, famine));
		} else {
			return (false);
		}
	} else {
		return (false);
	}
}

/*
**	Read a PE file
*/
t_pe			*pe(t_famine *famine, char *folder_path, char *file_name, bool is_recursive)
{
	char		*file_path	= (is_recursive) ? folder_path : get_file_path(file_name, folder_path);
	t_pe		*pe_file	= alloc_pe(file_name, file_path);

	if (pe_file && pe_file->path) {
		open_pe_file(pe_file, famine);
		if (pe_file->buffer != NULL && pe_header(pe_file, famine) == true) {
			return (pe_file);
		}
	}
	return (NULL);
}
