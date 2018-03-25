/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:08:25 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/26 13:09:10 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	ds;
	size_t	ss;

	ds = ft_strlen(dest);
	ss = ft_strlen(src);
	if (size)
	{
		i = 0;
		while (src[i] && (ds + i) < size - 1)
		{
			dest[ds + i] = src[i];
			i++;
		}
		dest[ds + i] = '\0';
	}
	if (ds < size)
		return (ds + ss);
	else
		return (size + ss);
}
