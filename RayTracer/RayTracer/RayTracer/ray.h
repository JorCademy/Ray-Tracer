#pragma once
#include "vec3.h"

class Ray
{
public:
	Ray();
	Ray(Vec3 origin, Vec3 direction);
	~Ray();
	Vec3 GetRayOrigin();
	void SetRayOrigin(Vec3& origin);
	Vec3 GetRayDirection();
	void SetRayDirection(Vec3& direction);
	Vec3 CalculateDirection(Point3 pointOnScreen, Point3 origin);
	Vec3 CalculateShadowRayDirection(Point3 origin, Point3 lightSource);
	Vec3 CalculateRefractionRayDirection(Vec3& normal, float nDivN);
	Vec3 CalculateReflectionRayDirection(Vec3& normal);
	Vec3 RayAtPoint(float t);
	float GetLength(Point3& origin, Point3& intersectionPoint);

	Vec3 m_rayAtPixel;
	Point3 m_origin;
	Vec3 m_direction;
	float m_distance;
};

