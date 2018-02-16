/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 11:30:09 by golliet           #+#    #+#             */
/*   Updated: 2018/01/26 10:16:57 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <unistd.h>
#include <limits.h>
#define S str[fd]
#define X '\n'

int				get_next_line(const int fd, char **line)
{
	int			rd;
	char		buf[BUFF_SIZE + 1];
	static char *str[OPEN_MAX];
	char		*cpy;

	if (!line || fd < 0 || !(S = S ? S : ft_strnew(1)))
		return (-1);
	while (!ft_strchr(S, X) && (rd = read(fd, buf, BUFF_SIZE)) != 0)
	{
		if (rd == ((buf[rd] = '\0') - 1))
			return (-1);
		cpy = ft_strjoin(S, buf);
		free(S);
		S = cpy;
	}
	*line = (ft_strchr(S, X) ? ft_strsub(S, 0,
				ft_strchr(S, X) - S) : ft_strdup(S));
	if (ft_strchr(cpy = S, X))
	{
		S = ft_strsub(S, ft_strchr(S, X) - S + 1, ft_strlen(S));
		free(cpy);
	}
	else
		ft_strdel(&S);
	return (!S && ft_strlen(*line) == 0 ? 0 : 1);
}
