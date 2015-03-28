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

#include "Vectors.h"
#include "Ray.h"
#include "Hit.h"

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

class Object3D
{
public:
	inline virtual ~Object3D(){};
	virtual bool Intersect(const Ray &r, Hit &h, float tmin) const  = 0;
protected:
	Vec3f my_diffColor;
};

#endif
