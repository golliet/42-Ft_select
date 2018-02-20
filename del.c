/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 12:29:25 by golliet           #+#    #+#             */
/*   Updated: 2018/02/20 14:55:44 by golliet          ###   ########.fr       */
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

void		ft_del(t_list *list, t_list **current, t_cursor *cursor)
{
	t_list *tmp;

	if (ft_empty_list(list) == 0)
		exit(0);
	tmp = (*current)->next;
	ft_del_elem(&list, *current);
	if ((*current)->next->len != -1)
		ft_left_right(cursor, current, "^[C");
	else
		ft_left_right(cursor, current, "^[D");
	ft_putstr("\x1b[0J");
}
