/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:17:44 by golliet           #+#    #+#             */
/*   Updated: 2018/02/15 16:15:15 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
# define FT_SELECT

# include <stdlib.h>

typedef struct s_list
{
	char			*str; //la chaine
	int				len;   // la taille de la chaine
	int				lenmax; // la taille de la plus grande chaine
	int				state;  // l'etat de la chaine
	struct s_list	*next;
	struct s_list	*prev;
} t_list;

void	ft_list(t_list **list, char **argv);
void	ft_display(t_list *list);

#endif
