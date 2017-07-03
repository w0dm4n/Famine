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
# include "../libft/includes/libft.h"

# define APP_ENV	"APPDATA"
# define TEMP_PATH	"\\Local\\Temp"
# define DEBUG_MODE	"DEBUG"
# define bool		int
# define true		1
# define false		0

typedef struct		s_famine
{
	char			*path;
	bool			debug;
}					t_famine;

/*
**	MAIN
*/
void				close_console();

/*
**	FAMINE
*/
void				init_famine(int, char**);

#endif
