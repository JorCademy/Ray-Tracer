#pragma warning(push)
#pragma warning( disable : 26812 )
#pragma warning( disable : 4100 )
#include "SDL.h"
#include "scene.h"
#include "ray.h"

/* Events */
SDL_Event event;
Scene* scene;
Ray* ref;
bool quitApplication = false;
bool sceneRendered = false;
int samplesPerPixel = 25;
bool removePlaneShadows = true;

/* Important Colors */
const Color BLACK(0, 0, 0);
const Color WHITE(255, 255, 255);
const Color WHITTED_BLUE(0, 191, 255);
Color backdrop;

/* Counters to cap recursion */
int reflectionCounter = 0;
int refractionCounter = 0;

/* Refraction values (may be moved later) */
float n1 = 1.0f;
float n2 = 1.333f;
float nDivN = n1 / n2;
float nDivNFlip = n2 / n1;

/* Random Number Generation */
unsigned short lfsr = 0xACE1u; /* Seed */
unsigned bit;

/* Function Definitions */
float GenerateRandomFloat();
int IntersectionWithRay(Ray& ray, int i);
int IntersectionWithRay(Ray& ray);
Point3 CalculatePointOnScreen(float u, float v, Point3 origin, Vec3 topLeft, Vec3 bottomLeft, Vec3 topRight);
Color RefractionColor(Ray& ray, float t, Vec3& normal, int i, int x, int y);
float Fresnel(Ray& ray, Ray& refractionRay, Vec3& normal);
Color ReflectedColor(Color& reflectedColor, Color& calculatedSceneColor, float objectReflectivity);
Color ShadowColor(Ray& ray, Color& sceneColor, float t);
Color Trace(Vec3 O, Vec3 D, int x, int y);
void RenderPixels(SDL_Renderer* Renderer);

/* Ref: https://stackoverflow.com/questions/7602919/how-do-i-generate-random-numbers-without-rand-function */
unsigned random()
{
	/* Returns either 1 or 0, based on the result of the comparison of shifted values (using XOR) and 1, using the AND operator. */
	bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1; 

	/* Compares bit values (using OR operator) and returns number. */
	return lfsr = (unsigned short)((lfsr >> 1) | (bit << 15));
}

float GenerateRandomFloat()
{
	/* Makes sure the generated number can be used as an offset. */
	return ((random() + 0.0f) / 100000);
}

int IntersectionWithRay(Ray& ray)
{
	float t = 0.0f;
	int indexToReturn = 101;

	for (int j = 0; j < sizeof(scene->objectsInScene[j]); j++)
	{
		if (scene->objectsInScene[j] != nullptr)
		{
			float calculatedT = scene->objectsInScene[j]->CalcIntersectionWithRay(ray);

			if (calculatedT > 0.0f)
			{
				if (calculatedT < t || t == 0.0f)
				{
					t = calculatedT;

					indexToReturn = j;
				}
			}
		}
	}

	/* If intersectionWithRay == 0.0f, then there is no intersection. */
	return indexToReturn;
}

int IntersectionWithRay(Ray& ray, int i)
{
	float t = 0.0f;
	int indexToReturn = 101;

	for (int j = 0; j < sizeof(scene->objectsInScene[j]); j++)
	{
		if (scene->objectsInScene[j] != nullptr)
		{
			if (j != i)
			{
				float calculatedT = scene->objectsInScene[j]->CalcIntersectionWithRay(ray);

				if (calculatedT > 0.0f)
				{
					if (calculatedT < t || t == 0.0f)
					{
						t = calculatedT;

						indexToReturn = j;
					}
				}
			}
		}
	}

	/* If intersectionWithRay == 0.0f, then there is no intersection. */
	return indexToReturn;
}

/* Ref: https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/variablesandmethods */
void EventManagement()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			quitApplication = true;
		}
	}
}

Point3 CalculatePointOnScreen(float u, float v, Point3 origin, Vec3 topLeft, Vec3 bottomLeft, Vec3 topRight)
{
	/* Ref: https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/variablesandmethods */
	Vec3 hor = Vec3(2.0f, 0.0f, 0.0f);
	Vec3 ver = Vec3(0.0f, 1.4f, 0.0f);

	Vec3 uHor = hor.MultFloatPoint(u);
	Vec3 vVer = ver.MultFloatPoint(v);

	Vec3 lowPlusU = bottomLeft.VectorAddition(uHor);
	Vec3 lowPlusUPlusV = lowPlusU.VectorAddition(vVer);

	return lowPlusUPlusV;
}

float Fresnel(Ray& ray, Ray& refractionRay, Vec3& normal)
{
	float angleD = (normal.Dot(ray.m_direction.MultFloatPoint(-1.0f)));
	float angleT = (normal.Dot(refractionRay.m_direction.MultFloatPoint(-1.0f)));

	double surfaceReflectivityFirstElement = ((n1 * angleD) - n2 * angleT) / ((n1 * angleD) + n2 * angleT);
	double surfaceReflectivitySecondElement = ((n1 * angleT) - n2 * angleD) / ((n1 * angleT) + n2 * angleD);

	double Fr = 0.5 * ((surfaceReflectivityFirstElement * surfaceReflectivityFirstElement) + (surfaceReflectivitySecondElement * surfaceReflectivitySecondElement));

	return (float) Fr;
}

