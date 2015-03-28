/* 
 * Wee Siang Wong
 * willydk@gmail.com	
 * CPSC 566
 * Spring 2012
 * CWID# 802852186
 *
 */

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "Vectors.h"

class Light 
{
public:
	Light() {}
	virtual ~Light() {}
	virtual void getIllumination (const Vec3f &p, Vec3f &dir, Vec3f &col) const = 0;
};

#endif
