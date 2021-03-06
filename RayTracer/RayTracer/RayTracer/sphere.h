#pragma once
#include "objects.h"
#include "ray.h"

class Sphere : public Objects
{
public:
	Sphere();
	Sphere(const Point3& middle, float radius, Color color, bool reflective, bool glass, float reflectivity);
	~Sphere();
	bool IntersectionWithRay(Ray& Ray);
	float CalcIntersectionWithRay(Ray& Ray);
	float FindNearestIntersectionPoint();
	Vec3 CalculateNormal(Point3& intersectionPoint);
	
private:
	Vec3 originMinusCenter;
	Point3 m_center;
	float m_a;
	float m_b;
	float m_c;
	float m_t1;
	float m_t2;
	float m_nearestIntersectionPoint;
	float m_discriminent;
	
	/* Normal Calculation */
	Vec3 P;
	Vec3 C;
};

