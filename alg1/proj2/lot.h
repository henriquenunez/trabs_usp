#ifndef _PARKING_LOT_H
#define _PARKING_LOT_H

//rules and everyting

typedef struct _parking_lot  PARKING_LOT;

PARKING_LOT* lot_create();
int lot_purge(PARKING_LOT*);
int register_car(PARKING_LOT*, int, int, int);
char* car_list();

#endif
