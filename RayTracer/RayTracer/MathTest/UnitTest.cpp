#include "UnitTest.h"
#include <stdio.h>

UnitTest::UnitTest()
{
	printf_s("* VEC3 UNIT TEST * \n");
	ConstructionTest();
	MathematicalOperatorsTest();
	LogicalOperatorTest();
	LengthOperationsTest();
}

UnitTest::~UnitTest()
{}

void UnitTest::ConstructionTest()
{
	const Vec3 v0 = Vec3();
	Check(1.1f, (v0.m_x == 0.0f && v0.m_y == 0.0f && v0.m_z == 0.0f));

	const Vec3 v1 = Vec3(9.1f, -3.0f, 2.5f);
	Check(1.2f, (v1.m_x == 9.1f && v1.m_y == -3.0f && v1.m_z == 2.5f));

	const Vec3 v2 = Vec3(9.2f);
	Check(1.3f, (v2.m_x == 9.2f && v2.m_y == 9.2f && v2.m_z == 9.2f));

	Vec3 v3 = v2;
	Check(1.4f, (v3.m_x == v2.m_x && v3.m_y == v2.m_y && v3.m_z == v2.m_z));

	v3.Clear();
	Check(1.5f, (v0.m_x == v3.m_x && v0.m_y == v3.m_y && v0.m_z == v3.m_z));
}

void UnitTest::MathematicalOperatorsTest()
{
	Vec3 v0 = Vec3(2.3f, 3.7f, 1.5f);
	Vec3 v1 = Vec3(-6.6f, 1.2f, 0.5f);
	const float factor = 3.5f;
	Vec3 v2;

	v2 = v0.VectorAddition(v1);
	Check(2.1f, (v2.m_x == v0.m_x + v1.m_x && v2.m_y == v0.m_y + v1.m_y));

	v2 = v0.VectorSubtraction(v1);
	Check(2.2f, (v2.m_x == v0.m_x - v1.m_x && v2.m_y == v0.m_y - v1.m_y));

	v2 = v1.MultFloatPoint(factor);
	Check(2.3f, (v2.m_x == v1.m_x * factor && v2.m_y == v1.m_y * factor && v2.m_z == v1.m_z * factor));

	v2 = v0.DivFloatPoint(factor);
	Check(2.4f, (v0.m_x / factor && v0.m_y / factor && v0.m_z / factor));

	const float dot = v0.Dot(v1);
	Check(2.5f, (dot == -9.99f));

	Vec3 v3 = Vec3(3.0f, -4.0f, 2.0f);
	v3.Add(v0);
	Check(2.6f, (v3.m_x == v0.m_x + 3.0f && v3.m_y == v0.m_y + -4.0f && v3.m_z == v0.m_z + 2.0f));

	Vec3 v4 = Vec3(3.0f, -4.0f, 2.0f);
	v4.Subtract(v1);
	Check(2.7f, (v4.m_x == 3.0f - v1.m_x && v4.m_y == -4.0f - v1.m_y && v4.m_z == 2.0f - v1.m_z));

	Vec3 v5 = Vec3(3.0f, -4.0f, 2.0f);
	v5.MultiplyWithScalar(factor);
	Check(2.8f, (v5.m_x == 3.0f * factor && v5.m_y == -4.0f * factor && v5.m_z == 2.0f * factor));
}

void UnitTest::LogicalOperatorTest()
{
	const float x = 2.93f;
	const float y = 4.39f;
	const float z = 3.28f;

	Vec3 v0 = Vec3(x, y, z);
	Vec3 v1 = Vec3(x, y, z);
	Vec3 v2 = Vec3(z, y, x);

	Check(3.1f, (v0.EqualTo(v1)));
	Check(3.2f, (v2.NotEqualTo(v0)));
}

void UnitTest::LengthOperationsTest()
{
	Vec3 v0 = Vec3(4.0f, 2.0f, 4.0f);

	const float vectorLength = v0.GetMagnitude();
	Check(4.1f, (vectorLength == 6.0f));

	const float vectorLengthSq = v0.GetMagnitudeSquared();
	Check(4.2f, (vectorLengthSq == 36.0f));

	v0.Trim(2.5f);
	Check(4.3f, (2.5f == v0.GetMagnitude()));

	Vec3 v1 = v0;
	Vec3 v2 = v1.Normalize();
	Check(4.4f, (v1.EqualTo(v0)));

	v0.Unit();
	Check(4.5f, (1.0f == v0.GetMagnitude()));
}

void UnitTest::Check(float test, bool expression)
{
	if (expression == true)
	{
		printf_s("%f: Test passed.\n", test);
	}
	else
	{
		printf_s("%f: Test failed.\n", test);
	}
}
