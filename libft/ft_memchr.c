/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 10:51:24 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/27 11:01:18 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char *temp;

	temp = (char*)s;
	while (n--)
	{
		if (*temp == (char)c)
		{
			return ((void *)temp);
		}
		temp++;
	}
	return (NULL);
}
