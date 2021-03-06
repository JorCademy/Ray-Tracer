#pragma once
#include "objects.h"
#include "ray.h"

class Plane : public Objects
{
public:
	Plane(Vec3 p0, Vec3 normal, Color color, bool reflective, bool glass, float size, float reflectivity);
	~Plane();
	bool IntersectionWithRay(Ray& ray);
	float CalcIntersectionWithRay(Ray& ray);
	void Checkerboard(Ray& ray, float t);

	float m_lightFactor;

private:
	float m_size;
	float m_normalDotDirection;
	Point3 m_p0;
};

