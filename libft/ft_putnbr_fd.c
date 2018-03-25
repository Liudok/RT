/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:25:32 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/27 15:32:47 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_num(unsigned int i, int fd)
{
	if (i / 10)
	{
		ft_put_num((i / 10), fd);
	}
	ft_putchar_fd((i % 10 + '0'), fd);
}

void		ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		ft_put_num(-nb, fd);
	}
	else
	{
		ft_put_num(nb, fd);
	}
}
