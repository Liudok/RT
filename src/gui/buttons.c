
#include "panels.h"

char **set_icons(void)
{
	char **icon;

	icon = (char **)malloc(sizeof(char *) * BUTTONS_AMOUNT);
	icon[0] = "src/icons/0.png";
	icon[1] = "src/icons/1.png";
	icon[2] = "src/icons/2.png";
	icon[3] = "src/icons/3.png";
	icon[4] = "src/icons/4.png";
	icon[5] = "src/icons/5.png";
	icon[6] = "src/icons/6.png";
	icon[7] = "src/icons/7.png";
	icon[8] = "src/icons/8.png";
	// icon[9] = "icons/9.png";
	// icon[10] = "icons/10.png";
	return (icon);
}

void			create_buttons(t_sdl *s)
{
	int i;
	char **icons;

	i = 0;
	icons = set_icons();
	while (i < BUTTONS_AMOUNT)
	{
		s->buttons[i].pressed = 0;
		s->buttons[i].name = i;
		s->buttons[i].rect.x = 30 + i * 40;
		s->buttons[i].rect.w = BUTTON_SIZE;
		s->buttons[i].rect.h = BUTTON_SIZE;
		if (i < 4)
			s->buttons[i].rect.y = 20;
		else if (i < 8)
		{
			s->buttons[i].rect.y = 100;
			s->buttons[i].rect.x -= 160;
		}
		else
		{
			s->buttons[i].rect.x = 100;
			s->buttons[i].rect.y = WINDOW_HEIGHT - 100;
		}
		s->buttons[i].txt = load_texture(icons[i], s);
		i++;
	}
	free(icons);
}

void			check_pressing(t_sdl *s, int x, int y)
{
	int i;

	i = 0;
	printf("x = %i, y = %i\n",x,y );
	while (i < BUTTONS_AMOUNT)
	{
		if (x >= s->buttons[i].rect.x - BUTTON_SIZE / 2 && x <= s->buttons[i].rect.x  + s->buttons[i].rect.w / 2
			&& y >= s->buttons[i].rect.y - 20 && y <= s->buttons[i].rect.y - 20 + s->buttons[i].rect.h)
		{
			printf("BUTTON # = %i\tx = %i\ny = %i\n",i, s->buttons[i].rect.x, s->buttons[i].rect.y );
		printf("s->buttons[i].rect.x = %i\ns->buttons[i].rect.y = %i\n", s->buttons[i].rect.x, s->buttons[i].rect.y );
		
			if (s->buttons[i].pressed == 0)
			{
				s->buttons[i].pressed = 1;
				if (i >= 8)
					file_choosing(s, i); 
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
