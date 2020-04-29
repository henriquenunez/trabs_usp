#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int _a = 1;
const int _b = 2;

int main(void){
	void* data = malloc(8);
	memcpy(data, &_a, sizeof(int));
	memcpy(data + sizeof(int) , &_b, sizeof(int));
	int a = *((int*)data);
	int b = *((int*)data+sizeof(int));
	printf("A=%d, B=%d", a, b);
	return 0;
}
