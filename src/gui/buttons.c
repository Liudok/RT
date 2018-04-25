
#include "../../include/panels.h"

void set_icons(t_rt *s)
{
	s->icon = (char **)malloc(sizeof(char *) * BUTTONS_AMOUNT);
	s->icon[0] = "src/icons/find.png";
	s->icon[1] = "src/icons/create_file.png";
	s->icon[2] = "src/icons/settings.png";
	s->icon[3] = "src/icons/render.png";
	s->icon[4] = "src/icons/sphere.png";
	s->icon[5] = "src/icons/planes.png";
	s->icon[6] = "src/icons/cyli.png";
	s->icon[7] = "src/icons/cones.png";
	s->icon[8] = "src/icons/tria.png";
	s->icon[9] = "src/icons/stop.png";
	s->icon[10] = "src/icons/icon.png";
	s->icon[11] = "src/icons/cubes.png";
	s->icon[12] = "src/icons/spotlight.png";
	s->icon[13] = "src/icons/sun-2.png";
	s->icon[14] = "src/icons/path.png";
	s->icon[15] = "src/icons/find_in.png";
//	s->icon[16] = "src/icons/settings.png";

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
	while (i < 16)
	{
		s->buttons[i].pressed = 0;
		s->buttons[i].name = i;
		if (i < 8)
			s->buttons[i].rect = make_rect((10 + k * 20), 50, BUTTON_SIZE, BUTTON_SIZE);
		else if (i < 12)
			s->buttons[i].rect = make_rect((10 + k * 20), 80, BUTTON_SIZE, BUTTON_SIZE);
		else if (i < 16)
			s->buttons[i].rect = make_rect((10 + k * 20), 120, BUTTON_SIZE, BUTTON_SIZE);
		s->buttons[i].txt = load_texture(s->icon[i], s);
		i++;
		k++;
		if (i >= 8 && k == 4)
			k = 0;
	}
}

void			check_pressing(t_rt *s, int x, int y)
{
	int i;

	i = 0;
	printf("x = %i, y = %i\n", x, y);
	while (i < BUTTONS_AMOUNT)
	{
		if (within_rect(s->buttons[i].rect, x, y))
		{
			if (s->buttons[i].pressed == 0)
			{
				if (i == 0)
					file_choosing(s);
				else if (i == 15)
					save_scene_to_file(s);
				else if (i == 3)
					save_scene_to_png(s);
				else
					s->buttons[i].pressed = 1;
			}
			else
			{
				s->buttons[i].pressed = 0;
			}
			printf("pressed in check i = %i\n", i);
		}
		i++;
	}
}
