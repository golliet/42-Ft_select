/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:07:47 by golliet           #+#    #+#             */
/*   Updated: 2018/02/26 13:19:32 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft/libft.h"

void	ft_larger(t_list **list)
{
	t_list	*tmp;
	int		larger;

	larger = 0;
	tmp = *list;
	while ((tmp = tmp->next) && tmp->len != -1)
		if (tmp->len > larger)
			larger = tmp->len;
	while ((tmp = tmp->next) && tmp->len != -1)
		tmp->lenmax = larger;
	*list = (*list)->next;
}

int		ft_toggle_raw(void)
{
	int				i;
	struct termios	term;
	char			*env;

	if (!(env = getenv("TERM")))
	{
		env = ft_strdup("xterm-256color");
		i = 1;
	}
	if (tgetent(NULL, env) == ERR)
		return (-1);
	if (i == 1)
		free(env);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (1);
}

void	ft_init_cursor(int argc, t_list *list)
{
	struct winsize size;

	ioctl(0, TIOCGWINSZ, &size);
	g_cursor->lenmax = list->lenmax;
	g_cursor->col_term = size.ws_col;
	g_cursor->line_term = size.ws_row;
	g_cursor->sizemax = (size.ws_col <= g_cursor->lenmax + 15) ? 1 : 0;
	g_cursor->argc = argc;
	g_cursor->str_len = g_cursor->argc * (list->lenmax + 5) + (argc - 1);
	ft_calculate();
}

void	ft_read_display(t_list *list)
{
	write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));
	ft_putstr_fd("\x1b[?25l", 0);
	if (g_cursor->line == 1)
	{
		while (list->len != -1)
		{
			ft_display(list);
			list = list->next;
		}
		list = list->next;
	}
	else
		ft_display_multiple(list);
}

int		main(int argc, char **argv)
{
	int		i;
	t_list	*list;

	g_cursor = malloc(sizeof(t_list));
	g_cursor->global = 0;
	signal(SIGINT, sig_c);
	signal(SIGWINCH, sig_w);
	signal(SIGCONT, sig_z);
	signal(SIGTSTP, sig_tstp);
	list = NULL;
	i = 0;
	if (argc > 1)
	{
		ft_toggle_raw();
		write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));
		ft_list(&list, argv);
		ft_larger(&list);
		list->state = 1;
		ft_init_cursor(argc, list);
		ft_read_display(list);
		ft_read(list, argc);
	}
	return (0);
}
