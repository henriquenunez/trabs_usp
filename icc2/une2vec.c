#include <stdio.h>


void join(int* V3, int* V1, int* V2);

int main(){;
	
}

join(int* V3, int* V1, int* V2){
	if(V2 != -1 && V1 != -1 && *V1 > *V2){
		if(*V2 > *V3){
			V3[1] = *V2;
		}else{
			V3[1] = *V1;
		}
	}else{
		if(*V1 > *V3){
			V3[1] = *V1;
		}else{
			if(*V2 > *V3){
				V3[1] = *V2;	
			}
		}
	}
	join()
}
