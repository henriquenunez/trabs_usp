//main.c
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "stack.h"
#include "queue.h"
#include "lot.h"

int main()
{
	/*
	TODO: finish printing cars
	discout draw
	*/
	PARKING_LOT* a_lot;
	int tempPlate;
	int tempArrival;
	int tempDeparture;
	char op;

	a_lot = lot_create();

	do
	{
		scanf(" %c ", &op);
		//printf("received %d\n", op);
		switch(op)
		{
			case '1':
				scanf("%d %d %d", &tempPlate, &tempArrival, &tempDeparture);
				register_car(a_lot, tempPlate, tempArrival, tempDeparture);
				break;
			case '2':
				break;
			case '3':
				printf("%s", car_list(a_lot));
				break;
			case '4':
				//lot_purge(a_lot);
				return 0;
				break;
		}
	}while(1);
	return 0;
}
