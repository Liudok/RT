/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:29:46 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/27 14:30:39 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int len;

	len = ft_strlen((char*)s);
	s = s + len - 1;
	if ((char)c == 0)
		return ((char*)(s + 1));
	while (len)
	{
		if (*s == (char)c)
			return ((char*)s);
		--s;
		len--;
	}
	return (NULL);
}
