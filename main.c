/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:07:47 by golliet           #+#    #+#             */
/*   Updated: 2018/02/19 14:39:23 by golliet          ###   ########.fr       */
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
}

int		ft_toggle_raw(void)
{
	int				i;
	struct termios	term;
	char *env;

	i = 0;
	if (!(env = getenv("TERM")))
		return (-1);
	if (tgetent(NULL, env) == ERR)
		return (-1);
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

void	ft_init_cursor(t_cursor *cursor, int argc, t_list *list)
{
	struct winsize size;

	ioctl(0, TIOCGWINSZ, &size);
	cursor->str_len = argc * list->lenmax + (argc - 1);
	cursor->pos = 0;
	cursor->line = 0;
	cursor->col_term = size.ws_col;
	cursor->line_term = size.ws_row;
}

// fonction void qui met/enleve les soulignage

// fonction void qui met/enleve le surlignage

void	ft_left_right(t_cursor *cursor, t_list **current, char *str)
{
	(*current)->state = ((*current)->state == 1) ? (0) : (2);
	if (str[2] == 'C') //droite
	{
		cursor->pos = (cursor->pos + (*current)->lenmax + 1) % cursor->str_len;
		if ((*current)->next->len == -1)
		{
			(*current)->next->next->state = ((*current)->state == 0) ? (1) : (4);
			*current = (*current)->next->next;
		}
		else
		{
			(*current)->next->state = ((*current)->state == 0) ? (1) : (4);
			*current = (*current)->next;
		}
	}
	else if (str[2] == 'D') //gauche
	{
		cursor->pos = (cursor->pos - (*current)->lenmax + 1) % cursor->str_len;
		if ((*current)->prev->len == -1)
		{
			(*current)->prev->prev->state = ((*current)->state == 0) ? (1) : (4);
			*current = (*current)->prev->prev;
		}
		else
		{
			(*current)->prev->state = ((*current)->state == 0) ? (1) : (4);
			*current = (*current)->prev;
		}
	}
}

void	ft_detect_term(t_cursor *cursor, t_list **current, char *str)
{
	// SPACE -> ' '
	// LEFT -> ^[[D
	// RIGHT -> ^[[C
	// ECHAP -> 0x1b
	// DEL -> 0x7f
	// BACKSPACE -> ^[[3~
	if (str[0] == ' ' && str[1] == '\0')
		(*current)->state = ((*current)->state == 0) ? (2) : (3) ; //selectionne
	else if (str[0] == 0x7f && str[1] == '\0')
		ft_putendl("SUPR"); // Supprime selection
	else if (str[0] == 0x1b && str[1] == '\0')
		exit(0); //quitte programme /!\ free
	else if (ft_strncmp(str, "^[[", 3))
	{
		if (str[2] == 'D' || str[2] == 'C')
			ft_left_right(cursor, current, str);
		if (str[2] == '3')
			ft_putendl("delete"); // Supprime selection
	}
}

void	ft_read(t_list *list, int argc)
{
	int rd;
	char buf[6];
	t_list *current;
	t_cursor cursor;

	current = list;
	ft_init_cursor(&cursor, argc, list);
	ft_putstr("\r");
	ft_putstr("\x1b[?25l");
	while (42)
	{
		rd = 0;
		ft_bzero(buf, 0);
		while (rd < 2) 
		{
			rd = read(0, &buf, 5);
			buf[rd] = '\0';
			if (buf[0] == 0x1b || buf[0] == ' ' || buf[0] == 0x7f)
				break;
		}
		ft_detect_term(&cursor, &current, buf);
		// fonction termcaps

		// fonction refresh
		while (list->len != -1)
		{
			ft_display(list);
			list = list->next;
		}
		ft_putstr("\n");
		list = list->next;

		ft_putstr("\x1b[0k");
		ft_putstr("\x1b[1A");
	}
}

int main(int argc, char **argv)
{
	int i;
	t_list *list;

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
		list = list->next;
		list->state = 1;
		while (list->len != -1)
		{
			ft_display(list);
			list = list->next;
		}
			list = list->next;
		ft_read(list, argc);
	}
	return (0);
}
