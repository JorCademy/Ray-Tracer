#include "ray.h"

Ray::Ray()
{
	m_distance = 1;
	m_origin = Vec3(0, 0, 0);
	m_direction = Vec3(0, 0, 1);
}

Ray::Ray(Point3 origin, Vec3 direction):
	m_distance(1),
	m_origin(origin),
	m_direction(direction)
{
	m_origin.Normalize();
}

Ray::~Ray() {}

Vec3 Ray::GetRayOrigin()
{
	return m_origin;
}

void Ray::SetRayOrigin(Vec3& origin)
{
	m_origin = origin;
}

Vec3 Ray::GetRayDirection()
{
	return m_direction;
}

void Ray::SetRayDirection(Vec3& direction)
{
	m_direction = direction;
}

Vec3 Ray::CalculateDirection(Point3 pointOnScreen, Point3 origin)
{
	/* Ref: https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/variablesandmethods */
	Vec3 direction = pointOnScreen.VectorSubtraction(origin);
	Vec3 normalizedDirection = direction.Normalize();

	return normalizedDirection;
}

Vec3 Ray::CalculateShadowRayDirection(Point3 origin, Point3 lightSource)
{
	Vec3 direction = (lightSource.VectorSubtraction(origin)).Normalize();
	
	return direction;
}

Vec3 Ray::CalculateRefractionRayDirection(Vec3& normal, float nDivN)
{
	float angle = (normal.Dot(this->m_direction.MultFloatPoint(-1.0f)));
	float k = 1 - (nDivN * nDivN) * (1 - (angle * angle));

	if (k >= 0)
	{
		return this->m_direction.MultFloatPoint(nDivN).VectorAddition(normal.MultFloatPoint(nDivN * angle - (float) sqrt(k)));
	}
	else if (k < 0)
	{
		return Vec3(0, 0, 0);
	}

	return Vec3(0, 0, 0);
}

Vec3 Ray::CalculateReflectionRayDirection(Vec3& normal)
{
	// R = D - 2(D * N)N
	Vec3 D = this->GetRayDirection();
	Vec3 N = normal;
	Vec3 V = N.MultFloatPoint(D.Dot(N));
	Vec3 U = D.VectorSubtraction(V);
	Vec3 R = U.VectorSubtraction(V);

	return R;
}

Point3 Ray::RayAtPoint(float t)
{
	m_distance = t;

	float productTdX = m_direction.m_x * m_distance;
	float productTdY = m_direction.m_y * m_distance;
	float productTdZ = m_direction.m_z * m_distance;

	m_rayAtPixel = Point3(m_origin.m_x + productTdX, m_origin.m_y + productTdY, m_origin.m_z + productTdZ);

	return m_rayAtPixel;	// p(t) = O + t * D;
}

float Ray::GetLength(Point3& origin, Point3& intersectionPoint)
{
	float xSquared = (intersectionPoint.m_x - origin.m_x) * (intersectionPoint.m_x - origin.m_x);
	float ySquared = (intersectionPoint.m_y - origin.m_y) * (intersectionPoint.m_y - origin.m_y);
	float zSquared = (intersectionPoint.m_z - origin.m_z) * (intersectionPoint.m_z - origin.m_z);

	return (float) sqrt(fabs(xSquared) + fabs(ySquared) + fabs(zSquared));
}