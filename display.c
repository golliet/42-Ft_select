/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:59:25 by golliet           #+#    #+#             */
/*   Updated: 2018/02/20 12:21:11 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft/libft.h"

#define STOP "\033[0m"
#define NORMAL_UNDER "\033[4m"
#define HIGHLIGHTED "\033[40;7m"
#define HIGH_UNDER "\033[40;7;4m"

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

	i = list->len - 1;
	if (list->state == 1)
		write(0, NORMAL_UNDER, 4);
	else if (list->state == 2)
		write(0, HIGHLIGHTED, 7);
	else if (list->state == 3)
		write(0, HIGH_UNDER, 9);
	ft_putstr_fd(list->str, 0);
	while (++i < list->lenmax)
		ft_putchar_fd(' ', 0);
	write(0, STOP, 4);
	ft_putstr_fd(" ", 0);
}

/*
** 4 color
** -> normal						: 0
** -> normal and underlined			: 1
** -> highlighted					: 2
** -> highlighted and underlined	: 3
*/
