/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:05:22 by frmarinh          #+#    #+#             */
/*   Updated: 2017/07/01 18:07:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <stdio.h>
# include <locale.h>
# include <windows.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/includes/libft.h"

# define APP_ENV	"APPDATA"
# define TEMP_PATH	"\\Local\\Temp"
# define BACKSLASH	"\\"
# define DEBUG_MODE	"DEBUG"
# define bool		int
# define true		1
# define false		0
# define NO_FLAGS	0
# define EXIT_CODE	-1

#ifndef _WINDEF_
	# define _WINDEF_
	/*
	**	Variable type definition
	*/
	typedef unsigned long       DWORD;
	typedef int                 BOOL;
	typedef unsigned char       BYTE;
	typedef unsigned short      WORD;
	typedef float               FLOAT;
	typedef FLOAT               *PFLOAT;
	typedef BOOL near           *PBOOL;
	typedef BOOL far            *LPBOOL;
	typedef BYTE near           *PBYTE;
	typedef BYTE far            *LPBYTE;
	typedef int near            *PINT;
	typedef int far             *LPINT;
	typedef WORD near           *PWORD;
	typedef WORD far            *LPWORD;
	typedef long far            *LPLONG;
	typedef DWORD near          *PDWORD;
	typedef DWORD far           *LPDWORD;
	typedef void far            *LPVOID;
	typedef CONST void far      *LPCVOID;
	typedef void                *HANDLE;
	typedef int                 INT;
	typedef unsigned int        UINT;
	typedef unsigned int        *PUINT;
	typedef UINT_PTR            WPARAM;
	typedef LONG_PTR            LPARAM;
	typedef LONG_PTR            LRESULT;

	/*
	**	PE Header (DOS Header)
	*/
	typedef struct	_IMAGE_DOS_HEADER
	{
		WORD	 	e_magic;
		WORD 		e_cblp;
		WORD 		e_cp;
		WORD 		e_crlc;
		WORD 		e_cparhdr;
		WORD 		e_minalloc;
		WORD 		e_maxalloc;
		WORD 		e_ss;
		WORD 		e_sp;
		WORD 		e_csum;
		WORD 		e_ip;
		WORD 		e_cs;
		WORD 		e_lfarlc;
		WORD 		e_ovno;
		WORD 		e_res[4];
		WORD	 	e_oemid;
		WORD 		e_oeminfo;
		WORD 		e_res2[10];
		LONG		 e_lfanew;
	}				IMAGE_DOS_HEADER;

#endif

typedef struct		s_pe
{
	char			*name;
	char			*path;
	int				len;
	char			*buffer;
}					t_pe;

typedef struct		s_famine
{
	char			*path;
	bool			debug;
}					t_famine;

/*
**	MAIN
*/
void				close_console();
void				start_debug_console();

/*
**	UTILS
*/
void				*ft_mmap(int fd, size_t size);
void				print_message(t_famine *famine, char *message, bool leave);

/*
**	FAMINE
*/
void				init_famine(int, char**);

/*
**	INFECTION
*/
void				infect_folder(t_famine *famine, char *folder_name);

/*
**	ACCESS FILE
*/
struct stat			*check_access_file(char *file, t_famine *famine);

/*
**	READ PE
*/
t_pe				*pe(t_famine *famine, char *folder_path, char *file_name);
#endif
