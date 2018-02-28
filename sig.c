/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 09:58:56 by golliet           #+#    #+#             */
/*   Updated: 2018/02/28 13:23:32 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft/libft.h"

void	sig_z(int n)
{
	struct termios term;

	g_cursor->global = 1;
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSANOW, &term);
	write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));
	ft_putstr_fd("\x1b[?25l", 0);
	ft_display_multiple(g_cursor->list);
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
	struct winsize	size;
	int				i;

	i = g_cursor->line;
	ioctl(0, TIOCGWINSZ, &size);
	g_cursor->sizemax = (size.ws_col < g_cursor->lenmax + 20) ? 1 : 0;
	if (size.ws_col < (g_cursor->lenmax + 20))
		write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));
	else
	{
		g_cursor->col_term = size.ws_col;
		g_cursor->line_term = size.ws_row;
		ft_calculate();
		write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));
		ft_read_display(g_cursor->list);
	}
}

void	sig_tstp(int n)
{
	struct termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSANOW, &term);
	ft_putstr_fd("\x1b[?25h", 0);
	write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));
	ioctl(0, TIOCSTI, (char[2]) {term.c_cc[VSUSP], 0});
	signal(SIGTSTP, SIG_DFL);
}

void	ft_end()
{
	struct termios term;
	char  *name;

	if ((name = getenv("TERM")) == NULL)
		return ;
	if (tgetent(NULL, name) != 1)
		return ;
	if (tcgetattr(0, &term) == -1)
		return ;
	term.c_lflag &= ICANON;
	term.c_lflag &= ECHO;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return ;
	exit(EXIT_FAILURE);
}

void	sig_hdl(int s)
{
	if (s == SIGINT || s == SIGQUIT || s == SIGKILL || s == SIGTERM || s == SIGABRT || s == SIGSEGV)
	{
		ft_putstr_fd("\x1b[?25h", 0);
		write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));

		tcsetattr(0, TCSANOW, g_cursor->old_term);
		exit(1);
		//ft_end();
	}
	else if (s == SIGWINCH)
		sig_w(s);
	else if (s == SIGCONT)
	{
		sig_z(s);
		signal(SIGTSTP, sig_hdl);
	}
	else if (s == SIGTSTP)
		sig_tstp(s);
}
