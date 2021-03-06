#pragma once
#include "vec3.h"
#include "ray.h"
#include "color.h"

class Objects
{
public:
	Objects();
	~Objects();
	virtual bool IntersectionWithRay(Ray&);
	virtual float CalcIntersectionWithRay(Ray&);
	virtual void Checkerboard(Ray&, float);
	void SwitchToOtherColor(Color& color1, Color& color2);
	virtual Vec3 CalculateNormal(Point3&); 

	float m_lightFactor;
	float m_reflectivity;
	bool m_checkerboard = false;
	bool m_glass;
	bool m_reflective;
	float m_radius;
	int m_type;
	Color m_color;
	Point3 m_center;
	Vec3 m_normal;
	enum types { SPHERE, PLANE, BOX };
};