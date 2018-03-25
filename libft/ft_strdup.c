/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 14:26:11 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/25 14:28:14 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	len = 0;
	while (src[i++] != '\0')
		len++;
	dup = (char*)malloc(sizeof(*dup) * (len + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (len > 0)
	{
		dup[i] = src[i];
		i++;
		len--;
	}
	dup[i] = '\0';
	return (&dup[0]);
}
