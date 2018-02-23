/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:59:25 by golliet           #+#    #+#             */
/*   Updated: 2018/02/23 14:16:15 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft/libft.h"

#define STOP "\033[0m"
#define NORMAL_UNDER "\033[4m"
#define HIGHLIGHTED "\033[40;7m"
#define HIGH_UNDER "\033[40;7;4m"
#define LBLUE "\033[36m"

/*
** 4 color
** -> normal						: 0
** -> normal and underlined			: 1
** -> highlighted					: 2
** -> highlighted and underlined	: 3
*/

void	ft_display_selection(t_list *list)
{
	write(0, tgetstr("cl", 0), ft_strlen(tgetstr("cl", 0)));
	while (list->len != -1)
	{
		if (list->is_selected == 1)
		{
			ft_putstr(list->str);
			ft_putchar(' ');
		}
		list = list->next;
	}
}

void	ft_display(t_list *list)
{
	int i;

	if (list->str == NULL || list->len == -1)
		return ;
	ft_putstr_fd("\033[34;1m[> \033[0m", 0);
	i = list->len - 1;
	if (list->state == 1)
		ft_putstr_fd(NORMAL_UNDER, 0);
	else if (list->state == 2)
		ft_putstr_fd(HIGHLIGHTED, 0);
	else if (list->state == 3)
		ft_putstr_fd(HIGH_UNDER, 0);
	ft_putstr_fd(LBLUE, 0);
	while (list->lenmax > 0 && ++i < list->lenmax)
		ft_putchar_fd(' ', 0);
	ft_putstr_fd(list->str, 0);
	ft_putstr_fd(STOP, 0);
	ft_putstr_fd("\033[34;1m] \033[0m", 0);
}

/*void	ft_display_multiple(t_list *list)
{
	int l;
	int j;
	int k;
	t_list *head;

	j = 0;
	while (j < g_cursor->line)
	{
		l = 1;
		k = 1;
		head = list;
		l += j;
		while (l <= g_cursor->argc - 1)
		{
			while (head->len != -1 && k != l)
			{
				head = head->next;
				k++;
			}
			ft_display(head);
			l += g_cursor->line;
		}
		ft_putchar_fd('\n', 0);
		j++;
	}
}*/

/*
** Function who will calculate number of word in one row, and number of row
*/

int		ft_round(double a)
{
	int b;

	b = a;
	//printf("a: %f b:%d\n", a,b);
	if (a - b > 0)
		return (b + 1);
	else if (a - b == 0)
		return (b);
	else
		return (0);
}

void	ft_calculate(void)
{
	int i;

	i = 0;
	while ((i * (g_cursor->lenmax + 5)) < g_cursor->col_term - 20)
		i++;
	g_cursor->line = ft_round((double)g_cursor->argc / ((double)i));
	//printf("line :%d\n", g_cursor->line);
	g_cursor->nb_word_line = i;
}

void	ft_display_multiple(t_list *list)
{
	int i;

	i = 0;
	while (list->len != -1)
	{
		ft_display(list);
		if ((i + 1) % g_cursor->nb_word_line == 0)
			ft_putchar_fd('\n', 0);
		list = list->next;
		i++;
	}
}
