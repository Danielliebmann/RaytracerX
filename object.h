#ifndef _SHAPE_H
#define _SHAPE_H

#include "math.h"
#include "vect.h"
#include "color.h"

class Shape {	
	public:
	
	Shape ();

	//method man
	virtual Color getColor () { return Color (0.0, 0.0, 0.0, 0); }

	virtual Vect getNormalAt(Vect intersection_position) {
		return Vect (0, 0, 0);
		}

	virtual double findIntersection(Ray ray) {
		return 0;
	}

};

Shape::Shape () {}


#endif
