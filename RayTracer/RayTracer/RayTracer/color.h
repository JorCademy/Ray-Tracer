#pragma once

class Color
{
public:
	Color();
	Color(float r, float g, float b);
	~Color();
	bool EqualTo(Color& color2);
	void SetColor(Color& color2);
	Color SetColorSkyBox(int y);
	Color SetColorWhitted(int y);
	Color BlackAndWhite(int y);
	Color DirectIllumination(Color& objectColor, float nDotL, float rayLength);
	
	Color Clamp(float r, float g, float b);

	float m_r;
	float m_g;
	float m_b;

private:
};

