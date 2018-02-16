/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:49:48 by golliet           #+#    #+#             */
/*   Updated: 2017/11/14 16:19:53 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_rank(int n)
{
	int i;

	i = (ft_isnegativ(n)) ? 2 : 1;
	while (n /= 10)
		i++;
	return (i);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		cpy;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	cpy = n;
	len = ft_count_rank(n);
	if (ft_isnegativ(n))
		cpy = -n;
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	len--;
	while (len >= 0)
	{
		str[len] = '0' + cpy % 10;
		cpy /= 10;
		len--;
	}
	if (ft_isnegativ(n))
		str[0] = '-';
	return (str);
}
