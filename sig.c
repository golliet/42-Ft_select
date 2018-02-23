/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 09:58:56 by golliet           #+#    #+#             */
/*   Updated: 2018/02/23 13:20:27 by golliet          ###   ########.fr       */
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
		g_cursor->global = 1;
		ft_calculate();
		ft_delete_line(i);
		ft_read_display(g_cursor->list);
		//printf("lignes : %d\n", g_cursor->line);
	}
}
