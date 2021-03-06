/* NOTE - THIS IS A COPY OF THE VEC3.CPP FILE IN THE MAIN APPLICATION */
#include "Vec3.h"

Vec3::Vec3()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
}

Vec3::Vec3(float x) :
	m_x(x),
	m_y(x),
	m_z(x)
{}

Vec3::Vec3(float x, float y, float z) :
	m_x(x),
	m_y(y),
	m_z(z)
{}

Vec3::~Vec3() {}

bool Vec3::EqualTo(Vec3 b)
{
	return (this->m_x == b.m_x) && (this->m_y == b.m_y) && (this->m_z == b.m_z);
}

bool Vec3::NotEqualTo(Vec3& b)
{
	return (this->m_x != b.m_x || this->m_y != b.m_y || this->m_z != b.m_z);
}

float Vec3::GetMagnitude()
{
	float magnitude;

	float xSquared = m_x * m_x;
	float ySquared = m_y * m_y;
	float zSquared = m_z * m_z;

	double sumOfSquaredValues = (double)(xSquared)+(double)ySquared + (double)zSquared;

	magnitude = (float)sqrt(sumOfSquaredValues);

	return magnitude;
}

float Vec3::GetMagnitudeSquared()
{
	float xSquared = m_x * m_x;
	float ySquared = m_y * m_y;
	float zSquared = m_z * m_z;

	float sumOfSquaredValues = xSquared + ySquared + zSquared;

	return (float)sumOfSquaredValues;
}

float Vec3::SumOfComponents()
{
	return (m_x + m_y + m_z);
}

float Vec3::Dot(Vec3 b)
{
	float dotProductX;
	float dotProductY;
	float dotProductZ;

	dotProductX = (m_x * b.m_x);
	dotProductY = (m_y * b.m_y);
	dotProductZ = (m_z * b.m_z);

	return dotProductX + dotProductY + dotProductZ;
}

Vec3 Vec3::Normalize()
{
	float x = m_x;
	float y = m_y;
	float z = m_z;

	float magnitude = GetMagnitude();

	x /= magnitude;
	y /= magnitude;
	z /= magnitude;

	return Vec3(x, y, z);
}

Vec3 Vec3::CrossProduct(Vec3 b)
{
	float generatedX = (m_y * b.m_z) - (m_z * b.m_y);
	float generatedY = (m_z * b.m_x) - (m_x * b.m_z);
	float generatedZ = (m_x * b.m_y) - (m_y * b.m_x);

	return Vec3(generatedX, generatedY, generatedZ);
}

Vec3 Vec3::VectorAddition(Vec3 b)
{
	float thisX = this->m_x;
	float thisY = this->m_y;
	float thisZ = this->m_z;

	float sumX = thisX + b.m_x;
	float sumY = thisY + b.m_y;
	float sumZ = thisZ + b.m_z;

	return Vec3(sumX, sumY, sumZ);
}

Vec3 Vec3::VectorSubtraction(Vec3 b)
{
	float thisX = this->m_x;
	float thisY = this->m_y;
	float thisZ = this->m_z;

	float sumX = thisX - b.m_x;
	float sumY = thisY - b.m_y;
	float sumZ = thisZ - b.m_z;

	return Vec3(sumX, sumY, sumZ);
}

Vec3 Vec3::VectorMultiplication(Vec3 b)
{
	Vec3 product;

	float x = this->m_x * b.m_x;
	float y = this->m_y * b.m_y;
	float z = this->m_z * b.m_z;

	product = Vec3(x, y, z);

	return product;
}

Vec3 Vec3::VectorDivision(Vec3 b)
{
	Vec3 division;

	float x = this->m_x / b.m_x;
	float y = this->m_y / b.m_y;
	float z = this->m_z / b.m_z;

	division = Vec3(x, y, z);

	return division;
}

Vec3 Vec3::MultFloatPoint(float n)
{
	float x = m_x;
	float y = m_y;
	float z = m_z;

	x *= n;
	y *= n;
	z *= n;

	return Vec3(x, y, z);
}

Vec3 Vec3::DivFloatPoint(float n)
{
	float x = m_x;
	float y = m_y;
	float z = m_z;

	x /= n;
	y /= n;
	z /= n;

	return Vec3(x, y, z);
}

void Vec3::Add(Vec3& b)
{
	this->m_x += b.m_x;
	this->m_y += b.m_y;
	this->m_z += b.m_z;
}

void Vec3::Subtract(Vec3& b)
{
	this->m_x -= b.m_x;
	this->m_y -= b.m_y;
	this->m_z -= b.m_z;
}

void Vec3::Trim(float newLength)
{
	Vec3 u;
	float scalar = (newLength / this->GetMagnitude());
	u = this->MultFloatPoint(scalar);

	this->m_x = u.m_x;
	this->m_y = u.m_y;
	this->m_z = u.m_z;
}

void Vec3::Unit()
{
	Vec3 u;
	float scalar = (1.0f / this->GetMagnitude());
	u = this->MultFloatPoint(scalar);

	this->m_x = u.m_x;
	this->m_y = u.m_y;
	this->m_z = u.m_z;
}

void Vec3::MultiplyWithScalar(float factor)
{
	this->m_x *= factor;
	this->m_y *= factor;
	this->m_z *= factor;
}

void Vec3::Clear()
{
	this->m_x = 0.0f;
	this->m_y = 0.0f;
	this->m_z = 0.0f;
}

float Vec3::CalculateAngleBetweenVectors(Vec3 b)
{
	float counter = this->SumOfComponents() * b.SumOfComponents();
	float denumerator = this->GetMagnitude() * b.GetMagnitude();

	float cosineAngle = counter / denumerator;
	double angle = acos(cosineAngle);

	return (float)angle;
}