Color RefractionColor(Ray& ray, float t, Vec3& normal, int i, int x, int y)
{
	Color color;
	Ray refractionRay;
	Point3 intersectionPoint = ray.RayAtPoint(t + 0.0001f);
	float nDivNSelected = nDivN;
	float intersectionWithRefractiveObjectT;
	Vec3 T = ray.CalculateRefractionRayDirection(normal, nDivNSelected);
	Color refractedColor;
	Color reflectedColor = Trace(ray.RayAtPoint(t + 0.0001f), ray.CalculateReflectionRayDirection(scene->objectsInScene[i]->m_normal), x, y);
	Color calculatedReflectedColor = ReflectedColor(reflectedColor, color, scene->objectsInScene[i]->m_reflectivity);

	if (!(T.EqualTo(Vec3(0, 0, 0))))
	{
		refractionRay = Ray(intersectionPoint, T);
		intersectionWithRefractiveObjectT = scene->objectsInScene[i]->CalcIntersectionWithRay(refractionRay);

		if (intersectionWithRefractiveObjectT > 0.0f)
		{
			intersectionPoint = refractionRay.RayAtPoint(intersectionWithRefractiveObjectT);

			T = refractionRay.CalculateRefractionRayDirection(normal, nDivNSelected);
		}

		refractionRay = Ray(intersectionPoint, T);
	}
	else
	{
		return calculatedReflectedColor;
	}

	int intersectionIndex = IntersectionWithRay(refractionRay, i);
	float Fr = Fresnel(ray, refractionRay, scene->objectsInScene[i]->m_normal);

	if (intersectionIndex != 101)
	{
		Point3 refractIntersection = refractionRay.RayAtPoint(scene->objectsInScene[(int)intersectionIndex]->CalcIntersectionWithRay(refractionRay) - 0.001f);
		refractedColor = Trace(refractIntersection, T, x, y);
	}
	else
	{
		refractedColor = backdrop;
	}

	float diffuseColorValue = 1.0f;
	color.m_r = Fr * reflectedColor.m_r + (1 - Fr) * refractedColor.m_r * diffuseColorValue;
	color.m_g = Fr * reflectedColor.m_g + (1 - Fr) * refractedColor.m_g * diffuseColorValue;
	color.m_b = Fr * reflectedColor.m_b + (1 - Fr) * refractedColor.m_b * diffuseColorValue;

	/* In order to calculate the right color, the reflectivity of the surface still needs to be calculated. */
	return color.Clamp(color.m_r, color.m_g, color.m_b);
}

Color ReflectedColor(Color& reflectedColor, Color& calculatedSceneColor, float objectReflectivity)
{
	float reflectedAmount = objectReflectivity;
	float objectAmount = 1 - objectReflectivity;

	/* Ref: https://blog.demofox.org/2017/01/09/raytracing-reflection-refraction-fresnel-total-internal-reflection-and-beers-law/ */
	reflectedColor.m_r = (reflectedAmount * reflectedColor.m_r) + (objectAmount * calculatedSceneColor.m_r);
	reflectedColor.m_g = (reflectedAmount * reflectedColor.m_g) + (objectAmount * calculatedSceneColor.m_g);
	reflectedColor.m_b = (reflectedAmount * reflectedColor.m_b) + (objectAmount * calculatedSceneColor.m_b);
	reflectedColor = reflectedColor.Clamp(reflectedColor.m_r, reflectedColor.m_g, reflectedColor.m_b);

	return reflectedColor;
}

Color ShadowColor(Ray& ray, Color& sceneColor, float t)
{
	Point3 shadowRayOrigin = ray.RayAtPoint(t - 0.0001f);
	Vec3 shadowRayDirection = (scene->pointLight->VectorSubtraction(shadowRayOrigin)).Normalize();
	Ray* shadowRay = new Ray(shadowRayOrigin, shadowRayDirection);
	Color color = sceneColor;

	int indexOfIntersectionPrimitive = IntersectionWithRay(*shadowRay);

	if (indexOfIntersectionPrimitive != 101)
	{
		if ((t > 0.0f) && t < ((scene->pointLight->VectorSubtraction(shadowRayOrigin)).GetMagnitude()))
		{
			if (!scene->objectsInScene[indexOfIntersectionPrimitive]->m_glass)
			{
				color.m_r = color.m_r * 0.2f;
				color.m_g = color.m_g * 0.2f;
				color.m_b = color.m_b * 0.2f;
			}
			else
			{
				color.m_r = color.m_r * 0.5f;
				color.m_g = color.m_g * 0.5f;
				color.m_b = color.m_b * 0.5f;
			}
		}

		color.Clamp(color.m_r, color.m_g, color.m_b);
	}

	delete shadowRay;

	return color;
}

