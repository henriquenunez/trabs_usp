#ifndef POINT_H
#define POINT_H
#include <stdbool.h>

typedef struct _point{
	float x;
	float y;
} POINT;

POINT* new_point(float x, float y);
void del_point (POINT* this_point);
bool set_point (POINT* this_point, float x, float y);
float get_coordinates(POINT* this_point, bool axis); //0 for x, 1 for y

#endif
