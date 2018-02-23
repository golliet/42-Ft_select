/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 09:58:56 by golliet           #+#    #+#             */
/*   Updated: 2018/02/23 14:13:45 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft/libft.h"

void	sig_c(int n)
{
	ft_putstr_fd("\x1b[?25h", 0);
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
	int i;

	i = g_cursor->line;
	ioctl(0, TIOCGWINSZ, &size);
	if (size.ws_col < (g_cursor->lenmax + 5) * 2)
		write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));
	else
	{
		g_cursor->col_term = size.ws_col;
		g_cursor->line_term = size.ws_row;
		g_cursor->global = 1;
		ft_calculate();
		write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));
		ft_read_display(g_cursor->list);
	}
}
