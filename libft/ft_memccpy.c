/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 10:28:12 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/27 10:36:19 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dst;
	unsigned char	*sor;

	dst = (unsigned char *)dest;
	sor = (unsigned char *)src;
	while (n--)
	{
		*(unsigned char *)dst = *(unsigned char *)sor;
		dst++;
		if (*(unsigned char *)sor == (unsigned char)c)
			return (dst);
		sor++;
	}
	return (NULL);
}
