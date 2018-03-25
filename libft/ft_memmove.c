/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:04:04 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/26 13:06:19 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	void	*res;

	res = dst;
	if (dst < src)
		while (n--)
			*(unsigned char *)(dst++) = *(unsigned char *)(src++);
	else
	{
		dst += n;
		src += n;
		while (n--)
		{
			*(unsigned char *)(--dst) = *(unsigned char *)(--src);
		}
	}
	return (res);
}
