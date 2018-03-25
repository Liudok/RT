/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 12:51:31 by lberezyn          #+#    #+#             */
/*   Updated: 2018/01/09 12:51:34 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpushback(t_list **alst, t_list *new)
{
	t_list *begin;

	begin = *alst;
	if (begin)
	{
		while ((begin)->next)
			(begin) = (begin)->next;
		(begin)->next = new;
	}
	else
		*alst = new;
}
