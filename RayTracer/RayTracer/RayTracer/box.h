#pragma once
#include "objects.h"

/*Ref: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection */
class Box : public Objects
{
public:
	Box(Point3 min, Point3 max, Vec3 normal, Color color, bool reflective, bool glass);
	~Box();
	bool IntersectionWithRay(Ray& Ray);
	float CalcIntersectionWithRay(Ray& Ray);

private:
	Point3 m_min;
	Point3 m_max;
};

