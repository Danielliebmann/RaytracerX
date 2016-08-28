#ifndef _PLANE_H
#define _PLANE_H

#include "math.h"
#include "vect.h"
#include "object.h"
#include "color.h"

//Hier bekommen wir die "Normale" des Punktes, den wir schneiden (Intersect). Der Normalvektor beim intersect ist der Normalvektor der Ebene (Plane)

class Plane : public Object {
	Vect normal;
	double distance;
	Color color;
	
	public:
	
	Plane ();
	
	Plane (Vect, double, Color);

	//method man
	Vect getPlaneNormal () { return normal; }
	double getPlaneDistance () { return distance; }
	Color getPlaneColor () { return color; }

	Vect getNormalAt(Vect point) {
		return normal;
	}
	//double = distance ray origin to point of intersection
	double findIntersection(Ray ray) {
		Vect ray_direction = ray.getRayDirection();
	
	double a = ray_direction.dotProduct(normal);
	
	if (a == 0) {
		//ray is parallel to the plane
		return -1;	
	}
	else {
		double b = normal.dotProduct(ray.getRayOrigin().vectAdd(normal.vectMult(distance).negative())); //b ist x produkt zwischen Normalvektor und einem anderen Vektor, Result = komponenten in entgegengesetzter Richtung der Ray.origin (MUltiplikation Distance Normalized, Ray.origin reversed)
		return -1*b/a; //distance from ray origin to point of intersection
	}		
       }

};

Plane::Plane () {
	normal = Vect(1,0,0);
	distance = 0;
	color = Color(0.5,0.5,0.5, 0);
	
}

Plane::Plane (Vect normalValue, double distanceValue, Color colorValue c) {
	normal = normalValue;
	distance = distanceValue;
	color = colorValue;
}

#endif

