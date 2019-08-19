#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define steps(base) (float)base/10 - (int)base/10 > 0 ? (int)base/10+1 : (int)base/10
					

void strtofloat(float* buffer, char* string, int base);
void strtofloat_2(float* buffer, char* string, int base);
char* find_point(char* string);
int counter_base(int stepSize);
int get_num(const char* string, char* pointer, int base);

int main(){

	float* answer = (float*) malloc(sizeof(float));
	//char* input_string;
	char string[50];

	//long unsigned int len = 0;
	fflush(0);
	int base;
	
	//getline(&input_string, &len, stdin);
	
	//string = (char*) malloc( sizeof(char) * strlen(input_string) );
	
	scanf("%s %d", string, &base);
	//strtofloat(answer, string, base);
	//printf("%d\n", steps(base));
	//printf("string: %s, base: %d\nget %d, at %p\n", string, base, get_num(string, &string[strlen(string)-3], base), &string[strlen(string)-1]);
	strtofloat_2(answer, string, base);
	printf("%.2f\n", *answer);
	//free(string);
	free(answer);
	return 666;
}

void strtofloat(float* buffer, char* string, int base){
	int i;
	int j = 0;
	int loc = -1; /*Whether we are dealing with integer or decimal part*/
	
	if (buffer == NULL){
		printf("There was not enough memory '-'\n Aborting...");
		exit(1);
	} else {
		*buffer = 0;
	}
	for (i = 0; i < strlen(string) ; i++){
		//printf("%d -> %lf -> %f -> %f\n", string[i]-48, pow(base, strlen(string) - 1 - i),  (string[i] - 48) * pow(base, strlen(string) -1 - i));
		
		if (string[i] == '.'){
			loc = i+1;
			//printf("point in %d\n", loc);
			continue;
		}
		j++;
		*buffer += (string[i] - 48) * pow(base, strlen(string) - j); /*48 -> offset to zero*/
	}
	
	if (loc != -1){
		*buffer /= pow(base, loc);	
	}
}

void strtofloat_2(float* buffer, char* string, int base){
	int i = strlen(string);
	int j = 0;
	int loc = -1; /*Whether we are dealing with integer or decimal part*/
	int step = steps(base);
	char* ptr;
	ptr = &string[strlen(string)-1];
	int pos_in_string;
	double num = 0;
	double big_num = 0;
	int ab = 0;
	int save_ab;
	int gap = steps(base);
	char* save_pointer = ptr;
	bool ok = false;
	
	ab = step;
	save_ab = i;
	save_ab = ab;
	ab = save_ab;

	if (find_point(string) != NULL)
		loc = ptr - find_point(string);
	//printf("%d\n", loc);

	while(save_pointer >= string){
		while(ok != true){
			if (*(save_pointer) != '.'){
				for ( ; j < gap; j++){

					if (*(save_pointer) == '.' || save_pointer < string){
						break;
					}
					num += ((double)*(save_pointer) - '0') * pow(10, j);
					//printf("num: %d at %p\n", num, save_pointer);
					save_pointer--;
				}
				j = 0;
				
				if (num < base){
					pos_in_string++;
					ok = true;
				}else{
					//ab = save_ab;
					ok=false;
					num = 0;
					save_pointer = ptr;
					gap--;
				}
			}else{
				save_pointer--;
			}
		}
		
		ok = false;
		big_num += (num * pow(base, pos_in_string-1)); 
		//printf("\tnum: %d bug num: %f\n", num, big_num);
		//printf("ptr: %p\n", save_pointer);
		num = 0;
		ptr = save_pointer;
	}


	if (loc != -1){
		big_num /= pow(base, loc);
	}
	*buffer = (float)big_num;
	//printf("numunun: %f\n", big_num);
}

char* find_point(char* string){
	char* p = string;
	for (int i = 0; i < strlen(string); i++){
		if(*p == '.'){
			return p;
		}
		p++;
	}
	return NULL;
}

int counter_base(int stepSize){
	static int count = 0;
	count++;
	if (count == stepSize){
		count = 0;
	}
	return count;
}

int get_num(const char* string, char* pointer, int base){
	int num = 0;
	int i = 0;
	int gap = steps(base);
	char* save_pointer = pointer;
	bool ok = false;

	while(ok != true){
		for ( ; i < gap; i++){
			num += (*(save_pointer) - 48) * pow(10, i);
			//printf("pointer is %p\n", save_pointer);
			save_pointer--;
		}
		
		if (num < base){
			ok = true;
			i = 0;
		}else{
			ok=false;
			num = 0;
			i = 0;
			save_pointer = pointer;
			gap--;
		}
		
	}
	pointer = save_pointer;
	return num;
}