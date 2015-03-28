/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 * Triangle.h, Probably the hardest coding/math combination to implement
 * First of all, we need to find out whether the ray is inside or outside of the 
 * three vertices that provided in the text file.
 * 
 */


#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Object3D.h"
#include <math.h>

class Triangle : public Object3D
{
public:
//-------------------------------------------------------------------------
	Triangle(const Vec3f &a, const Vec3f &b, const Vec3f &c, const Vec3f &color)
	{
		my_a = a;
		my_b = b;
		my_c = c;
		// (b-a) = beta axis
		// (c-a) = gama axis
		// n = (b-a) X (c-a) then normalize
		Vec3f::Cross3(my_normal, b - a, c - a);
		my_normal.Normalize();
		my_color = color;
		Vec3f tmp;
		my_asubb = a - b;
		my_asubc = a - c;
		// obtain tmp value of (a-b) X (a-c)
		Vec3f::Cross3(tmp, my_asubb, my_asubc);
	}
//-------------------------------------------------------------------------
	bool Intersect(const Ray &r, Hit &h, float tmin) const
	{
		bool result = false;
		// ori and dir
		const Vec3f O = r.getOrigin();
		const Vec3f V = r.getDirection();
		float NdotV = my_normal.Dot3(V);

		/*
			A = (a-b).x * (a-c).y * v.z +
			    (a-c).x * v.y * (a-b).z +
				v.x * (a-b).y * (a-c).z -
				v.x * (a-c).y * (a-b).z -
				(a-c).x * (a-b).y * v.z -
				(a-b).x * v.y * (a-c).z
		*/
		float A = 
		my_asubb.x() * my_asubc.y() * V.z() + 
		my_asubc.x() * V.y() * my_asubb.z() + 
		V.x() * my_asubb.y() * my_asubc.z() 
		- 
		V.x() * my_asubc.y() * my_asubb.z() - 
		my_asubc.x() * my_asubb.y() * V.z() - 
		my_asubb.x() * V.y() * my_asubc.z();

		if (NdotV != 0.0f)
		{
			Vec3f asubO = my_a - O;
			float t = 
			my_asubb.x() * my_asubc.y() * asubO.z() + 
			my_asubc.x() * asubO.y() * my_asubb.z() + 
			asubO.x() * my_asubb.y() * my_asubc.z()
			- 
			asubO.x() * my_asubc.y() * my_asubb.z() - 
			my_asubc.x() * my_asubb.y() * asubO.z() - 
			my_asubb.x() * asubO.y() * my_asubc.z();
			// t = A/t
			t /= A;

			if (t > tmin)
			{
				// calcuate beta and gama
				float beta = 
				asubO.x() * my_asubc.y() * V.z() + 
				my_asubc.x() * V.y() * asubO.z() + 
				V.x() * asubO.y() * my_asubc.z() 
				- 
				V.x() * my_asubc.y() * asubO.z() - 
				my_asubc.x() * asubO.y() * V.z() - 
				asubO.x() * V.y() * my_asubc.z();
				
				// beta = A/beta
				beta /= A;

				float gama = 
				my_asubb.x() * asubO.y() * V.z() +
				asubO.x() * V.y() * my_asubb.z() +
				V.x() * my_asubb.y() * asubO.z() 
				- 
				V.x() * asubO.y() * my_asubb.z() -
				asubO.x() * my_asubb.y() * V.z() -
				my_asubb.x() * V.y() * asubO.z();
 
				// gama = A/gama
				gama /= A;
				// return true it is inside of the beta gama coordinates system
				if (beta > 0 && gama > 0 && beta + gama < 1)
				{
					result = true;
					if ( t < h.getT())
					h.set(t, my_color, my_normal);
				}
			}
		}
		// return result, if its inside return true, outside then false
		return result;
	}
//-------------------------------------------------------------------------
protected:
	Vec3f my_a;
	Vec3f my_b;
	Vec3f my_c;
	Vec3f my_normal;
	Vec3f my_color;
private:
	Vec3f my_asubb;
	Vec3f my_asubc;
};

#endif
