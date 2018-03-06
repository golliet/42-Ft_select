/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:07:47 by golliet           #+#    #+#             */
/*   Updated: 2018/03/01 13:54:41 by golliet          ###   ########.fr       */
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
	struct termios	term;
	char			*env;

	if (!(env = getenv("TERM")))
		exit(EXIT_FAILURE);
	if (ft_strlen(env) == 0)
		exit(EXIT_FAILURE);
	if (tgetent(NULL, env) != 1)
		exit(EXIT_FAILURE);
	if (tcgetattr(0, &term) == -1)
		exit(EXIT_FAILURE);
	g_cursor->old_term = (struct termios *)malloc(sizeof(struct termios));
	if (tcgetattr(0, g_cursor->old_term) == -1)
		exit(EXIT_FAILURE);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSANOW, &term) == -1)
		exit(EXIT_FAILURE);
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
	int		j;

	if (argc > 1)
	{
		j = 0;
		while (j < 32)
			signal(j++, sig_hdl);
		g_cursor = malloc(sizeof(t_list));
		g_cursor->global = 0;
		list = NULL;
		i = 0;
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
