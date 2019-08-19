#include <circle.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265
#define euclid_distance(x, y, X, Y) sqrt((x-X)*(x-X)+(y-Y)*(y-Y))

CIRCLE* new_circle (float x, float y, float radius){
	CIRCLE* this_circle;
	this_circle = (CIRCLE*) malloc (sizeof(CIRCLE));
	this_circle->center = new_point(x, y);
	this_circle->radius = radius;
	return this_circle;
}

void del_circle (CIRCLE* this_circle){
	free(this_circle);
}

float area_circle (CIRCLE* this_circle){
	return PI * this_circle->radius * this_circle->radius;
}

POINT* get_circle_center (CIRCLE* this_circle){
	return this_circle->center;
}

float get_circle_radius (CIRCLE* this_circle){
	return this_circle->radius;
}


//The decision of implementing this function here is due to the previous inclusion of "point.c" functions, and thus
//there is already access to the abstract data type
float circle_point_dist (POINT* this_point, CIRCLE* this_circle){
	float diff = euclid_distance(get_coordinates(this_point, 0), 
						get_coordinates(this_point, 1),
						get_coordinates(get_circle_center(this_circle), 0),
						get_coordinates(get_circle_center(this_circle), 1));
	return diff;
}

