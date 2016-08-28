#ifndef _OBJECT_H
#define _OBJECT_H

#include "math.h"
#include "vect.h"
#include "color.h"

class Object {	
	public:
	
	Object ();

	//method man
	Color getObjectColor () { return Color (0.0, 0.0, 0.0, 0); }

	double findIntersection(Ray ray) {
		return 0;
	}

};

Object::Object () {}


#endif
