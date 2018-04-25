
#include "../../include/panels.h"

void 			save_scene_to_png(t_rt *s)
{
	const char	*export;
	const char	*format[1] = { "*.png" };
	SDL_Surface *surface;

	export = tinyfd_saveFileDialog("", "amazing.png", 1, format, NULL);
	if (export == NULL)
		return ;
	surface = SDL_CreateRGBSurface(0, s->sdl.win_w, s->sdl.win_h,
								   32, 0, 0, 0, 0);
	ft_memcpy(surface->pixels, s->sdl.pixels, surface->h * surface->pitch);
	IMG_SavePNG(surface, export);
	SDL_FreeSurface(surface);
}
