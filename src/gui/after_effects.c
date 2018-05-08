/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_effects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 11:20:17 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/08 11:20:19 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void		apply_after_effect(t_rt *rt, int i)
{
	if (rt->buttons[i].pressed)
		rt->effect_type = i % 15;
	if (i == 16)
	{
		rt->buttons[17].pressed = 0;
		rt->buttons[18].pressed = 0;
		rt->buttons[19].pressed = 0;
		rt->buttons[20].pressed = 0;
	}
	else if (i == 17)
	{
		rt->buttons[16].pressed = 0;
		rt->buttons[18].pressed = 0;
		rt->buttons[19].pressed = 0;
		rt->buttons[20].pressed = 0;
	}
	else if (i == 18)
	{
		rt->buttons[16].pressed = 0;
		rt->buttons[17].pressed = 0;
		rt->buttons[19].pressed = 0;
		rt->buttons[20].pressed = 0;
	}
	else
		apply_after_effect2(rt, i);
}

void		apply_after_effect2(t_rt *rt, int i)
{
	if (i == 19)
	{
		rt->buttons[16].pressed = 0;
		rt->buttons[17].pressed = 0;
		rt->buttons[18].pressed = 0;
		rt->buttons[20].pressed = 0;
	}
	else if (i == 20)
	{
		rt->buttons[16].pressed = 0;
		rt->buttons[17].pressed = 0;
		rt->buttons[18].pressed = 0;
		rt->buttons[19].pressed = 0;
	}
	clSetKernelArg(rt->effect_kernel.kernel, 2,
				   sizeof(cl_uchar), &rt->effect_type);
}
