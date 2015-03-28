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
 */

#ifndef _Scene_H_
#define _Scene_H_

#include "Vectors.h"

class Camera;
class Light;
class Object3D;
class Group;
class Sphere;
class Plane;
class Triangle;

#define MAX_PARSER_TOKEN_LENGTH 100

class Scene 
{
public:
	// CONSTRUCTORS, DESTRUCTOR & INITIALIZE
	Scene();
	Scene(const char *filename);
	~Scene();

	// ACCESSORS
	Camera* getCamera() { return camera; }
	Vec3f getBackgroundColor() { return background_color; }
	Vec3f getAmbientLight() { return ambient_light; }
	int getNumLights() { return num_lights; }
	Light* getLight(int i) { 
	assert(i >= 0 && i < num_lights); 
	return lights[i]; }  
	Group* getGroup() { return group; }

private:
	// HELPER FUNCTIONS
	void initialize();
	int getToken(char token[MAX_PARSER_TOKEN_LENGTH]);
	Vec3f readVec3f();
	float readFloat();
	int readInt();

	// PARSING
	void parseFile();
	void parseOrthographicCamera();
	void parsePerspectiveCamera();
	void parseBackground();
	void parseLights();
	void parseMaterial();
	Object3D* parseObject(char token[MAX_PARSER_TOKEN_LENGTH]);
	Group* parseGroup();
	Sphere* parseSphere();
	Plane* parsePlane();
	Triangle* parseTriangle();
	Group* parseTriangleMesh();

	// REPRESENTATION
	Group *group;
	Camera *camera;
	Vec3f background_color;
	Vec3f ambient_light;
	Vec3f current_object_color;
	FILE *file;
	Light **lights;
	int num_lights;
};
#endif

