/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 * Assignment 3 - Mopr Ray Tracing
 * Add Directional Light and Shadow calculation
 * 
 * Since assignment does not need depth file, so I will just comment the code out
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <iostream>

#include "getopt.h"
#include "Ray.h"
#include "Hit.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Camera.h"
#include "Orthographic_Camera.h"
#include "Perspective_Camera.h"
#include "Group.h"
#include "Scene.h"
#include "Image.h"

double min_depth, max_depth;
string gProgramName;
int resolution;

void dispSceneSummary(char *inputFile, char *outputFile, //char *depthFile ,
					  int resolution)
{
	printf("\n==============================");
	printf("\n Scene Summary		  ");
	printf("\n---------------");
	printf("\n Scene File: %s", inputFile);
	printf("\n Output File: %s", outputFile);
//	printf("\n Depth File: %s", depthFile);
	printf("\n Resolution: %dx%d", resolution, resolution);
	printf("\n==============================");
	printf("\n");
}

void usage( string message = "" ){
	cerr << message << endl;
	// assign 1
	//cerr << gProgramName << " <inputfile> <outputfile> <depthfile> <resolution>" << endl;
	// assign 2
	cerr << gProgramName << " <inputfile> <outputfile> <resolution>" << endl;
}


int main (int argc, char** argv)
{
	gProgramName = argv[0];
	if (argc < 4 )
	{
		usage();
	}
	else
	{
		char * inputFile = argv[1];
		char * outputFile = argv[2];
		//char * depthFile = argv[3];
		//resolution = atoi(argv[4]);
		resolution = atoi(argv[3]);

		//int min_depth = 8;
		//int max_depth = 14;

		Scene sp(inputFile);
		Camera *cam = sp.getCamera();
		Group *group = sp.getGroup();
		int light_num = sp.getNumLights();
		Vec3f bg_color = sp.getBackgroundColor();
		Vec3f ambient = sp.getAmbientLight();
		Image color_img(resolution, resolution);
		color_img.SetAllPixels(bg_color);
		//Image depth_img(resolution, resolution);
		//depth_img.SetAllPixels(Vec3f(0.0f, 0.0f, 0.0f));


		int i, j, k;
		//int precalc = max_depth - min_depth;
		//if (precalc == 0) precalc = 1;
		dispSceneSummary(inputFile, outputFile, //depthFile, 
			resolution);

		// Rendering Start
		for ( j = 0; j < resolution; j++)
		{
			for ( i = 0; i < resolution; i++)
			{
				float x = (float) i / resolution;
				float y = (float) j / resolution;
				Ray ray = cam->generateRay(Vec2f(x, y));
				Hit h(99999, bg_color, Vec3f(0.0f, 0.0f, 1.0f));
				float tmin = 0.0f;
				if (group->Intersect(ray, h, tmin))
				{
					Vec3f color = h.getColor();
					Vec3f pixel (ambient.r() * color.r(), ambient.g() * color.g(), ambient.b() * color.b());

					float t = h.getT();
					Vec3f p = ray.getOrigin() + ray.getDirection() * t;
					Vec3f n = h.getNormal();
					// calculate the lighting on the current pixel
					for ( k = 0; k < light_num; k++)
					{
						Light *light = sp.getLight(k);
						Vec3f dir;
						Vec3f col;
						light->getIllumination(p, dir, col);
						float diffuse = dir.Dot3(n);
						if (diffuse < 0) diffuse = 0;
						pixel += Vec3f(color.r() * col.r(), color.g() * col.g(), color.b() * col.b()) * diffuse;

						/*
							generate a shadow ray from the current hit object to the light source,
							if there is another object between the two, then shadow the current hit object.
						*/
						Ray shadowRay = Ray(dir, p);
						if(group->Intersect(shadowRay,h,tmin))
						{
							pixel += Vec3f(0.05,0.05,0.05);
						}

					}
				
				color_img.SetPixel(i, j, pixel);
				// calculate the depth image 
				/*
				if (t >= min_depth && t <= max_depth)
				{ 
					float volumn = (max_depth - t) / precalc;
					depth_img.SetPixel(i, j, Vec3f(volumn, volumn, volumn));
				}*/
			}
		}
	}
	// Rendering End

	// Output
	color_img.SavePPM(outputFile);
	//depth_img.SavePPM(depthFile);
	}
	return 0;
}
