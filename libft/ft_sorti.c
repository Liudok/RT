/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 13:53:31 by lberezyn          #+#    #+#             */
/*   Updated: 2017/11/01 13:54:12 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_sorti(int *arr, int n)
{
	int i;
	int k;

	i = 0;
	if (!arr)
		return (NULL);
	while (i < n)
	{
		k = 0;
		while (k < n)
		{
			if (arr[i] < arr[k])
				ft_swapi(&arr[i], &arr[k]);
			k++;
		}
		i++;
	}
	return (arr);
}
