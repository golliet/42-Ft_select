/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: golliet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:45:56 by golliet           #+#    #+#             */
/*   Updated: 2017/11/14 16:20:30 by golliet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long int h;

	h = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		h = -h;
	}
	if (h >= 10)
	{
		ft_putnbr_fd(h / 10, fd);
		ft_putchar_fd(h % 10 + 48, fd);
	}
	else
		ft_putchar_fd(h + '0', fd);
}
