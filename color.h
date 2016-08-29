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

	//Farben manipulieren um Schatten herauszubekommen
	double brightness() {
		return(red + green + blue)/3;
	}

	Color colorScalar(double scalar) {
		return Color (red*scalar, green*scalar, blue*scalar, special);
	}

	Color colorAdd(Color color) {
		return Color (red + color.getColorRed(), green + color.getColorGreen(), blue + color.getColorBlue(), special);			
	}

	Color colorMultiply(Color color) {
		return Color (red*color.getColorRed(), green*color.getColorGreen(), blue*color.getColorBlue(), special);
	}
	
	Color colorAverage(Color color) {
		return Color ((red + color.getColorRed())/2, (green + color.getColorGreen())/2, (blue + color.getColorBlue())/2, special);

	//Method function: normalizes Color 
	Color clip() {
		double alllight = red + green + blue;
		double excesslight = allight - 3;
		if (excesslight > 0) {
			red = red + excesslight*(red/alllight);
			green = green + excesslight*(green/alllight);
			blue = blue + excesslight*(blue/alllight);
		}
		if (red > 1) {red = 1;}
		if (green > 1) {green = 1;}
		if (blue > 1) {blue = 1;}
		if (red < 0) {red = 0;}
		if (green < 0) {green = 0;}
		if (blue < 0) {blue = 0;}

		return Color (red, green, blue, special);
	   }
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
