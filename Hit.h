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

#ifndef _HIT_H_
#define _HIT_H_

class Hit{
  
public:
	Hit(const float _t, const Vec3f c, const Vec3f n) { t = _t; color = c; normal = n; }
	Hit(const Hit &h) { t = h.t; color = h.color; normal = h.normal; }
	~Hit() {}
	float getT() const { return t; }
	Vec3f getColor() const { return color; }
	Vec3f getNormal() const { return normal; }
	void set(const float _t, Vec3f c, const Vec3f n) { t = _t; color = c; normal = n;}

private: 
	float t;
	Vec3f color;
	Vec3f normal;
};

#endif
