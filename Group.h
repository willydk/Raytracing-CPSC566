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

#include "Object3D.h"
#include <assert.h>
#include <memory.h>
 
#ifndef _GROUP_H_
#define _GROUP_H_

// Group class that holds all kinds of primitives, (currently just sphere)
class Group : public Object3D
{
public:
//-------------------------------------------------------------------------
	~Group()
	{
		my_nObjectNum = 0;
		if (my_pObjects)
		{
			delete[] my_pObjects;
			my_pObjects = NULL;
		}
	}
//-------------------------------------------------------------------------
	Group(int object_num)
	{
		my_nObjectNum = object_num;
		my_pObjects = new Object3D*[object_num];
		memset(static_cast<void*>(my_pObjects), 0x00, sizeof(Object3D*) * object_num);
	}
//-------------------------------------------------------------------------
	// adds the primitives to the selected group
	void addObject(int index, Object3D *obj)
	{
		assert(index < my_nObjectNum);
		assert(index >= 0);
		my_pObjects[index] = obj;
	}
//-------------------------------------------------------------------------
	// group intersect method
	bool Intersect(const Ray &r, Hit &h, float tmin) const
	{
		bool result = false;
		for (int i = 0; i < my_nObjectNum; i++)
		{
			assert(my_pObjects[i] != NULL);
			result |= my_pObjects[i]->Intersect(r, h, tmin);
		}
		return result;
	}
//-------------------------------------------------------------------------
protected:
	int my_nObjectNum;
	Object3D** my_pObjects;
};

#endif
