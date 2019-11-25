#include <stdlib.h>
#include <stdio.h>

#include "defines.h"
#include "lot.h"
#include "stack.h"
#include "queue.h"

/*TODO:
comment the project
sprintf instead of printf
*/

typedef struct _car
{
	int plate;
	int timeArrival;
	int timeDeparture;
	float price;
	int discount;
} CAR;

struct _parking_lot
{
	STACK* P;
	unsigned int P_hour;

	QUEUE* F;
	unsigned int F_hour;

	unsigned int lastArrive;	
};

int check_availability(PARKING_LOT*);

PARKING_LOT* lot_create()
{
	PARKING_LOT* new_lot = (PARKING_LOT*) malloc (sizeof(PARKING_LOT));
	new_lot->P = stack_create();
	new_lot->F = queue_create();

	new_lot->lastArrive = 8;	//the parking opens at 8

	return new_lot;
}


int register_car(PARKING_LOT* this_lot, int plate, int arrival, int stay)
{
	if(check_availability(this_lot, plate, arrival, stay) == NOT_AVAILABLE)
		return NOT_AVAILABLE;	

	CAR* new_car = (CAR*) malloc (sizeof(CAR));

	new_car->plate = plate;
	new_car->timeArrival = arrival;
	new_car->timeDeparture = arrival + stay;
	new_car->price = stay*3;
	new_car->discount = 0;

	if (stack_get_num(this_lot->P) == 0)
	{
		//park on F
		this_lot->P_hour = new_car->timeDeparture;
		this_lot->lastArrive = arrival;
		return stack_push(this_lot->P, new_car);;
	}
	else if (queue_get_num(this_lot->F) == 0)
	{
		//park on P
		this_lot->F_hour = new_car->timeDeparture;
		this_lot->lastArrive = arrival;
		return queue_append(this_lot->F, new_car);;
	}
	else
	{
		if (new_car->timeDeparture >= this_lot->F_hour)
		{
			this_lot->F_hour = new_car->timeDeparture;
			return queue_append(this_lot->F, new_car);
		}

		if (new_car->timeDeparture <= this_lot->P_hour)
		{
			this_lot->P_hour = new_car->timeDeparture;
			return stack_push(this_lot->P, new_car);
		}
	} 
	printf("Couldn't find vacancy\n");
	free(new_car);

	return NOT_AVAILABLE;
}

char* car_list(PARKING_LOT* this_lot)
{
	//allocate the *exact space* for making a string out of the printed cars
	/*printing format
	LOT PLATE PRICE
	X   XXXX  XXXXX
	Lot:X Plate: XXXX Price: XXXX.XX\n => 31 characters 
	*/
	CAR* temp_car;
	char* print_list = (char*) 
			calloc(31*(this_lot->P_cars + this_lot->F_cars),
		       	sizeof(char));

	for ( temp_car = (CAR*) queue_iter(this_lot->F) ; temp_car != NULL ; temp_car = (CAR*) queue_iter(this_lot->F))
	{
		printf("Q %d %d %d\n", temp_car->plate, temp_car->timeArrival, temp_car->stayPeriod);
	}

	for ( temp_car = (CAR*) stack_iter(this_lot->P) ; temp_car != NULL ; temp_car = (CAR*) stack_iter(this_lot->P))
	{
		printf("S %d %d %d\n", temp_car->plate, temp_car->timeArrival, temp_car->stayPeriod);
	}
	
	return print_list;
}

int lot_purge(PARKING_LOT* this_lot)
{
	stack_purge(this_lot->P);
	queue_purge(this_lot->F);
	free(this_lot);

	return OK;
}

char* draw_discount(PARKING_LOT* this_lot)
{
	int i;
	int sortedNum;
	CAR* prizeCar;
	char* print_string;

	stack_reset_iter(this_lot->P);
	queue_reset_iter(this_lot->F);

	sortedNum = rand() % 100;	

	if (sortedNum % 2)
	{
		sortedNum = rand() % stack_get_num(this_lot->P) + 1;
		while(sortedNum--)
		{
			prizeCar = stack_iter(this_lot->P);
		}
	}
	else
	{
		sortedNum = rand() % queue_get_num(this_lot->F) + 1;
		while(sortedNum--)
		{
			prizeCar = queue_iter(this_lot->F);
		}
	}
	if (prizeCar == NULL) printf("deu merda\n");

	prizeCar->discount = 1;
	printf("Got discount: %d", prizeCar->plate);

	return print_string;
}

