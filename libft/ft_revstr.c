/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:15:18 by lberezyn          #+#    #+#             */
/*   Updated: 2017/11/01 14:15:21 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_revstr(char *str)
{
	size_t	i;
	size_t	k;
	size_t	z;
	char	*new;

	i = 0;
	if (!str)
		return (NULL);
	k = ft_strlen(str);
	new = ft_strnew(k);
	z = k - 1;
	while (i < k)
	{
		new[i] = str[z];
		i++;
		z--;
	}
	new[i] = '\0';
	return (new);
}
