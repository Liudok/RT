/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 14:50:17 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/28 14:50:29 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_counter(const char *stroka, char c)
{
	int			i;
	int			z;
	int			count;

	if (!stroka)
		return (0);
	i = 0;
	count = 0;
	while (stroka[i] != '\0')
	{
		z = i - 1;
		if (stroka[i] != c && stroka[i + 1] == '\0')
			count++;
		if (stroka[i] != c)
			i++;
		else if (stroka[z] != c && z >= 0)
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static size_t	ft_delim_counter(const char *stroka, char c)
{
	size_t		count;

	count = 0;
	if (*stroka == c)
	{
		while (*stroka == c && *stroka != '\0')
		{
			stroka++;
			count++;
		}
	}
	return (count);
}

static size_t	ft_sym_counter(const char *stroka, char c)
{
	size_t		count;

	count = 0;
	while (*stroka == c)
	{
		stroka++;
	}
	while (*stroka != c && *stroka != '\0')
	{
		stroka++;
		count++;
	}
	return (count);
}

static char		*ft_filler(char *ret, const char *src, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		ret[i] = src[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**ret;
	size_t		k;
	size_t		i;
	size_t		delim;
	size_t		len;

	i = 0;
	ret = NULL;
	k = ft_counter(s, c);
	if (!(ret = (char **)malloc(sizeof(char **) * (k + 1))))
		return (NULL);
	if (k)
		while (i <= k - 1)
		{
			delim = ft_delim_counter(s, c);
			len = ft_sym_counter(s, c);
			if (!(ret[i] = (char *)malloc(sizeof(char *) * (len + 1))))
				return (NULL);
			s = s + delim;
			ret[i] = ft_filler(ret[i], s, len);
			s = s + len;
			i++;
		}
	ret[k] = NULL;
	return (ret);
}
