/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 13:11:09 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/26 13:11:59 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*ret;

	ret = NULL;
	if (size)
	{
		if ((ret = (void*)malloc(size)) == NULL)
			return (NULL);
		ft_memset(ret, 0, size);
	}
	return (ret);
}
