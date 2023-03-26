#pragma once

#include <initializer_list>
#include <Windows.h>
#include <string>
#include <vector>

#include "../../sdk/classes/rendering/color.h"

struct Option 
{
	Option(const std::wstring title) : title{ title } {}
	const std::wstring title;
	virtual void while_selected(int x, int& y) = 0;
	virtual void while_not_selected(int x, int& y) = 0;
};

struct BoolOption : Option 
{
	BoolOption(const std::wstring title, bool* state)
		: Option(title), state{ state } {}
	bool* state;
	virtual void while_selected(int x, int& y) override;
	virtual void while_not_selected(int x, int& y) override;
};

struct InvisibleBool : Option
{
	InvisibleBool(const std::wstring title, bool* state, bool* parent)
		: Option(title), state{ state }, parent{ parent } {}
	bool* state;
	bool* parent;
	virtual void while_selected(int x, int& y) override;
	virtual void while_not_selected(int x, int& y) override;
};

struct FloatOption : Option
{
	FloatOption(const std::wstring title, float* flt, float modifier, float min, float max)
		: Option(title), flt{ flt }, modifier{ modifier }, min{ min }, max{ max } {}
	float* flt;
	float modifier;
	float min;
	float max;
	virtual void while_selected(int x, int& y) override;
	virtual void while_not_selected(int x, int& y) override;
};

struct IntOption : Option
{
	IntOption(const std::wstring title, int* i, int modifier, int min, int max)
		: Option(title), i{ i }, modifier{ modifier }, min{ min }, max{ max } {}
	int* i;
	int modifier;
	int min;
	int max;
	virtual void while_selected(int x, int& y) override;
	virtual void while_not_selected(int x, int& y) override;
};

namespace config
{
	void render();
	void render_watermark();

	constexpr int menu_button{ VK_INSERT };
	constexpr int panic_button{ VK_END };

	inline bool autopistol{ true };
	inline bool bunnyhop{ true };
	inline bool backtrack_chams{ true };
	inline bool chams{ true };
	inline bool ignore_z{ false };
	inline bool render_target_tick{ false };
	inline int crosshair_mode{ 1 };
	inline float fakeping{ 0.0f };
	inline bool triggerbot{ true };

	namespace colors
	{
		constexpr Color crosshair{ 0xFF, 0xFF, 0xFF };
		constexpr Color enemy_hidden{ 0x6f, 0x4f, 0xfe };
		constexpr Color enemy_visible{ 0x00, 0x78, 0xff };
		constexpr Color interp_ticks{ 0x1E, 0xAD, 0x28, 0x50 };
		constexpr Color target_tick{ 0x6f, 0x4f, 0xfe, 0xAE };
	}

	namespace convars
	{
		// Go to the moon!
		inline bool apollo{ true };
		inline bool nade_preview{ true };
		inline bool stretched_ratio{ false };

		void set();
		// Called when uninjecting
		void restore();
	}
}