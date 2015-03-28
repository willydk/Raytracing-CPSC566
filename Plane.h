/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 * Added in assignment 2, Plane
 * Plane given a normal and an offset
 *
 */

#ifndef _PLANE_H_
#define _PLANE_H_

#include "Object3D.h"
#include <math.h>

class Plane : public Object3D
{
public:
	Plane(const Vec3f &normal, float d, const Vec3f &color)
	{
		my_normal = normal;
		// offset
		my_d = d;
		my_color = color;
	}

	bool Intersect(const Ray &r, Hit &h, float tmin) const
	{
		bool result= false;

		const Vec3f O = r.getOrigin();
		const Vec3f V = r.getDirection();
		float NdotV = my_normal.Dot3(V);

		if (NdotV != 0.0f)
		{
			float t = - (my_normal.Dot3(O) - my_d) / NdotV;
			if (t > tmin)
			{
				result = true;
				if ( t < h.getT())
					h.set(t, my_color, my_normal);
			}
		}
		return result;
	}

protected:
	Vec3f my_normal;
	float my_d;
	Vec3f my_color;
};

#endif
