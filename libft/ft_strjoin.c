/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 13:59:13 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/28 14:00:04 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ret;

	ret = NULL;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	if (!(ret = (char *)malloc(sizeof(char *) * (len + 1))) || !s1 || !s2)
		return (NULL);
	ft_strcpy(ret, (char *)s1);
	ft_strcat(ret, (char *)s2);
	return (ret);
}
