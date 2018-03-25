/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 12:49:30 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/28 12:52:42 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	mylen;
	char	*ret;
	size_t	i;

	ret = NULL;
	if (!s)
		return (0);
	mylen = ft_strlen((char *)s);
	i = 0;
	if (mylen == 0 || mylen < len || !(ret = (char *)malloc(len + 1)) ||
		mylen < start)
		return (NULL);
	while (i < len)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (&ret[0]);
}
