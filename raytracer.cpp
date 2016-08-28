
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "vect.h"
#include "ray.h"
#include "camera.h"
#include "color.h"
#include "light.h"
#include "object.h"
#include "sphere.h"
#include "plane.h"

using namespace std;

struct RGBtype {
	double r;
	double g;
	double b;

};
//-------------------BILD ERSTELLEN-----------------
void savebmp (const char *filename, int w, int h, int dpi, RGBtype *data) {
	FILE *f;
	int k = w*h
	int s = 4*k
	int filesize = 54 +  s;

	double factor = 39.375
	int m = static_cast<int>(factor);

	int ppm = dpi*m;
	unsigned char bmpfileheader[14] = {'B', 'M', 0,0,0,0, 0,0,0,0, 54,0,0,0);
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0);

	bmpfileheader[ 2] = (unsigned char)(filesize);
	bmpfileheader[ 3] = (unsigned char)(filesize>>8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(w);
	bmpinfoheader[ 5] = (unsigned char)(w>>8);
	bmpinfoheader[ 6] = (unsigned char)(w>>16);
	bmpinfoheader[ 7] = (unsigned char)(w>>24);

	bmpinfoheader[ 8] = (unsigned char)(h);
	bmpinfoheader[ 9] = (unsigned char)(h>>8);
	bmpinfoheader[10] = (unsigned char)(h>>16);
	bmpinfoheader[11] = (unsigned char)(h>>24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s>>8);
	bmpinfoheader[23] = (unsigned char)(s>>16);
	bmpinfoheader[24] = (unsigned char)(s>>24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm>>8);
	bmpinfoheader[27] = (unsigned char)(ppm>>16);
	bmpinfoheader[28] = (unsigned char)(ppm>>24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm>>8);
	bmpinfoheader[31] = (unsigned char)(ppm>>16);
	bmpinfoheader[32] = (unsigned char)(ppm>>24);

	f= fopen(filename, "wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);

	for (int i = 0; i < k; i++) {
	RGBtype rgb = data[i];
	
	double red = (data[i].r)*255;
	double green = (data[i].g)*255;
	double blue = (data[i].b)*255;

	unsigned char color[3] = {(int)floor(blue),(int)floor(green),(int)floor(red)}

	fwrite(color,1,3,f);
  }

  fclose(f);
}

int winningObjectIndex(vector<double> object_intersections) {
	//return the index of the winnning intersection
	int index_of_minimum_value;

	//prevent unnessary calculations
	if (object_intersections.size() == 0) {
		//if there are no intersections
		return -1;
	}
	else if (object_intersections.size() == 1) {
		if (object_intersections.at(0) > 0) {
		//if that intersection is greater than zero then its our index of minimum value
		return 0;
	}
	else {
		//otherwise the only intersection value is negative
		return -1;
	}
 }
 else {
       //otherwise there is more than one intersection
       //first find the max value

	double max = 0;
	for (int i = 0; i < object_intersections.size(); i++) {
		if (max < object_intersections.at(i)) {
		    max = object_intersections.at(i);		
		}
	}
	//then starting from the max value to find the minimum positive value
	if (max > 0) {
		//we only want positive intersections
		for (int index = 0; index < object_intersections.size(); index++) {
			if (object_intersections.at(index) > 0 && object_intersections.at(index) <= max) {
				max = object_intersections.at(index);
				index_of_minimum_value = index; //reset max value to min value
			}
		}
		return index_of_minimum_value;
	    }
	    else {
		//all the intersections were negative
		return -1;
		}
 	}
}


//-----------------FARBEN-----------------------------
int thisone;

int main (int argc, char *argv[]) {
	cout << "rendering ..." << endl;
	
	int dpi = 72;
	int width = 640;
	int height = 480;
	int n = width*height;
	RGBtype *pixels = new RGBtype [n];

	double aspectratio = (double)width/(double)height;

//Vektor Klasse-----------CAMERA-----------------
	Vect O (0,0,0);
	Vect X (1,0,0);
	Vect Y (0,1,0);
	Vect Z (0,0,1);

	Vect campos (3, 1.5, -4);

	Vect look_at (0, 0, 0);
	Vect diff_btw (campos.getVectX() - look_at.getVectX(), campos.getVectY() - look_at.getVectY(), campos.getVectZ() - look_at.getVectZ());

	Vect camdir = diff_btw.negative().normalize();
	Vect camright = Y.crossProduct(camdir).normalize();
	Vect camdown = camright.crossProdukt(camdir);
	Camera scene_cam (campos, camdir, camright, camdown);

	Color white_light (1.0, 1.0, 1.0, 0);
	Color pretty_green (0.5, 1.0, 0.5, 0.3);
	Color maroon (0.5, 0.25, 0.25, 0);
	Color gray (0.5, 0.5, 0.5, 0);
	Color black (0.0, 0.0, 0.0, 0);

	Vect light_position (-7,10,-10);
	Light scene_light (light_position, white_light);

	//scene objects------------------------------------

	Sphere scene_sphere (0, 1, pretty_green);
	Plane scene_plane (Y, -1, maroon); //placed plane beneath sphere
	
	vector<Object*> scene_objects;
	scene_objects.push_back(dynamic_cast<Object*>(&scene_sphere));
	scene_objects.push_back(dynamic_cast<Object*>(&scene_plane));

	double xamnt, yamnt; 


	//Loop für Matrix, Pixel werden Höhe/Breite abgegangen
	for (int x = 0, x < width; x++) {
		for (int y = 0, y < height; y++) {
			thisone = y*width + x;
//------------------------Height, Width Image--------------------------------------

			//start with no anti-aliasing
			if (width > height) {
				//the image is wider than it is tall
				xamnt = ((x+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
				yamnt = ((height - y) + 0.5)/height;
			}
			else if (height > width) {
				// the image is taller than its wide
				xamnt = (x + 0.5)/ width;
				yamnt = (((height - y) + 0.5)/height)/aspectratio - (((height - width)/(double)width/2);
				}
			else {
				//this image is square
				xamnt = (x + 0.5)/width;
				yamnt = ((height -y) +0.5)/height;			

			}

			Vect cam_ray_origin = scene_cam.getCameraPosition();
			Vect cam_ray_direction = camdir.vectAdd(camright.vectMult(xamnt - 0.5).vectAdd(camdown.vectMult(yamnt - 0.5))).normalize();
			//Ray cam-ray goes through the pixel to look for intersections
			Ray cam_ray (cam_ray_origin, cam_ray_direction);

			vector<double> intersections;

			for (int index = 0; index < scene_object.size(); index++) {
				intersections.push_back(scene_objects.at(index)->findIntersection(cam_ray));			
			}

			int index_of_winning_object = winningObjectIndex(intersections);
			//Index sorts our ray of intersections and returns index of winning object (same index of scene index objects)

			//return color
			if ((x > 200 && x < 440) && (y > 200 && y < 280)) { {
			pixels[thisone].r = 23;
			pixels[thisone].g = 222;
			pixels[thisone].b = 10;
			}
			else{
			pixels[thisone].r = 0;
			pixels[thisone].g = 0;
			pixels[thisone].b = 0;
			}

//--------------------FUNKTION--------------------------	
	
	 }
	}
	//Funktion
	savebmp("scene.bmp",width,height,dpi,pixels);

	return 0;
	}















