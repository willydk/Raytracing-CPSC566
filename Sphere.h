/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 */

#include "Object3D.h"
#include <math.h>

#ifndef _SPHERE_H_
#define _SPHERE_H_

class Sphere : public Object3D
{
public:
//-------------------------------------------------------------------------
	Sphere(const Vec3f &center, float radius, const Vec3f &diffColor)
	{
		my_center = center;
		my_radius = radius;
		my_diffColor  = diffColor;
	}
//-------------------------------------------------------------------------
	bool Intersect(const Ray &r, Hit &h, float tmin) const
	{
		bool result = false;
		// direction where ray going
		Vec3f V = r.getDirection();
		// origin where the ray from
		Vec3f O = r.getOrigin();
		Vec3f tmp = O - my_center;
		float dist = tmp.Length();
		// solve the quadratic equation to find the intersection
		float a = V.Dot3(V);
		float b = 2.0f * V.Dot3(tmp);
		float c = dist * dist - my_radius * my_radius;
		// find discriminant
		float disc = b * b - 4 * a * c;
		float t = 0;

		if (disc > 0)
		{
			float val = 1.0f / (2.0f * a);
			float t1 = (-b - sqrt(disc)) * val;
			float t2 = (-b + sqrt(disc)) * val;

			if ( t1 >= tmin )
				t = t1;
			else if ( t2 >= tmin )
				t = t2;
			if ( t < h.getT() )
			{
				Vec3f n = tmp + V * t;
				n.Normalize();
				h.set(t, my_diffColor, n);
			}
			result = true;
		}
		else
			result = false;
		return result;
	}
//-------------------------------------------------------------------------
protected:
	Vec3f my_center;
	float my_radius;
};

#endif
