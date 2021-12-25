#pragma once

// See: https://github.com/faluthe/cstrike15_src/blob/master/public/vgui/ISurface.h

#include "../sdk/classes/rendering/color.h"
#include "../sdk/sdk.h"

struct ISurface
{
	VIRTUAL_METHOD(void, DrawSetTextFont, 23, (unsigned long font), (this, font))
	VIRTUAL_METHOD(void, DrawSetTextColor, 25, (int r, int g, int b, int a = 255), (this, r, g, b, a))
	VIRTUAL_METHOD(void, DrawSetTextPos, 26, (int x, int y), (this, x, y))
	VIRTUAL_METHOD(void, DrawPrintText, 28, (const wchar_t* text, int textLen), (this, text, textLen, 0))
	VIRTUAL_METHOD(unsigned long, CreateFont, 71, (), (this))
	VIRTUAL_METHOD(bool, SetFontGlyphSet, 72, 
		(unsigned long font, const char* windowsFontName, int tall, int weight, 
			int blur, int scanlines, int flags),
		(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0))
	VIRTUAL_METHOD(int, GetFontTall, 74, (unsigned long font), (this, font))

	void DrawSetTextColor(const Color& color)
	{
		DrawSetTextColor(static_cast<int>(color.r), static_cast<int>(color.g), static_cast<int>(color.b), static_cast<int>(color.a));
	}
};