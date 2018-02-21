/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 11:17:44 by golliet           #+#    #+#             */
/*   Updated: 2018/02/21 14:18:06 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdlib.h>
# include <termios.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <term.h>
# include <stdlib.h>
# include <sys/ioctl.h>

typedef struct	s_list
{
	char			*str; //la chaine
	int				len;   // la taille de la chaine
	int				lenmax; // la taille de la plus grande chaine
	int				state;  // l'etat de la chaine
	int				is_selected; // Est selectionne ou pas
	struct s_list	*next;
	struct s_list	*prev;
}				t_list;

int				g_lol;

typedef struct	s_cursor
{
	int			str_len;
	int			pos;
	int			line;
	int			col_term;
	int			line_term;
}				t_cursor;

void			ft_list(t_list **list, char **argv);
void			ft_display(t_list *list);
void			ft_display_selection(t_list *list);
void			ft_del_elem(t_list **list, t_list *trash);
void			ft_free_node(t_list *list);
void			ft_del(t_list *list, t_list **current, t_cursor *cursor);
void			ft_left_right(t_cursor *cursor, t_list **current, char *str);

#endif
