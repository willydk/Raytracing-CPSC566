/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 * 
 */

#include "Ray.h"
#include "Vectors.h"

#ifndef _CAMERA_H_
#define _CAMERA_H_

class Camera
{
public:
	inline virtual ~Camera(){};
	virtual Ray generateRay(Vec2f point) = 0;
};

#endif
