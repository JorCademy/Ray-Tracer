#include "objects.h"

Objects::Objects():
	m_glass(false),
	m_lightFactor(1.0f),
	m_reflectivity(false),
	m_radius(0), 
	m_reflective(false), 
	m_type(0)
{}

Objects::~Objects() {}

bool Objects::IntersectionWithRay(Ray&) { return false; }

float Objects::CalcIntersectionWithRay(Ray&) { return 0.0f; }

void Objects::Checkerboard(Ray&, float) {  }

void Objects::SwitchToOtherColor(Color& color1, Color& color2) 
{
	if (this->m_color.EqualTo(color1))
	{
		this->m_color.SetColor(color2);
	}
	else if (this->m_color.EqualTo(color2))
	{
		this->m_color.SetColor(color1);
	} 
}

Vec3 Objects::CalculateNormal(Point3&) { return m_normal; }