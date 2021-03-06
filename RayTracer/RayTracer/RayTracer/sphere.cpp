#include "sphere.h"

Sphere::Sphere():
	m_discriminent(0),
	P(Vec3(0, 0, 0)),
	C(Vec3(0, 0, 0)),
	originMinusCenter(Vec3(0, 0, 0)),
	m_t1(0),
	m_t2(0), 
	m_nearestIntersectionPoint(0),
	m_a(0), 
	m_b(0),
	m_c(0) 
{
	m_reflective = false;
	m_radius = 1;
	m_normal = Vec3(0, 0, 1);
	m_type = SPHERE;
	m_center = Point3(0, 0, 10);
}

Sphere::Sphere(const Point3& middle, float radius, Color color, bool reflective, bool glass, float reflectivity): 
	m_discriminent(0),
	P(Vec3(0, 0, 0)),
	C(Vec3(0, 0, 0)),
	originMinusCenter(Vec3(0, 0, 0)),
	m_a(0),
	m_b(0),
	m_c(0), 
	m_nearestIntersectionPoint(0), 
	m_t1(0), 
	m_t2(0)
{
	m_reflectivity = reflectivity;
	m_glass = glass;
	m_reflective = reflective;
	m_radius = radius;
	m_normal = Vec3(0, 0, 1);
	m_type = SPHERE;
	m_center = middle;
	m_color = color;
}

Sphere::~Sphere() 
{
}

/* Ref: https://fiftylinesofcode.com/ray-sphere-intersection/ */
bool Sphere::IntersectionWithRay(Ray& Ray)
{
	originMinusCenter = Ray.m_origin.VectorSubtraction(m_center);

	m_a = Ray.m_direction.Dot(Ray.m_direction);
	m_b = (Ray.m_direction.Dot(originMinusCenter)) * 2.0f;
	m_c = originMinusCenter.Dot(originMinusCenter) - (m_radius * m_radius);

	m_discriminent = sqrtf((m_b * m_b) - (4 * m_a * m_c));

	return (m_discriminent >= 0);
}

float Sphere::CalcIntersectionWithRay(Ray& Ray)
{
	originMinusCenter = Ray.m_origin.VectorSubtraction(m_center);

	m_a = Ray.m_direction.Dot(Ray.m_direction);
	m_b = (Ray.m_direction.Dot(originMinusCenter)) * 2.0f;
	m_c = originMinusCenter.Dot(originMinusCenter) - (m_radius * m_radius);

	m_discriminent = (float) sqrtf((m_b * m_b - (4 * m_a * m_c)));

	if (m_discriminent > 0)
	{
		m_t1 = ((-m_b) + m_discriminent) / (2 * (m_a));
		m_t2 = ((-m_b) - m_discriminent) / (2 * (m_a));

		return FindNearestIntersectionPoint();
	}
	else if (m_discriminent == 0)
	{
		m_t1 = (float) (-m_b + m_discriminent) / (2 * m_a);

		return m_t1;
	}

	return 0.0f;
}

float Sphere::FindNearestIntersectionPoint()
{
	if (m_t1 < m_t2)
	{
		m_nearestIntersectionPoint = m_t1;
	}
	else
	{
		m_nearestIntersectionPoint = m_t2;
	}

	return m_nearestIntersectionPoint;
}

Vec3 Sphere::CalculateNormal(Point3& intersectionPoint)
{
	P = intersectionPoint;
	C = m_center;;
	m_normal = ((P.VectorSubtraction(C)).DivFloatPoint(m_radius)).Normalize();

	return m_normal;
}