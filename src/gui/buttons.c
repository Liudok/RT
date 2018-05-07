
#include "../../include/panels.h"

void set_icons(t_rt *s)
{
	s->icon = (char **)malloc(sizeof(char *) * BUTTONS_AMOUNT);
	s->icon[0] = "src/icons/find.png";
	s->icon[1] = "src/icons/settings.png";
	s->icon[2] = "src/icons/path.png";
	s->icon[3] = "src/icons/render.png";
	s->icon[4] = "src/icons/sphere.png";
	s->icon[5] = "src/icons/planes.png";
	s->icon[6] = "src/icons/cyli.png";
	s->icon[7] = "src/icons/cones.png";
	s->icon[8] = "src/icons/disk.png";
	s->icon[9] = "src/icons/icon.png";
	s->icon[10] = "src/icons/tria.png";
	s->icon[11] = "src/icons/cubes.png";
	s->icon[12] = "src/icons/spotlight.png";
	s->icon[13] = "src/icons/sun-2.png";
	s->icon[14] = "src/icons/create_file.png";
	s->icon[15] = "src/icons/find_in.png";
	s->icon[16] = "src/icons/blur.png";
	s->icon[17] = "src/icons/negative.png";
	s->icon[18] = "src/icons/sepia.png";
	s->icon[19] = "src/icons/cartoon.png";
	s->icon[20] = "src/icons/chb.png";

}

void			create_buttons(t_rt *s)
{
	int i;

	i = 0;
	set_icons(s);
	while (i < BUTTONS_AMOUNT)
	{
		s->buttons[i].pressed = 0;
		s->buttons[i].name = i;
		if (i < 4)
			s->buttons[i].rect = make_rect((10 + i * 20), 10, BUTTON_SIZE, BUTTON_SIZE);
		s->buttons[i].txt = load_texture(s->icon[i], s);
		i++;
	}
	create_subbuttons(s);
}

void			create_subbuttons(t_rt *s)
{
	int i;
	int k;

	i = 4;
	k = 0;
	while (i < BUTTONS_AMOUNT)
	{
		if (i < 8)
			s->buttons[i].rect = make_rect((10 + k * 20), 50, BUTTON_SIZE, BUTTON_SIZE);
		else if (i < 12)
			s->buttons[i].rect = make_rect((10 + k * 20), 80, BUTTON_SIZE, BUTTON_SIZE);
		else if (i < 16)
			s->buttons[i].rect = make_rect((10 + k * 20), 120, BUTTON_SIZE, BUTTON_SIZE);
		else if (i < 20)
			s->buttons[i].rect = make_rect((106 + (k % 4) * 20), 10, BUTTON_SIZE, BUTTON_SIZE);
		else if (i < 21)
			s->buttons[i].rect = make_rect(188, 10, BUTTON_SIZE, BUTTON_SIZE);
		i++;
		k++;
		if (i >= 8 && k == 4)
			k = 0;
	}
}

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
		//		rt->blur = 1;
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
	else if (i == 19)
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
	clSetKernelArg(rt->effect_kernel.kernel, 2, sizeof(cl_uchar), &rt->effect_type);
}

void        add_new_disk(t_rt *rt, float3 origin);

void 			clean_scene(t_rt *rt)
{
	rt->scene.objnum = 1;
	free(rt->scene.objs);
	rt->scene.objs = (t_object*)malloc(sizeof(t_object));
	ft_bzero(rt->scene.objs, sizeof(rt->scene.objs) * rt->scene.objnum);
	add_new_disk(rt, (float3){{0, 5, 1}});
	rt->scene.objs[0].material.s3 = 1;
	rt->scene.objs[0].color = (float3){{0.9, 0.9, 0.9}};
	rt->scene.objs[0].prim.disk.normal = (float3){{0, 1, -0.1}};
	rt->scene.objs[0].prim.disk.radius2 = 100;
	rt->buttons[14].pressed = 0;
	reinit_opencl(rt);
}
void			check_pressing(t_rt *s, int x, int y)
{
	int i;
	int fig;
	i = -1;
	while (++i < BUTTONS_AMOUNT)
	{
		if (within_rect(s->buttons[i].rect, x, y))
		{
			if (s->buttons[i].pressed == 0)
			{
				if (i == 0)
					file_choosing(s);
				else if (i == 3)
					save_scene_to_png(s);
				else if (i == 15 && s->buttons[1].pressed)
					save_scene_to_file(s);
				else if (i == 14 && s->buttons[1].pressed)
					clean_scene(s);
				else
				{
					s->buttons[i].pressed = 1;
                    if (i > 3 && i < 16 && s->buttons[1].pressed && s->buttons[i].pressed)
                        modify_scene(s, i);
					if (i >= 16 && i < 21 && s->buttons[2].pressed && s->buttons[i].pressed)
						apply_after_effect(s, i);
				}
			}
			else
			{
				s->buttons[i].pressed = 0;
				if (i >= 16 && i < 21 && s->buttons[2].pressed)
					s->effect_type = 0;
			}
			return;
		}
	}
	fig = mouse_ray(s, x, y);
	if (fig > 0)
	{
		printf("\nfigure = %i\n", fig);
		start_settings_win(s, fig);
	}
}
