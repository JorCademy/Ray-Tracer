#pragma once
/* NOTE - THIS IS A COPY OF THE VEC3.H FILE IN THE MAIN APPLICATION */
#include <math.h>

class Vec3
{
public:
	Vec3();
	Vec3(float x);
	Vec3(float x, float y, float z);
	~Vec3();
	bool EqualTo(Vec3 b);
	bool NotEqualTo(Vec3& b);
	float GetMagnitude();
	float GetMagnitudeSquared();
	float SumOfComponents();
	float Dot(Vec3 b);
	Vec3 Normalize();
	Vec3 MultFloatPoint(float n);
	Vec3 DivFloatPoint(float n);
	Vec3 CrossProduct(Vec3 b);
	Vec3 VectorAddition(Vec3 b);
	Vec3 VectorSubtraction(Vec3 b);
	Vec3 VectorMultiplication(Vec3 b);
	Vec3 VectorDivision(Vec3 b);
	void Add(Vec3& b);
	void Subtract(Vec3& b);
	void MultiplyWithScalar(float factor);
	void Trim(float newLength);
	void Unit();
	void Clear();
	float CalculateAngleBetweenVectors(Vec3 b);

	float m_x;
	float m_y;
	float m_z;
};

// Ref: https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/variablesandmethods
using Point3 = Vec3;
