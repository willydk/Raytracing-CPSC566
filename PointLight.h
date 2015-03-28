/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 */

#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include "Light.h"
#include "Vectors.h"

class PointLight : public Light 
{
public:
	PointLight() 
	{ 
		position = Vec3f(0,0,0);
		color = Vec3f(1,1,1); 
	}
	PointLight(const Vec3f &p, const Vec3f &c) 
	{
		position = p; position.Normalize();
		color = c; 
	}
	virtual ~PointLight() {}

	void getIllumination (const Vec3f &p, Vec3f &pos, Vec3f &col) const 
	{
		pos = position;
		col = color; 
	}

private:
	Vec3f position;
	Vec3f color;
};

#endif
