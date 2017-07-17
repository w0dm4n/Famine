/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/01 18:05:22 by frmarinh          #+#    #+#             */
/*   Updated: 2017/07/01 18:07:34 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

/*
**	Print the message if famine is on DEBUG_MODE
*/
void				print_message(t_famine *famine, char *message)
{
	if (famine->debug == true) {
		printf("%s\n", message);
	}
}

/*
**	Hide and close the current terminal
*/
void				close_console()
{
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_MINIMIZE);
	ShowWindow(hWnd, SW_HIDE);
	FreeConsole();
}

/*
**	Start a new console and relink file descriptor 0, 1, 2
**	then resizing window 300x600 to position x(100) y(100) and disabling resizing
*/
void				start_debug_console()
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	HWND hWnd = GetConsoleWindow();
	if (hWnd) {
		SetWindowPos(hWnd, 0, 100, 100, 300, 600, NO_FLAGS);
		SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) &~ WS_SIZEBOX);
	}
}


/*
**	Main entry point
*/
int					main(int argc, char **argv)
{
	setlocale(LC_CTYPE, "");
	init_famine(argc, argv);
}
