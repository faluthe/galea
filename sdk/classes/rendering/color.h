#pragma once

struct Color
{
	float r, g, b;
	float a{ 255.f };
};

namespace colors
{
	constexpr Color white{ 255.f, 255.f, 255.f };
	constexpr Color grey{ 145.f, 145.f, 145.f };
	constexpr Color red{ 255.f, 0.f, 0.f };
}