/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:39:08 by golliet           #+#    #+#             */
/*   Updated: 2018/02/23 13:56:08 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
#include "libft/libft.h"

// free list

void	ft_free_node(t_list *list)
{
	free(list->str);
	free(list);
}

// rm elem
void	ft_del_elem(t_list **list, t_list *trash)
{
	while ((*list)->next != trash)
		*list = (*list)->next;
	(*list)->next = trash->next;
	(*list)->next->prev = trash->prev;
	ft_free_node(trash);
	while ((*list)->prev->len != -1)
		*list = (*list)->next;
}

// add elem
void	ft_add_elem(t_list **list, t_list *head, char *str)
{
	t_list *new;
	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return ;
	(*list)->next = new;
	new->prev = *list;
	new->next = head;
	new->state = 0;
	new->len = ft_strlen(str);
	new->str = ft_strdup(str);
	new->is_selected = 0;
}

// init
void	ft_init_list(t_list **list)
{
	if (!(*list = (t_list*)malloc(sizeof(t_list))))
		exit(EXIT_FAILURE);
	(*list)->str = NULL;
	(*list)->len = -1;
	(*list)->next = NULL;
	(*list)->prev = NULL;
	(*list)->lenmax = 0;
}

// une fonction qui check si le truc est vide, si oui alors init sinon addelem

void	ft_list(t_list **list, char **argv)
{
	t_list	*head;
	int		i;

	i = 0;
	ft_init_list(list); // init
	head = *list;
	while (argv[++i])
	{
		ft_add_elem(list, head,argv[i]);
		*list = (*list)->next;
		if (!argv[i + 1])
			head->prev = *list; // finir la boucle prev
	}
	*list = (*list)->next;
}
