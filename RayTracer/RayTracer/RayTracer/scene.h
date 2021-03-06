#pragma once
#include "camera.h"
#include "objects.h"
#include "sphere.h"
#include "plane.h"
#include "box.h"

class Scene
{
public:
	Scene();
	~Scene();
	void ConstructScene();

	Camera* camera;
	Vec3 cameraPosition;
	Objects* objectsInScene[10];
	Sphere* sphere1;
	Sphere* sphere2;
	Sphere* sphere3;
	Plane* plane1;
	Point3* pointLight;
};

