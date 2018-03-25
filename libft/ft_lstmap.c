/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:59:41 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/30 15:59:45 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*temp;

	ret = NULL;
	if (lst && f)
	{
		while (lst)
		{
			if (ret == NULL)
			{
				ret = (*f)(lst);
				temp = ret;
			}
			else
			{
				temp->next = (*f)(lst);
				temp = temp->next;
			}
			lst = lst->next;
		}
	}
	return (ret);
}
