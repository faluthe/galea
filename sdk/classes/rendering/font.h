#pragma once

#include <string>

#include "color.h"

class Font
{
private:
	unsigned long HFont{};
public:
	int height{};

	void print(const std::wstring& text, int x, int y, const Color& color = colors::white);
	void setup(int tall, int weight, int flags, const char* windows_font_name = "Tahoma");
	int text_width(const std::wstring& text);
};