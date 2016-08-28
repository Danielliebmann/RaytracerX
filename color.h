#ifndef _COLOR_H
#define _COLOR_H

class Color {
	double red, green, blue, special;
	
	public:
	
	Color ();
	
	Color (double, double, double, double);

	//method functions
	double getColorRed() { return red; }
	double getColorGreen() { return green; }
	double getColorBlue() { return blue; }
	double getColorSpecial() { return special; }

	double set ColorRed(double redValue) {red = redValue};
	double set ColorGreen(double greenValue) {green = greenValue};
	double set ColorBlue(double blueValue) {blue = blueValue};
	double set ColorSpecial(double specialValue) {special = specialValue};
	};

Color::Color (double i, double j, double k) {
	x = 0;
	y = 0;
	z = 0;
}
Color::Color (double r, double g, double b, double s) {
	red = r;
	green = g;
	blue = b;
	special = s;
}

#endif
