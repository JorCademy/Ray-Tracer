#pragma once
#include "vec3.h"

class Camera
{
public:
	Camera();
	Camera(Vec3& position);
	~Camera();
	float DistanceToPoint(Point3& point);
	
	Point3 m_position;
	Vec3 screenCenter;
	Vec3 screenUpperLeft;
	Vec3 screenUpperRight;
	Vec3 screenLowerLeft;

	Vec3 upperLeftRef;
	Vec3 upperRightRef;
	Vec3 lowerLeftRef;

	/* Ref: Jacco Slides 1a - slide 22 */

	/* Screen */
	const int SCREEN_WIDTH = 600;
	const float SCREEN_HEIGHT = 400;

	/* Camera */
	float d;
	Vec3 fov;
	Vec3 viewDirection;
};

