/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:07:47 by golliet           #+#    #+#             */
/*   Updated: 2018/02/15 16:40:13 by golliet          ###   ########.fr       */
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

int main(int argc, char **argv)
{
	int i;
	t_list *list;

	list = NULL;
	i = 0;
	if (argc > 1)
	{
		ft_list(&list, argv);
		ft_larger(&list);
		list = list->next;
		while (list->len != -1)
		{
			ft_display(list);
			list = list->next;
			//afficher les mots en fonction de leur struct
			//read
			//deplacer curseur et modifier structure
		}
			ft_putstr("\n");
	}
	return (0);
}
