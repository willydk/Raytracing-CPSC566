/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 * Added in assignment 2, perspective camera
 *
 */

#ifndef _PERSPECTIVE_CAMERA_H_
#define _PERSPECTIVE_CAMERA_H_

#include "Camera.h"
#include "Vectors.h"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(const Vec3f &center, const Vec3f &direction, const Vec3f &up, float angle)
	{
		/*
			stored the values that parsed in from the file 
		*/
		my_center = center;
		my_direction = direction;
		my_direction.Normalize();
		my_up = up;
		// up = up - dir* up (dot) dir
		my_up = my_up - my_direction * my_up.Dot3(my_direction);
		my_up.Normalize();
		// hoirzontal = dir X up
		Vec3f::Cross3(my_horizontal, my_direction, my_up);
		my_angle = angle;
	}

	Ray generateRay(Vec2f point)
	{
		float size = tan(my_angle / 2.0f) * 2.0f;
		Vec3f direction =  my_horizontal * (point.x() - 0.5) * size + my_up * ( point.y() - 0.5) * size + my_direction;
		return Ray(direction, my_center);
	}

protected:
	Vec3f my_center;
	Vec3f my_direction;
	Vec3f my_up;
	Vec3f my_horizontal;
	float my_angle;

};

#endif


  
