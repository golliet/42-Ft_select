/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 13:18:20 by golliet           #+#    #+#             */
/*   Updated: 2018/02/26 13:23:05 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_select.h"

static void		ft_current(t_list **current)
{
	if ((*current)->state == 1)
		(*current)->state = 0;
	else if ((*current)->state == 3)
		(*current)->state = 2;
	else
		(*current)->state = 2;
}

static void		ft_right(t_list **c)
{
	if ((*c)->next->len == -1)
	{
		(*c)->next->next->state = (*c)->next->next->state == 0 ? (1) : (3);
		*c = (*c)->next->next;
	}
	else
	{
		(*c)->next->state = ((*c)->next->state == 0) ? (1) : (3);
		*c = (*c)->next;
	}
}

static void		ft_left(t_list **c)
{
	if ((*c)->prev->len == -1)
	{
		(*c)->prev->prev->state = (*c)->prev->prev->state == 0 ? (1) : (3);
		*c = (*c)->prev->prev;
	}
	else
	{
		(*c)->prev->state = ((*c)->prev->state == 0) ? (1) : (3);
		*c = (*c)->prev;
	}
}

void			ft_left_right(t_list **c, char *str)
{
	ft_current(c);
	if (str[2] == 'C')
		ft_right(c);
	else if (str[2] == 'D')
		ft_left(c);
}
