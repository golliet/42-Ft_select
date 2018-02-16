/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 10:29:42 by golliet           #+#    #+#             */
/*   Updated: 2017/11/14 16:20:05 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char		*source;
	char			*dest;

	if (n != 0)
	{
		dest = (char*)dst;
		source = (char*)src;
		while (n > 0)
		{
			*dest = *source;
			dest++;
			source++;
			n--;
		}
	}
	return (dst);
}
