#ifndef _LIGHT_H
#define _LIGHT_H

#include "source.h"
#include "vect.h"
#include "color.h"

class Light : public Source {
	Vect position;
	Color color;
	
	public:
	
	Light ();
	
	Light (Vect, Color);

	//get functions
	//------------VIrtual Funktion??
	virtual Vect getLightPosition () { return position; }
	virtual Color getLightColor () {return color; }


};

Light::Light () {
	position = Vect(0,0,0);
	color = Color(1,1,1, 0);
	
}

Light::Light (Vect p, Color c) {
	position = p;
	color = c;
}

#endif
