#include "panels.h"

void		file_choosing(t_sdl *s, int i)
{
	char const * lFilterPatterns[2] = { "*.bmp", "*.rt" };
	if (i == 8)
	{
		s->file = (char *)tinyfd_openFileDialog("Please choose .rt file", "", 2, lFilterPatterns, NULL, 0);
		printf("file = %s\n",s->file );
	}
	if (i == 9)
	{

		
	}
	// validate_file(s->file);
}