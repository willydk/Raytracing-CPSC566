/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 * Same as assignment 1
 *
 */

#include "Camera.h"
#include "Vectors.h"

#ifndef _ORTHOGRAPHIC_CAMERA_H_
#define _ORTHOGRAPHIC_CAMERA_H_

class OrthographicCamera : public Camera
{
public:
//-------------------------------------------------------------------------
	/*
		setting up orthographic camera from the scene file that parsed in
		center, direction, up...
		width, height pixelsize...
	*/
	OrthographicCamera(const Vec3f &center, const Vec3f &direction, const Vec3f &up, float width, float height, float pixelsize)
	{
		my_center = center;
		my_direction = direction;
		my_direction.Normalize();
		my_up = up;
		my_up = my_up - my_direction * my_up.Dot3(my_direction);
		my_up.Normalize();
		Vec3f::Cross3(my_horizontal, my_direction, my_up);
		my_size = width = height;
		my_pixelsize = pixelsize;
	}
//-------------------------------------------------------------------------
	Ray generateRay(Vec2f point)
	{
		Vec3f origin =  my_center + my_horizontal * point.x() * my_size * 0.5 + my_up * point.y() * my_size * my_pixelsize * 0.5;
		return Ray(my_direction, origin);
	}
//-------------------------------------------------------------------------
protected:
	Vec3f my_center;
	Vec3f my_direction;
	Vec3f my_up;
	Vec3f my_horizontal;
	float my_size;
	float my_pixelsize;
};

#endif
