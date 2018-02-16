/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:07:47 by golliet           #+#    #+#             */
/*   Updated: 2018/02/16 15:37:57 by golliet          ###   ########.fr       */
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

int main(int argc, char **argv)
{
	int i;
	t_list *list;
	int rd;
	char buf[5];

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
		while (42)
		{
			rd = 0;
			while (rd < 2)
				rd = read(0, &buf, 4);
			while (list->len != -1)
			{
				ft_display(list);
				list = list->next;
			}
			ft_putstr("\n");
			list = list->next;
			ft_putstr("\x1b[0K");
			ft_putstr("\x1b[1A");
		}
			//afficher les mots en fonction de leur struct
			//read
			//deplacer curseur et modifier structure
	}
	return (0);
}
