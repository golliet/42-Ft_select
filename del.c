/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:29:25 by golliet           #+#    #+#             */
/*   Updated: 2018/02/23 13:10:41 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft/libft.h"

static int	ft_empty_list(t_list *list)
{
	t_list *tmp;
	int i;

	i = 0;
	tmp = list;
	while (tmp->next->len != -1)
	{
		i++;
		tmp = tmp->next;
	}
	return ((i == 0) ? (0) : (1) );
}

void		ft_del(t_list **list, t_list **current)
{
	if (ft_empty_list(*list) == 0)
	{
		ft_putstr_fd("\x1b[?25h", 0);
		exit(0);
	}
	if ((*current)->len != -1)
		ft_del_elem(list, *current);
	if ((*current)->next->len != -1)
		ft_left_right(current, "^[C");
	else
		ft_left_right(current, "^[D");
	ft_putstr_fd("\x1b[0J", 0);
	g_cursor->argc -= 1;
	ft_calculate();
}
