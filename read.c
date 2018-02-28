/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:59:54 by golliet           #+#    #+#             */
/*   Updated: 2018/02/28 14:14:27 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_select.h"

static void		ft_select_and_jump(t_list **current)
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

static void		ft_detect_term(t_list **current, char *str, t_list **list)
{
	if (str[0] == ' ' && str[1] == '\0')
		ft_select_and_jump(current);
	else if (str[0] == 0x7f && str[1] == '\0')
		ft_del(list, current);
	else if (str[0] == 0x1b && str[1] == '\0')
		ft_exit();
	else if (str[0] == '\n')
	{
		ft_putstr_fd("\x1b[?25h", 0);
		write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));
		ft_display_selection(*list);
		tcsetattr(0, TCSANOW, g_cursor->old_term);
		exit(1);
	}
	else if (ft_strncmp(str, "^[[", 3))
	{
		if (str[2] == 'D' || str[2] == 'C')
			ft_left_right(current, str);
		if (str[2] == '3')
			ft_del(list, current);
	}
}

static void		ft_launch(t_list **current, char *b, t_list **list)
{
	ft_detect_term(current, b, list);
	ft_read_display(*list);
}

void			ft_exit(void)
{
	ft_putstr_fd("\x1b[?25h", 0);
	write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));
	tcsetattr(0, TCSANOW, g_cursor->old_term);
	exit(1);
}

void			ft_read(t_list *list, int argc)
{
	int			rd;
	char		b[6];
	t_list		*current;

	current = list;
	while (42)
	{
		rd = 0;
		g_cursor->list = list;
		while (rd < 2)
		{
			ft_bzero(b, '\0');
			rd = read(0, &b, 5);
			if (g_cursor->global == 1)
			{
				g_cursor->global = 0;
				continue;
			}
			b[rd] = '\0';
			if (b[0] == 0x1b || b[0] == ' ' || b[0] == 0x7f || b[0] == '\n')
				break ;
		}
		ft_launch(&current, b, &list);
	}
}
