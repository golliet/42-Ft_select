/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 09:58:56 by golliet           #+#    #+#             */
/*   Updated: 2018/02/22 15:13:01 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft/libft.h"

void	sig_c(int n)
{
	ft_putstr("\x1b[?25h");
	//free
	exit(0);
}

void	sig_z(int n)
{
	struct termios term;

	g_cursor->global = 1;
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
}

int		ft_nb_line(int len, int col)
{
	int nb;

	nb = 1;
	while (len > col)
	{
		len = len / 2 + 10;
		nb++;
	}
	return (nb);
}

void	sig_w(int n)
{
	struct winsize size;
	static int a = 0;
	int i;

	i = ft_nb_line(g_cursor->str_len, g_cursor->col_term);
	ioctl(0, TIOCGWINSZ, &size);
	if (size.ws_col < 80)
	{
		ft_delete_line(i);
		int lol = -1;
		while (++lol < i)
			ft_putstr_fd("\x1b[1B", 0);
	}
	else
	{
		g_cursor->col_term = size.ws_col;
		g_cursor->line_term = size.ws_row;
		g_cursor->line = ft_nb_line(g_cursor->str_len, g_cursor->col_term);
		g_cursor->global = 1;
		g_cursor->str_len = g_cursor->argc * (g_cursor->lenmax + 5) + (g_cursor->argc - 1);
		ft_delete_line(i);
		ft_read_display(g_cursor->list);
	}
}