Color Trace(Vec3 O, Vec3 D, int x, int y)
{
	Color color;

	/* Edit to change backdrop. */
	/* Some backdrops are accessible in the Color class. */
	backdrop = color.BlackAndWhite(y);

	float t = 0.0f;
	int objectIndexToDraw = 0;
	Ray ray = Ray(O, D);

	for (int i = 0; i < sizeof(scene->objectsInScene) / sizeof(scene->objectsInScene[i]); i++)
	{
		if (scene->objectsInScene[i] != NULL)
		{
			float intersectT = scene->objectsInScene[i]->CalcIntersectionWithRay(ray);

			if (intersectT > 0.0f)
			{
				if (intersectT < t || t == 0.0f)
				{
					t = intersectT;
					objectIndexToDraw = i;
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			break;
		}
	}

	if (t > 0.0f)
	{
		Point3 intersectionPoint = ray.RayAtPoint(t);
		Vec3 intersectToLight = scene->pointLight->VectorSubtraction(intersectionPoint);
		float nDotL = intersectionPoint.Dot(intersectToLight.Normalize());
		float distanceIntersectToLight = intersectToLight.GetMagnitude();

		if (scene->objectsInScene[objectIndexToDraw]->m_checkerboard)
		{
			scene->objectsInScene[objectIndexToDraw]->Checkerboard(ray, t);
		}

		color = color.DirectIllumination(scene->objectsInScene[objectIndexToDraw]->m_color, nDotL, distanceIntersectToLight);

		scene->objectsInScene[objectIndexToDraw]->CalculateNormal(intersectionPoint);

		if (scene->objectsInScene[objectIndexToDraw]->m_reflective)
		{
			if (reflectionCounter < 10000000000)
			{
				Color reflectedColor = Trace(ray.RayAtPoint(t), ray.CalculateReflectionRayDirection(scene->objectsInScene[objectIndexToDraw]->m_normal), x, y);
				color = ReflectedColor(reflectedColor, color, scene->objectsInScene[objectIndexToDraw]->m_reflectivity);

				reflectionCounter++;
			}
		}
		else if (scene->objectsInScene[objectIndexToDraw]->m_glass)
		{
			if (refractionCounter < 100000000)
			{
				color = RefractionColor(ray, t, scene->objectsInScene[objectIndexToDraw]->m_normal, objectIndexToDraw, x, y);

				refractionCounter++;
			}
		}
		else
		{
			color = ShadowColor(ray, color, t);
		}
	}
	else
	{
		return backdrop;
	}

	return color;
}

void RenderPixels(SDL_Renderer* Renderer)
{
	for (int y = (int) scene->camera->SCREEN_HEIGHT; y >= 0; y--)
	{
		Color color;

		for (int x = 0; x < (int) scene->camera->SCREEN_WIDTH; x++)
		{
			float colorSum_r = 0.0f;
			float colorSum_g = 0.0f;
			float colorSum_b = 0.0f;

			for (int i = 0; i < samplesPerPixel; i++)
			{
				/* Ref: https://raytracing.github.io/books/RayTracingInOneWeekend.html#thevec3class/variablesandmethods */
				float u = float(x + GenerateRandomFloat()) / (scene->camera->SCREEN_WIDTH - 1);
				float v = float(y + GenerateRandomFloat()) / (scene->camera->SCREEN_HEIGHT - 1);

				Point3 pointOnScreen = CalculatePointOnScreen(u, v, scene->cameraPosition, scene->camera->screenUpperLeft, scene->camera->screenLowerLeft, scene->camera->screenUpperRight);
				Vec3 rayDirection = ref->CalculateDirection(pointOnScreen, scene->cameraPosition);

				color = Trace(scene->cameraPosition, rayDirection, x, y);

				colorSum_r += color.m_r;
				colorSum_g += color.m_g;
				colorSum_b += color.m_b;
			}

			color.m_r = colorSum_r / samplesPerPixel;
			color.m_g = colorSum_g / samplesPerPixel;
			color.m_b = colorSum_b / samplesPerPixel;

			SDL_SetRenderDrawColor(Renderer, (Uint8) color.m_r, (Uint8) color.m_g, (Uint8) color.m_b, 0);

			SDL_RenderDrawPoint(Renderer, x, y);
		}
	}

	SDL_RenderPresent(Renderer);

	sceneRendered = true;
}

/* Ref: for setting up the project I used the following tutorial: https://www.youtube.com/watch?v=QQzAHcojEKg */
int main(int argc, char* argv[])
{
	scene = new Scene;
	ref = new Ray;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* Window = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int) scene->camera->SCREEN_WIDTH, (int) scene->camera->SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1, 0);

	SDL_SetRenderDrawColor(Renderer, 135, 206, 235, 0);
	SDL_RenderClear(Renderer);

	while (!quitApplication)
	{
		EventManagement();

		if (!sceneRendered)
		{
			RenderPixels(Renderer);
		}
	}

	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);

	delete ref;
	delete scene;

	return 0;
}