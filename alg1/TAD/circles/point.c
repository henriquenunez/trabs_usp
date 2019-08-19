#include <point.h>
#include <stdlib.h>

POINT* new_point(float x, float y){
	POINT* this_point;
	this_point = (POINT*) malloc(sizeof(POINT));
	this_point->x = x;
	this_point->y = y;
	return this_point;
}

void del_point (POINT* this_point){
	free(this_point);
}

bool set_point (POINT* this_point, float x, float y){
	if (this_point == NULL || (sizeof(*this_point) != sizeof(POINT))) { //checks wether pointer exists, and at least the same type
		return false;
	}
	this_point->x = x;
	this_point->y = y;
	return true;
}

float get_coordinates(POINT* this_point, bool axis){ //0 for x, 1 for y
	if(axis){
		return this_point->y;
	} else {
		return this_point->x;
	}
} 