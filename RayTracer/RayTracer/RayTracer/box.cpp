#include "box.h"

Box::Box(Point3 min, Point3 max, Vec3 normal, Color color, bool reflective, bool glass):
	m_min(min),
	m_max(max)
{
	m_type = BOX;
	m_normal = normal;
	m_color = color;
	m_reflective = reflective;
	m_glass = glass;
}

Box::~Box() {}

/* Ref: Jacco Bikker lecture 'Faster' - slide 28 */
bool Box::IntersectionWithRay(Ray& Ray) 
{
	double tx1 = (m_min.m_x - Ray.m_origin.m_x) / Ray.m_direction.m_x;
	double tx2 = (m_max.m_x - Ray.m_origin.m_x) / Ray.m_direction.m_x;

	double tmin = fmin(tx1, tx2);
	double tmax = fmax(tx1, tx2);

	double ty1 = (m_min.m_y - Ray.m_origin.m_y) / Ray.m_direction.m_y;
	double ty2 = (m_max.m_y - Ray.m_origin.m_y) / Ray.m_direction.m_y;

	tmin = fmax(tmin, fmin(ty1, ty2));
	tmax = fmin(tmax, fmax(ty1, ty2));

	return (tmax >= tmin && tmax > 0);
}

float Box::CalcIntersectionWithRay(Ray& Ray) 
{
	if (this->IntersectionWithRay(Ray))
	{
		double tx1 = (m_min.m_x - Ray.m_origin.m_x) / Ray.m_direction.m_x;
		double tx2 = (m_max.m_x - Ray.m_origin.m_x) / Ray.m_direction.m_x;

		double tmin = fmin(tx1, tx2);
		double tmax = fmax(tx1, tx2);

		double ty1 = (m_min.m_y - Ray.m_origin.m_y) / Ray.m_direction.m_y;
		double ty2 = (m_max.m_y - Ray.m_origin.m_y) / Ray.m_direction.m_y;

		tmin = fmax(tmin, fmin(ty1, ty2));
		tmax = fmin(tmax, fmax(ty1, ty2));

		double t = (tmax - Ray.m_origin.m_x) / Ray.m_direction.m_x;

		return (float) t;
	}

	return 0.0f;
}