/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:03:50 by golliet           #+#    #+#             */
/*   Updated: 2017/11/13 10:47:58 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	if (*s1 == '\0' && *s2 == '\0')
		return (0);
	while ((*s1 == *s2) && (*s2 && *s1) && (i < n - 1))
	{
		s1++;
		s2++;
		i++;
	}
	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}
