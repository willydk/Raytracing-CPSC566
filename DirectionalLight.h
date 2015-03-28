/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 * Added in assignment 3
 *
 */

#ifndef _DIRECTIONALLIGHT_H_
#define _DIRECTIONALLIGHT_H_

#include "Light.h"
#include "Vectors.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight()
	{
		position = Vec3f(0,0,0);
		direction = Vec3f(0,0,-1);
		color = Vec3f(1,1,1);
		angle = 15;
	}
	DirectionalLight(const Vec3f &p, const Vec3f &dir, const Vec3f &c, float &a)
	{
		position = p; position.Normalize();
		direction = dir; direction.Normalize();
		color = c;
		angle = a;
	}
	virtual ~DirectionalLight(){}
	void getIllumination( const Vec3f &p, Vec3f &dir, Vec3f &col) const
	{
		dir = direction ;
		col = color;
	}
private: 
	Vec3f position;
	Vec3f direction;
	Vec3f color;
	float angle;
}
#endif
