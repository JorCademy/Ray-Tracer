#include "plane.h"
 
Plane::Plane(Vec3 p0, Vec3 normal, Color color, bool reflective, bool glass, float size, float reflectivity):
	m_normalDotDirection(0),
	m_p0(p0),
	m_size(size)
{
	/* When increasing the lightFactor, the colors of the plane pop more. */
	m_lightFactor = 3.3f;
	m_center = p0;
	m_reflectivity = reflectivity;
	m_glass = glass;
	m_reflective = reflective;
	m_normal = normal;
	m_type = PLANE;
	m_color = color;
	m_normal.Normalize();
}
 
Plane::~Plane() 
{}
 
bool Plane::IntersectionWithRay(Ray& ray)
{
	m_normalDotDirection = this->m_normal.Dot(ray.m_direction);
 
	if (m_normalDotDirection > 0.0001f)
	{
		Vec3 difference = m_center.VectorSubtraction(ray.m_origin);
 
		float t = (difference.Dot(m_normal)) / (ray.m_direction.Dot(m_normal));

		if (t > 0.0001f)
		{
			if ((m_center.m_x - m_size) > ray.RayAtPoint(t).m_x || (m_center.m_x + m_size) < ray.RayAtPoint(t).m_x)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
	}
 
	return false;
}
 
/* Ref: https://samsymons.com/blog/math-notes-ray-plane-intersection/ */
float Plane::CalcIntersectionWithRay(Ray& ray)
{
	if (IntersectionWithRay(ray))
	{
		Vec3 difference = m_center.VectorSubtraction(ray.m_origin);
 
		float t = (difference.Dot(m_normal)) / (ray.m_direction.Dot(m_normal));
 
		if (t > 0.0001f)
		{
			return t;
		}
	}
 
	return 0.0f;
}
 
void Plane::Checkerboard(Ray& ray, float t)
{
	Point3 p1 = ray.RayAtPoint(t);
 
	if ((int)(p1.m_x * 2 + 2000) % 2 == (int)(p1.m_z * 2) % 2)
	{
		m_color = Color(0 * m_lightFactor, 0 * m_lightFactor, 0 * m_lightFactor);
	}
	else
	{
		m_color = Color(255 * m_lightFactor, 255 * m_lightFactor, 255 * m_lightFactor);;
	}
}