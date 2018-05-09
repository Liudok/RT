/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pressing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberezyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 10:51:57 by lberezyn          #+#    #+#             */
/*   Updated: 2018/05/08 10:52:00 by lberezyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/panels.h"

void		button_pressed(t_rt *s, int i)
{
	if (s->buttons[i].pressed == 0)
	{
		if (i == 0)
			file_choosing(s);
		else if (i == 3)
			save_scene_to_png(s);
		else if (i == 15 && s->buttons[1].pressed)
			save_scene_to_file(s);
		else
		{
			s->buttons[i].pressed = 1;
			if (i > 3 && i < 16 && s->buttons[1].pressed
				&& s->buttons[i].pressed)
				modify_scene(s, i);
			if (i >= 16 && i < 21 && s->buttons[2].pressed
				&& s->buttons[i].pressed)
				apply_after_effect(s, i);
		}
	}
	else
	{
		s->buttons[i].pressed = 0;
		if (i >= 16 && i < 21 && s->buttons[2].pressed)
			s->effect_type = 0;
	}
}

void		check_pressing(t_rt *s, int x, int y)
{
	int		i;
	int		fig;

	i = -1;
	while (++i < BUTTONS_AMOUNT)
	{
		if (within_rect(s->buttons[i].rect, x, y))
		{
			button_pressed(s, i);
			return ;
		}
	}
	fig = mouse_ray(s, x, y);
	if (fig > 0)
	{
		printf("\nfigure = %i\n", fig);
		start_settings_win(s, fig);
	}
}

int			check_pressing_setting(int prop, t_rec *recs, int x, int y)
{
	int		i;

	i = -1;
	while (++i < prop)
	{
		if (within_rect(recs[i].rect, x, y))
			return (i);
	}
	return (-1);
}

int			this_figure_props(t_obj_type type)
{
	if (type == 0)
		return (24);
	else if (type == 1 || type == 10)
		return (26);
	else if (type == 2 || type == 5)
		return (28);
	else if (type == 3)
		return (29);
	else if (type == 4)
		return (27);
	else if (type == 6)
		return (29);
	else if (type == 7)
		return (22);
	else
		return (0);
}

int			this_figure_small_props(t_obj_type type)
{
	if (type == 0 || type == 10)
		return (7);
	else if (type == 1 || type == 7)
		return (7);
	else if (type == 2 || type == 5)
		return (9);
	else if (type == 3)
		return (10);
	else if (type == 4)
		return (8);
	else if (type == 6)
		return (8);
	else
		return (0);
}
