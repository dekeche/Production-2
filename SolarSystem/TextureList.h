#pragma once
#include "d3dApp.h"

struct TextureList
{
	static IDirect3DTexture9* Fire;
	static IDirect3DTexture9* NightEarth;
	static IDirect3DTexture9* DayEarth;
	static IDirect3DTexture9* WeatherEarth;
	static IDirect3DTexture9* DayMoon;
	static IDirect3DTexture9* NightMoon;
};
struct EffectList
{
	static ID3DXEffect* Fire;
	static ID3DXEffect* SunShadow;
	static ID3DXEffect* MoonShadow;
	static ID3DXEffect* FinalPass;
};