/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 */


#include "vectors.h"
#include <iostream>
;using namespace std;

#ifndef _RAY_H_
#define _RAY_H_

class Ray {

public:
	Ray () {}
	Ray (const Vec3f &dir, const Vec3f &ori) 
	{
		dirVector = dir;
		dirVector.Normalize();
		oriVector = ori; 
	}
	Ray (const Ray& r) {*this=r;}

	const Vec3f& getOrigin() const { return oriVector; }
	const Vec3f& getDirection() const { return dirVector; }
	Vec3f pointAtParameter(float t) const 
	{
		return oriVector+dirVector*t; 
	}

private:
	Vec3f dirVector;
	Vec3f oriVector;
};


#endif
