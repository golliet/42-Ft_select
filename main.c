/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:07:47 by golliet           #+#    #+#             */
/*   Updated: 2018/02/23 13:19:48 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft/libft.h"

void	ft_larger(t_list **list)
{
	t_list *tmp;
	int larger;

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
	char *env;

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
	g_cursor->argc = argc;
	g_cursor->str_len = g_cursor->argc * (list->lenmax + 5) + (argc - 1);
	ft_calculate();
}

void	ft_current(t_list **current)
{
	if ((*current)->state == 1)
		(*current)->state = 0;
	else if ((*current)->state == 3)
		(*current)->state = 2;
	else
		(*current)->state = 2;
}

void	ft_left_right(t_list **current, char *str)
{
	ft_current(current);
	if (str[2] == 'C') //droite
	{
		if ((*current)->next->len == -1)
		{
			(*current)->next->next->state = ((*current)->next->next->state == 0) ? (1) : (3);
			*current = (*current)->next->next;
		}
		else
		{
			(*current)->next->state = ((*current)->next->state == 0) ? (1) : (3);
			*current = (*current)->next;
		}
	}
	else if (str[2] == 'D') //gauche
	{
		if ((*current)->prev->len == -1)
		{
			(*current)->prev->prev->state = ((*current)->prev->prev->state == 0) ? (1) : (3);
			*current = (*current)->prev->prev;
		}
		else
		{
			(*current)->prev->state = ((*current)->prev->state == 0) ? (1) : (3);
			*current = (*current)->prev;
		}
	}
}

void	ft_select_and_jump(t_list **current)
{
		if ((*current)->state == 1)
		{
			(*current)->state = 3;
			(*current)->is_selected = 1;
			ft_left_right(current, "^[C");
		}
		else if ((*current)->state == 3)
		{
			(*current)->state = 1;
			(*current)->is_selected = 0;
			ft_left_right(current, "^[C");
		}
}

void	ft_detect_term(t_list **current, char *str, t_list **list)
{
	if (str[0] == ' ' && str[1] == '\0')
		ft_select_and_jump(current);
	else if (str[0] == 0x7f && str[1] == '\0')
		ft_del(list, current);
	else if (str[0] == 0x1b && str[1] == '\0')
	{
		ft_putstr_fd("\x1b[?25h", 0);
		exit(0); //quitte programme /!\ free
	}
	else if (str[0] == '\n')
	{
		ft_display_selection(*list);
		ft_putstr_fd("\x1b[?25h", 0);
		exit(0);
	}
	else if (ft_strncmp(str, "^[[", 3))
	{
		if (str[2] == 'D' || str[2] == 'C')
			ft_left_right(current, str);
		if (str[2] == '3')
			ft_del(list, current);
	}
}

void	ft_delete_line(int n)
{
	int i;

	i = 1;
	while (i < n)
	{
		ft_putstr_fd("\r\x1b[2K", 0);
		ft_putstr_fd("\x1b[1A", 0);
		i++;
	}
	ft_putstr_fd("\r\x1b[2K", 0);
}

void	ft_read_display(t_list *list)
{
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

void	ft_read(t_list *list, int argc)
{
	int rd;
	char buf[6];
	t_list *current;

	current = list;
	//ft_putstr_fd("\x1b[?25l", 0);
	while (42)
	{
		rd = 0;
		g_cursor->list = list;
		while (rd < 2 && g_cursor->global == 0)
		{
			ft_bzero(buf, '\0');
			rd = read(0, &buf, 5);
			buf[rd] = '\0';
			if (buf[0] == 0x1b || buf[0] == ' ' || buf[0] == 0x7f || buf[0] == '\n')
				break;
		}
		if (g_cursor->global == 1)
			g_cursor->global = 0;
		else
			ft_detect_term(&current, buf, &list);
		ft_delete_line(g_cursor->line);
		ft_read_display(list);
	}
}

int main(int argc, char **argv)
{
	int i;
	t_list *list;

	g_cursor = malloc(sizeof(t_list));
	g_cursor->global = 0;
	signal(SIGINT, sig_c);
	signal(SIGWINCH, sig_w);
	signal(SIGCONT, sig_z);
	list = NULL;
	i = 0;
	if (argc > 1)
	{
		if (!(ft_toggle_raw()))
		{
			ft_putendl_fd("OSCOUR JEANNE !", 2);
			return (-1);
		}
		ft_list(&list, argv);
		ft_larger(&list);
		list->state = 1;
		ft_init_cursor(argc, list);
		ft_read_display(list);
		ft_read(list, argc);
	}
	return (0);
}
