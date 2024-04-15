#pragma once
#include <stdio.h>

typedef enum
{
	// Normal
	Black = 30,
	Red = 31,
	Green = 32,
	Yellow = 33,
	Blue = 34,
	Magenta = 35,
	Cyan = 36,
	White = 37,
	// Bright
	BrightBlack = 90,
	BrightRed = 91,
	BrightGreen = 92,
	BrightYellow = 93,
	BrightBlue = 94,
	BrightMagenta = 95,
	BrightCyan = 96,
	BrightWhite = 97
} TextColor;

void set_cursor_position(int x, int y);
void set_text_color(int c);
void set_back_color(int c);
