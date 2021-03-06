#include "camera.h"

Camera::Camera():
	d(1.0f)
{}

Camera::Camera(Vec3& position):
	d(1.0f)
{
	m_position = position;

	viewDirection = Vec3(0, 0, 1.0f);
	fov = viewDirection.MultFloatPoint(d);

	screenCenter = m_position.VectorAddition(fov);
	
	lowerLeftRef = Vec3(-1, -1, 0);
	upperLeftRef = Vec3(-1, 1, 0);
	upperRightRef = Vec3(1, 1, 0);

	screenUpperLeft = screenCenter.VectorAddition(upperLeftRef);
	screenUpperRight = screenCenter.VectorAddition(upperRightRef);
	screenLowerLeft = screenCenter.VectorAddition(lowerLeftRef);
}

Camera::~Camera() {}

float Camera::DistanceToPoint(Point3& point)
{
	auto dX = point.m_x - this->m_position.m_x;
	auto dY = point.m_y - this->m_position.m_y;
	auto dZ = point.m_z - this->m_position.m_z;

	double distance = sqrt((((double)dX * dX) + ((double)dY + dY) + ((double)dZ + dZ)));

	return (float) distance;
}