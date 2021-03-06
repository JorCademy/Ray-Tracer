#include "scene.h"

Scene::Scene() 
{
	/* Camera initialization */
	cameraPosition = Vec3(0.0f, -1.5f, -0.5f);
	camera = new Camera(cameraPosition);

	/* Sphere initialization */
	sphere1 = new Sphere(Vec3(-0.0f, -3.5f, 6.5f), 2.5, Color(255, 255, 255), false, true, 0.5f);
	sphere2 = new Sphere(Vec3(-3.2f, -3.0f, 8.0f), 2.0, Color(100, 0, 0), true, false, 0.3f);
	sphere3 = new Sphere(Vec3(1.0f, -1.5f, 3.0f), 0.5f, Color(0, 0, 150), true, false, 0.2f);

	/* Plane initialization */
	plane1 = new Plane(Point3(0.0f, -1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Color(100, 0, 0), false, false, 10.0f, 0.1f);

	/* Construct the Scene */
	ConstructScene();
}

Scene::~Scene() 
{
	delete pointLight;
	delete camera;
	delete sphere1;
	delete sphere2;
	delete sphere3;
	delete plane1;
}

void Scene::ConstructScene()
{
	/* Light source(s) */
	pointLight =  new Point3(0, -25, 8);
	
	/* Primitives */
	objectsInScene[0] = plane1;
	objectsInScene[1] = sphere1;
	objectsInScene[2] = sphere2;
	objectsInScene[3] = sphere3;

	/* Enabled checkerboard texture onto the plane */
	plane1->m_checkerboard = true;
}