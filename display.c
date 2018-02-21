/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:59:25 by golliet           #+#    #+#             */
/*   Updated: 2018/02/21 16:22:10 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft/libft.h"

#define STOP "\033[0m"
#define NORMAL_UNDER "\033[4m"
#define HIGHLIGHTED "\033[40;7m"
#define HIGH_UNDER "\033[40;7;4m"
#define BLUE "\033[34;1m"
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

	if (ft_strlen(list->str) == 0)
		return ;
	ft_putstr_fd(BLUE, 0);
	ft_putstr_fd("[> ", 0);
	ft_putstr_fd(STOP, 0);
	i = list->len - 1;
	if (list->state == 1)
		ft_putstr_fd(NORMAL_UNDER, 0);
	else if (list->state == 2)
		ft_putstr_fd(HIGHLIGHTED, 0);
	else if (list->state == 3)
		ft_putstr_fd(HIGH_UNDER, 0);
	ft_putstr_fd(LBLUE, 0);
	ft_putstr_fd(list->str, 0);
	while (++i < list->lenmax)
		ft_putchar_fd(' ', 0);
	ft_putstr_fd(STOP, 0);
	ft_putstr_fd(BLUE, 0);
	ft_putstr_fd("]", 0);
	ft_putstr_fd(STOP, 0);
	ft_putstr_fd(" ", 0);
}
