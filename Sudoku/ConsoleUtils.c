#include "ConsoleUtils.h"

void set_cursor_position(int x, int y)
{
	printf("\033[%d;%dH", x, y);
}

void set_text_color(int c)
{
	printf("\033[%dm", c);
}

void set_back_color(int c)
{
	printf("\033[%dm", c + 10);
}

