#include "stdafx.h"
#include "Font.h"

#include "Image.h"

void drawText(std::string s, const int x, const int y)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s.c_str()[i] != ' ')
		{
			char* sx = (char*)malloc(2 * sizeof sx);

			sx[0] = s.c_str()[i];
			sx[1] = '\0';

			std::string path = std::string("res/Font/").append(sx).append(".png");

			if (s.c_str()[i] == ':')
			{
				path = "res/Font/Colon.png";
			}

			Unknown::Graphics::Image character(path.c_str());

			character.render(x + i * 18, y);
		}
	}
}