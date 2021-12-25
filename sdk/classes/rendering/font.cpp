#include <stdexcept>

#include "../../interfaces/interfaces.h"
#include "font.h"

void Font::print(const std::wstring& text, int x, int y, const Color& color)
{
	ifaces::surface->DrawSetTextFont(HFont);
	ifaces::surface->DrawSetTextColor(color);

	ifaces::surface->DrawSetTextPos(x, y);

	ifaces::surface->DrawPrintText(text.c_str(), text.length());
}

void Font::setup(int tall, int weight, int flags, const char* windows_font_name)
{
	HFont = ifaces::surface->CreateFont();

	if (!ifaces::surface->SetFontGlyphSet(HFont, windows_font_name, tall, weight, 0, 0, flags))
		sdk::debug::error("SetFontGlyphSet error");

	height = ifaces::surface->GetFontTall(HFont);

	sdk::debug::print("Font height: " + std::to_string(height) + " pixels");
}