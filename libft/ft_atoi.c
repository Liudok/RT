/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 18:41:26 by lberezyn          #+#    #+#             */
/*   Updated: 2017/10/24 18:47:47 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int						ft_atoi(const char *str)
{
	unsigned long int	nb;
	int					i;
	int					sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\v' || str[i] == '\f' ||
		str[i] == '\r' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb >= 9223372036854775807 && sign == 1)
			return (-1);
		else if (nb > 9223372036854775807 && sign == -1)
			return (0);
		i++;
	}
	return ((int)(nb * sign));
}
