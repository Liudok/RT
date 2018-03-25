/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:00:58 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/24 18:34:21 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char *dest;

	dest = destination;
	while (n--)
	{
		*(unsigned char*)destination = (unsigned char)c;
		destination++;
	}
	return (dest);
}
