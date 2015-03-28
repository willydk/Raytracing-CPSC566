/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 * Open courseware from MIT
 * http://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-837-computer-graphics-fall-2003/assignments/
 * with some modification
 *
 */

#include <stdio.h>
#include <string.h>
#include "Vectors.h"
#include "Scene.h"
#include "Camera.h"
#include "Orthographic_camera.h"
#include "Perspective_camera.h" 
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Object3d.h"
#include "Group.h" 
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "common.h"

//-------------------------------------------------------------------------
Scene::Scene() 
{
	initialize();
}
//-------------------------------------------------------------------------
Scene::Scene(const char* filename) 
{
	initialize();

	// open the file
	assert(filename != NULL);
	const char *ext = &filename[strlen(filename)-4];
	assert(!strcmp(ext,".txt"));
	file = fopen(filename,"r");
	assert (file != NULL);

	// parse the scene
	parseFile();

	// close the file
	fclose(file); 
	file = NULL;
}
//-------------------------------------------------------------------------
Scene::~Scene() 
{
	if (group != NULL) 
		delete group;
	if (camera != NULL) 
		delete camera;
}
//-------------------------------------------------------------------------
void Scene::initialize() 
{
	group = NULL;
	camera = NULL;
	background_color = Vec3f(0.5,0.5,0.5);
	lights = NULL;
	num_lights = 0;
	ambient_light = Vec3f(1.0,1.0,1.0);
	current_object_color = Vec3f(1,1,1);
	file = NULL;
}
//-------------------------------------------------------------------------
void Scene::parseFile() 
{
	/* 
		parse the whole file, starting from OrthographicCamera
		or Perspective Camera
		to Background to Lights then Group, then the Group parses the 
		Material and the spheres, or other primitives (plane/triangle)
	*/
	char token[MAX_PARSER_TOKEN_LENGTH];    
	while (getToken(token)) 
	{ 
		if (!strcmp(token, "OrthographicCamera")) 
		{
			parseOrthographicCamera();
		} 
		else if (!strcmp(token, "PerspectiveCamera")) 
		{
			parsePerspectiveCamera();
		} 
		else if (!strcmp(token, "Background")) 
		{
			parseBackground();
		} 
		else if (!strcmp(token, "Lights")) 
		{
			parseLights();
		} 
		else if (!strcmp(token, "Group")) 
		{
			group = parseGroup();
		} 
		else 
		{
			printf ("Unknown token in parseFile: '%s'\n", token);
			exit(0);
		}
	}
}
//-------------------------------------------------------------------------
Group* Scene::parseGroup() 
{
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token); assert (!strcmp(token, "{"));

	// read in the number of objects
	getToken(token); assert (!strcmp(token, "numObjects"));
	int num_objects = readInt();

	Group *answer = new Group(num_objects);

	// read in the objects
	int count = 0;
	while (num_objects > count) 
	{
		getToken(token); 
		// parse the Material for current group
		if (!strcmp(token, "Material")) 
		{
			parseMaterial();
		} 
		else 
		{
			// parse Objects in the group, could be sphere/plane/triangle
			Object3D *object = parseObject(token);
			assert (object != NULL);
			answer->addObject(count,object);
			count++;
		}
	}
	getToken(token); assert (!strcmp(token, "}"));

	// return the group
	return answer;
}
//-------------------------------------------------------------------------
Object3D* Scene::parseObject(char token[MAX_PARSER_TOKEN_LENGTH]) 
{
	Object3D *answer = NULL;
	if (!strcmp(token, "Group")) 
	{      
		answer = (Object3D*)parseGroup();
	}	
	else if (!strcmp(token, "Sphere")) 
	{      
		answer = (Object3D*)parseSphere();
	} 
	else if (!strcmp(token, "Plane")) 
	{      
		answer = (Object3D*)parsePlane();
	}
	else if (!strcmp(token, "Triangle")) 
	{      
		answer = (Object3D*)parseTriangle();
	} 
	else if (!strcmp(token, "TriangleMesh")) 
	{      
		answer = (Object3D*)parseTriangleMesh();
	} 
	else 
	{
		printf ("Unknown token in parseObject: '%s'\n", token);
		exit(0);
	}
	return answer;
}
//-------------------------------------------------------------------------
void Scene::parseLights() 
{
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token); assert (!strcmp(token, "{"));

	// read in the number of objects
	getToken(token); assert (!strcmp(token, "numLights"));
	num_lights = readInt();
	lights = new Light*[num_lights];

	// read in the objects
	int count = 0;
	while (num_lights > count) 
	{
		getToken(token); 
		if (!strcmp(token, "PointLight")) 
		{
			getToken(token); assert (!strcmp(token, "{"));
			getToken(token); assert (!strcmp(token, "position"));
			Vec3f position = readVec3f();
			getToken(token); assert (!strcmp(token, "color"));
			Vec3f color = readVec3f();
			getToken(token); assert (!strcmp(token, "}"));

			lights[count] = new PointLight(position,color);
			count++;
		}
		else if (!strcmp(token, "DirectionalLight")) 
		{
			getToken(token); assert (!strcmp(token, "{"));
			getToken(token); assert (!strcmp(token, "position"));
			Vec3f position = readVec3f();
			getToken(token); assert (!strcmp(token, "direction"));
			Vec3f direction = readVec3f();
			getToken(token); assert (!strcmp(token, "color"));
			Vec3f color = readVec3f();
			getToken(token); assert (!strcmp(token, "angle"));
			float angle = readFloat();
			getToken(token); assert (!strcmp(token, "}"));

			lights[count] = new DirectionalLight(position,direction,color,angle);
			count++;
		} 
		else 
		{
			printf ("Unknown token in parseLights: '%s'\n", token);
			exit(0);
		}   
	}
	getToken(token); assert (!strcmp(token, "}"));
}
//-------------------------------------------------------------------------
void Scene::parseOrthographicCamera() 
{
	char token[MAX_PARSER_TOKEN_LENGTH];

	// read in the camera parameters
	getToken(token); assert (!strcmp(token, "{"));
	getToken(token); assert (!strcmp(token, "center"));
	Vec3f center = readVec3f();
	getToken(token); assert (!strcmp(token, "direction"));
	Vec3f direction = readVec3f();
	getToken(token); assert (!strcmp(token, "up"));
	Vec3f up = readVec3f();
	getToken(token); assert (!strcmp(token, "width"));
	float width = readFloat();
	getToken(token); assert (!strcmp(token, "height"));
	float height = readFloat();
	getToken(token); assert (!strcmp(token, "pixelsize"));
	float pixelsize = readFloat();
	getToken(token); assert (!strcmp(token, "}"));

	// set camera to the orthographic camera values that parsed in
	camera = new OrthographicCamera(center,direction,up,width,height,pixelsize);
}
//-------------------------------------------------------------------------
void Scene::parsePerspectiveCamera() 
{
	char token[MAX_PARSER_TOKEN_LENGTH];

	// read in the camera parameters
	getToken(token); assert (!strcmp(token, "{"));
	getToken(token); assert (!strcmp(token, "center"));
	Vec3f center = readVec3f();
	getToken(token); assert (!strcmp(token, "direction"));
	Vec3f direction = readVec3f();
	getToken(token); assert (!strcmp(token, "up"));
	Vec3f up = readVec3f();
	getToken(token); assert (!strcmp(token, "angle"));
	float angle_degrees = readFloat();
	float angle_radians = DegreesToRadians(angle_degrees);
	getToken(token); assert (!strcmp(token, "}"));

	// set camera to the perspective camera values that parsed in
	camera = new PerspectiveCamera(center,direction,up,angle_radians);
}
//-------------------------------------------------------------------------
void Scene::parseBackground() 
{
	char token[MAX_PARSER_TOKEN_LENGTH];
	// read in the background color
	getToken(token); assert (!strcmp(token, "{"));  
	while (1) 
	{
		getToken(token); 
		if (!strcmp(token, "}")) 
		{ 
			break;  
		} 
		else if (!strcmp(token, "color")) 
		{
			background_color = readVec3f();
		} 
		else if (!strcmp(token, "ambientLight")) 
		{
			ambient_light = readVec3f();
		} 
		else 
		{
			printf ("Unknown token in parseBackground: '%s'\n", token);
			assert(0);
		}
	}
}
//-------------------------------------------------------------------------
void Scene::parseMaterial() 
{
	char token[MAX_PARSER_TOKEN_LENGTH];
	// read in the material color
	getToken(token); assert (!strcmp(token, "{"));
	getToken(token); assert (!strcmp(token, "diffuseColor"));
	// set the current object color
	current_object_color = readVec3f();
	getToken(token); assert (!strcmp(token, "}"));
}
//-------------------------------------------------------------------------
Sphere* Scene::parseSphere() 
{
	char token[MAX_PARSER_TOKEN_LENGTH];

	// read in the sphere parameters
	getToken(token); assert (!strcmp(token, "{"));
	getToken(token); assert (!strcmp(token, "center"));
	Vec3f center = readVec3f();
	getToken(token); assert (!strcmp(token, "radius"));
	float radius = readFloat();
	getToken(token); assert (!strcmp(token, "}"));

	// return the values for current sphere
	return new Sphere(center,radius,current_object_color);
}
//-------------------------------------------------------------------------
Plane* Scene::parsePlane() 
{
	char token[MAX_PARSER_TOKEN_LENGTH];

	// read in the sphere parameters
	getToken(token); assert (!strcmp(token, "{"));
	getToken(token); assert (!strcmp(token, "normal"));
	Vec3f normal = readVec3f();
	getToken(token); assert (!strcmp(token, "offset"));
	float offset = readFloat();
	getToken(token); assert (!strcmp(token, "}"));

	// return the values for current plane
	return new Plane(normal,offset,current_object_color);
}
//-------------------------------------------------------------------------
Triangle* Scene::parseTriangle() 
{
	char token[MAX_PARSER_TOKEN_LENGTH];

	// read in the sphere parameters
	getToken(token); assert (!strcmp(token, "{"));
	getToken(token); assert (!strcmp(token, "vertex0"));
	Vec3f v0 = readVec3f();
	getToken(token); assert (!strcmp(token, "vertex1"));
	Vec3f v1 = readVec3f();
	getToken(token); assert (!strcmp(token, "vertex2"));
	Vec3f v2 = readVec3f();
	getToken(token); assert (!strcmp(token, "}"));

	// return the values for current triangle
	return new Triangle(v0,v1,v2,current_object_color);
}
//-------------------------------------------------------------------------
Group* Scene::parseTriangleMesh() 
{
	char token[MAX_PARSER_TOKEN_LENGTH];
	char filename[MAX_PARSER_TOKEN_LENGTH];

	// get the filename
	getToken(token); assert (!strcmp(token, "{"));
	getToken(filename); 
	getToken(token); assert (!strcmp(token, "}"));
	const char *ext = &filename[strlen(filename)-4];
	assert(!strcmp(ext,".txt"));

	// read it once, get counts
	FILE *file = fopen(filename,"r");
	assert (file != NULL);
	int vcount = 0; int fcount = 0;
	while (1) 
	{
		int c = fgetc(file);
		if (c == EOF) 
		{ 
			break;
		} 
		else if (c == 'v') 
		{ 
			  assert(fcount == 0); float v0,v1,v2;
			  fscanf (file,"%f %f %f",&v0,&v1,&v2);
			  vcount++; 
		} 
		else if (c == 'f') 
		{
			int f0,f1,f2;
			fscanf (file,"%d %d %d",&f0,&f1,&f2);
			fcount++; 
		} 
	}
	fclose(file);

	// make arrays
	Vec3f *verts = new Vec3f[vcount];
	Group *answer = new Group(fcount);

	// read it again, save it
	file = fopen(filename,"r");
	assert (file != NULL);
	int new_vcount = 0; int new_fcount = 0;
	while (1) 
	{
		int c = fgetc(file);
		if (c == EOF) 
		{ 
			break;
		} 
		else if (c == 'v') 
		{ 
			assert(new_fcount == 0); float v0,v1,v2;
			fscanf (file,"%f %f %f",&v0,&v1,&v2);
			verts[new_vcount] = Vec3f(v0,v1,v2);
			new_vcount++; 
		} 
		else if (c == 'f') 
		{
			assert (vcount == new_vcount);
			int f0,f1,f2;
			fscanf (file,"%d %d %d",&f0,&f1,&f2);
			
			assert (f0 > 0 && f0 <= vcount);
			assert (f1 > 0 && f1 <= vcount);
			assert (f2 > 0 && f2 <= vcount);

			Triangle *t = new Triangle(verts[f0-1],verts[f1-1],verts[f2-1],
			current_object_color);			

			answer->addObject(new_fcount,t);
			new_fcount++; 
		} 
	}
	delete [] verts;
	assert (fcount == new_fcount);
	assert (vcount == new_vcount);
	fclose(file);
	return answer;
}
//-------------------------------------------------------------------------
int Scene::getToken(char token[MAX_PARSER_TOKEN_LENGTH]) 
{
	// for simplicity, tokens must be separated by whitespace
	assert (file != NULL);
	int success = fscanf(file,"%s ",token);
	if (success == EOF) 
	{
		token[0] = '\0';
		return 0;
	}
	return 1;
}
//-------------------------------------------------------------------------
Vec3f Scene::readVec3f() 
{
	float x,y,z;
	int count = fscanf(file,"%f %f %f",&x,&y,&z);
	if (count != 3) 
	{
		printf ("Error trying to read 3 floats to make a Vec3f\n");
		assert (0);
	}
	return Vec3f(x,y,z);
}
//-------------------------------------------------------------------------
float Scene::readFloat() 
{
	float answer;
	int count = fscanf(file,"%f",&answer);
	if (count != 1) 
	{
		printf ("Error trying to read 1 float\n");
		assert (0);
	}
	return answer;
}
//-------------------------------------------------------------------------
int Scene::readInt() 
{
	int answer;
	int count = fscanf(file,"%d",&answer);
	if (count != 1) 
	{
		printf ("Error trying to read 1 int\n");
		assert (0);
	}
	return answer;
}
//-------------------------------------------------------------------------
// end of Scene.cpp
