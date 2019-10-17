#include <stdlib.h>

#include "defines.h"
#include "lot.h"
#include "stack.h"
#include "queue.h"

typedef struct _car
{
	int plate;
	int timeArrival;
	int stayPeriod;
} CAR;


struct _parking_lot
{
	STACK* P;
	unsigned int P_cars;
	unsigned int P_first_hour;

	QUEUE* F;
	unsigned int F_cars;
	unsigned int F_last_hour;
	
};

int check_availability(PARKING_LOT*);


PARKING_LOT* lot_create()
{
	PARKING_LOT* new_lot = (PARKING_LOT*) malloc (sizeof(PARKING_LOT));
	new_lot->P = stack_create();
	new_lot->P_cars = 0;
	new_lot->F = queue_create();
	new_lot->F_cars = 0;

	return new_lot;
}


int register_car(PARKING_LOT* this_lot, int plate, int arrival, int stay)
{
	CAR* new_car = (CAR*) malloc (sizeof(CAR));
	CAR* holder;

	new_car->plate = plate;
	new_car->timeArrival = arrival;
	new_car->stayPeriod = stay;

	if (this_lot->P_cars == 0)
	{
		//park on F
		return stack_push(this_lot->P, new_car);;
	}
	else if (this_lot->F_cars == 0)
	{
		//park on P
		return queue_append(this_lot->F, new_car);;
	}
	else
	{
		if ( (holder = (CAR*)queue_call(this_lot->F)) != NULL)
		{
			//reinsert on queue
			queue_append(this_lot->F, holder);
			if ( (holder->timeArrival + holder->stayPeriod) >= this_lot->F_last_hour)
			{
				this_lot->F_last_hour = arrival + stay;
				return queue_append(this_lot->F, new_car);
			}
		}

		if ( (holder = (CAR*)stack_pop(this_lot->P)) != NULL)
		{
			//reinsert on stack
			stack_push(this_lot->P, holder);
			if ( (holder->timeArrival + holder->stayPeriod) <= this_lot->P_first_hour)
			{
				this_lot->P_first_hour = arrival + stay;
				return stack_push(this_lot->P, new_car);
			}
		}
	} 
	/*Couldn't find vacancy*/
	free(new_car);

	return NOT_AVAILABLE;
}

char* car_list(PARKING_LOT* this_lot)
{
	//alloc the *exact space* for making a string out of the printed cars

	//sprintf("%4d %d %2.2f", ); format output for cars
}

int lot_purge(PARKING_LOT* this_lot)
{
	stack_purge(this_lot->P);
	queue_purge(this_lot->F);
	free(this_lot);

	return OK;
}
