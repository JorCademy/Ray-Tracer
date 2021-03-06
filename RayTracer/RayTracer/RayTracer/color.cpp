#include "color.h"

Color::Color():
	m_r(0), 
	m_g(0), 
	m_b(0)
{}

Color::Color(float r, float g, float b):
	m_r(r), 
	m_g(g), 
	m_b(b)
{}

Color::~Color() {}

bool Color::EqualTo(Color& color2)
{
	return (this->m_r == color2.m_r && this->m_g == color2.m_g && this->m_b == color2.m_b);
}

void Color::SetColor(Color& color2)
{
	this->m_r = color2.m_r;
	this->m_g = color2.m_g;
	this->m_b = color2.m_b;
}

Color Color::DirectIllumination(Color& objectColor, float nDotL, float rayLength)
{
	float emittance = 100.0f;

	float r = emittance * (1 / (rayLength * rayLength)) * objectColor.m_r * nDotL;
	float g = emittance * (1 / (rayLength * rayLength)) * objectColor.m_g * nDotL;
	float b = emittance * (1 / (rayLength * rayLength)) * objectColor.m_b * nDotL;

	return Clamp(r, g, b);
}

Color Color::SetColorSkyBox(int y)
{
	float sky_r = 0;
	float sky_g = 0;
	float sky_b = 200;

	sky_r = (sky_r + 0.8f * y);
	sky_g = (sky_g + 0.8f * y);

	if (sky_r > 150)
	{
		sky_r = 150;
	}

	if (sky_g > 150)
	{
		sky_g = 150;
	}

	return Color(sky_r, sky_g, sky_b);
}

Color Color::SetColorWhitted(int y)
{
	float sky_r = 100;
	float sky_g = 100;
	float sky_b = 200;

	sky_r = sky_r - 0.7f * y;
	sky_g = sky_g - 0.7f * y;
	sky_b = sky_b - 0.7f * y;
	
	return Clamp(sky_r, sky_g, sky_b);
}

Color Color::BlackAndWhite(int y)
{
	float sky_r = 255;
	float sky_g = 255;
	float sky_b = 255;

	sky_r = sky_r - 0.85f * y;
	sky_g = sky_g - 0.85f * y;
	sky_b = sky_b - 0.85f * y;

	return Clamp(sky_r, sky_g, sky_b);
}

Color Color::Clamp(float r, float g, float b)
{
	if (r > 255) { r = 255; } else if (r < 0) { r = 0; }
	if (g > 255) { g = 255; } else if (g < 0) { g = 0; }
	if (b > 255) { b = 255; } else if (b < 0) { b = 0; }

	return Color(r, g, b);
}