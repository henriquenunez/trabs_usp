#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
	float sep_len; //sepal length in cm
	float sep_wid; //sepal width in cm
	float pet_len; //petal length in cm 
	float pet_wid; //petal width in cm
}flower;

float comp_dist(flower group , flower fleur){
	return sqrt(pow((fleur.sep_len - group.sep_len),2)+
		    pow((fleur.sep_wid - group.sep_wid),2)+
                    pow((fleur.pet_len - group.pet_len),2)+
                    pow((fleur.pet_wid - group.pet_wid),2));
	}

char belongs_to(flower defendant , flower g0 , flower g1 , flower g2){
	float d0 = comp_dist(g0 , defendant);
	float d1 = comp_dist(g1 , defendant);
	float d2 = comp_dist(g2 , defendant);
	
	if(min(d0 , min(d1,d2)) == d0){
		return 0;	
	}else if((min(d0 , min(d1,d2)) == d1)){
		return 1;
	}else{
		return 2;
	}
}

int main(){
flower ref_0;
	ref_0.sep_len = 5.4;
	ref_0.sep_wid = 3.7;
	ref_0.pet_len = 1.5;
	ref_0.pet_wid = 0.2;
flower ref_1;
	ref_1.sep_len = 6.0;
	ref_1.sep_wid = 2.2;
	ref_1.pet_len = 4.0;
	ref_1.pet_wid = 1.0;
flower ref_2;
	ref_2.sep_len = 5.8;
	ref_2.sep_wid = 2.7;
	ref_2.pet_len = 5.1;
	ref_2.pet_wid = 1.9;
	
	int groups[3] = {0};	
	int sel;
	flower buff;
	FILE* dataset;
	dataset = fopen("iris.data" , "r");
	while(!feof(dataset)){
		fscanf(dataset, "%f,%f,%f,%f,%*[^\r\n]\n" ,
			&buff.sep_len,
			&buff.sep_wid,
		       	&buff.pet_len,
			&buff.pet_wid);
	sel = belongs_to(buff , ref_0 , ref_1 , ref_2);
	groups[sel]++;
	}
	printf("Total do Grupo 0: %d\nTotal do Grupo 1: %d\nTotal do Grupo 2: %d\n" ,groups[0],groups[1],groups[2]);
	return 0;
}
