#ifndef CIRCLE_H
#define CIRCLE_H
#include <point.h>

typedef struct circle_ {
	POINT* center;
	float radius;
} CIRCLE;
CIRCLE* new_circle (float x, float y, float radius);
void del_circle (CIRCLE* this_circle);
float area_circle (CIRCLE* this_circle);
POINT* get_circle_center (CIRCLE* this_circle);
float get_circle_radius (CIRCLE* this_circle);
float circle_point_dist (POINT* this_point, CIRCLE* this_circle);
#endif
