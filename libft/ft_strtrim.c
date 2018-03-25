/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:16:56 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/28 14:17:00 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_white(char c)
{
	if (c == '\n' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

static size_t	ft_delim_counter(const char *stroka)
{
	size_t		count;

	count = 0;
	if (ft_is_white(*stroka))
	{
		while (ft_is_white(*stroka) && *stroka != '\0')
		{
			stroka++;
			count++;
		}
	}
	return (count);
}

static size_t	ft_sym_counter(const char *stroka)
{
	size_t		count;

	count = 0;
	if (stroka)
	{
		while (*stroka != '\0')
		{
			stroka++;
			count++;
		}
		stroka--;
		while (ft_is_white(*stroka))
		{
			stroka--;
			count--;
		}
	}
	return (count);
}

char			*ft_strtrim(char const *s)
{
	char		*ret;
	char		*final;
	size_t		delim;
	size_t		len;

	if (!s)
		return (NULL);
	delim = ft_delim_counter(s);
	s = s + delim;
	if (*s == '\0')
		return ((char *)ft_strnew(1));
	len = ft_sym_counter(s);
	s = s + len;
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	final = ret;
	s = s - len;
	while (len--)
	{
		*ret = *s;
		ret++;
		s++;
	}
	*ret = '\0';
	return (final);
}
