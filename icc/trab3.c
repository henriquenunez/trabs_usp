#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROI matrix[pos_x][pos_y] //aka "region of interest"

typedef struct _pixel{ //stores pixel grayscale value and wether it belongs to a segmented region or not.
	unsigned char value;
	int seg_region;
}pixel;

float mod(float n){ //absolute value of a float
	if(n >= 0){
	return n;
	}else{
	return (n * -1);
	}
}

bool print_point(){
	printf(" . ");
	return false;
}

void conquer(pixel** matrix , int pos_x , int pos_y ,  int x_size, int y_size, int value , int q_num , bool start , float* seg_mean , int* count);
void scan_pic(pixel** matrix , int x_size, int y_size);
bool check_boundary(pixel** matrix , int pos_x , int pos_y , int x_size, int y_size);
void check_border();

int main(){
	FILE* pic;
	char filename[40];
	pixel** image;
	int num_queries;
	int x_size , y_size;
	int buff_val;
	int x_query , y_query;
	
	int* pixel_count = (int *) malloc (sizeof(int)); //pointers to variables for segmentation control.
	float* mean = (float *) malloc (sizeof(float));
	*pixel_count = 0;
	*mean = 0;

	scanf("%s[^\r\n]\n" , filename); 			//file name
	scanf("%d[^\r\n]\n" , &num_queries);  //number of queries

	pic = fopen(filename , "r");
	fscanf(pic , "%*[^\r\n]\n");
	fscanf(pic , "%d %d[^\r\n]\n " , &x_size , &y_size); //grab only x and y size
	fscanf(pic , " %*[^\r\n]\n ");
	
	image = (pixel**) malloc (x_size * (sizeof(pixel*))); //allocates memory on heap.
	for (int i = 0 ; i < x_size ; i++)
		image[i] = (pixel*) calloc (y_size , y_size * (sizeof(pixel))); 
	
	for (int j = 0 ; j < y_size ; j++){
		for (int i = 0 ; i < x_size ; i++){
			fscanf(pic , "%d[^\r\n]\n" , &buff_val);
			(image[i][j]).value = buff_val;
			image[i][j].seg_region = 0;
			//printf( "%d ",(image[i][j]).value);//DEBUGGING
		}
		//printf("\n");//DEBUGGING
	}

	for (int i = 1 ; i <= num_queries ; i++){
		scanf("%d %d %d[^\r\n]\n", &y_query, &x_query, &buff_val);
		conquer(image , x_query , y_query , x_size, y_size,  buff_val , i , 1 , mean , pixel_count);
		//printf("ok\n"); //DEBUGGING
		*pixel_count = 0;
		*mean = 0;
	}
	/*for (int j = 0 ; j < y_size ; j++){
		for (int i = 0 ; i < x_size ; i++){
		printf( "%d ",(image[i][j]).seg_region);//DEBUGGING		
		}
		printf("\n");//DEBUGGING
	}
	*/
	scan_pic(image , x_size, y_size);
	
	for (int i = 0; i < x_size; ++i)
	{
		free(image[i]);
	}
	free(image);
	free(pixel_count);
	free(mean);
	fclose(pic);
}

void conquer(pixel** matrix , int pos_x , int pos_y , int x_size, int y_size, int value, int q_num , bool start , float* seg_mean , int* count){

	//printf("SEG:%d - %d %d criterio:%d , count:%d , mean:%f , diff:%f , value:%d\n" , q_num , pos_x , pos_y , value , (*count) , *seg_mean , mod(matrix[pos_x][pos_y].value - *seg_mean) , matrix[pos_x][pos_y].value);
	if(start) *seg_mean = matrix[pos_x][pos_y].value; 

	if( (mod(matrix[pos_x][pos_y].value - *seg_mean) <= value || start) && matrix[pos_x][pos_y].seg_region == 0) { //pixel eligibility
		matrix[pos_x][pos_y].seg_region = q_num; 
		(*count)++;
		*seg_mean = (((*seg_mean)*((*count)-1) + matrix[pos_x][pos_y].value)/(*count));
	}else{
		return;
	}
	/*
	for (int j = 0 ; j < y_size ; j++){
		for (int i = 0 ; i < x_size ; i++){
			printf( "%d ",(matrix[i][j]).seg_region);//DEBUGGING	
		}
		printf("\n");
	}
	*/
	//sleep(1); //HUMAN READABILITY
	//fflush(0);
	if(pos_y > 0  		)	conquer(matrix , pos_x , pos_y-1 , x_size, y_size, value, q_num , 0 , seg_mean , count);
	if(pos_x < x_size-1 )   conquer(matrix , pos_x+1 , pos_y , x_size, y_size, value, q_num , 0 , seg_mean , count);
	if(pos_y < y_size-1 )	conquer(matrix , pos_x , pos_y+1 , x_size, y_size, value, q_num , 0 , seg_mean , count);
	if(pos_x > 0 		)	conquer(matrix , pos_x-1 , pos_y , x_size, y_size, value, q_num , 0 , seg_mean , count);
	
	return ;
}

void scan_pic(pixel** matrix , int x_size, int y_size){ //scans picture looking for boundaries
	//printf("\t\t size x: %d, size Y: %d\n" , x_size , y_size);
	for (int j = 0; j < y_size; ++j)
	{
		for (int i = 0; i < x_size; ++i)
		{
			if(check_boundary(matrix , i , j ,x_size, y_size)) printf("(%d, %d)\n" , j , i);
			//else printf("not this time...(%d, %d)\n" , i , j);
			//sleep(1);
		}
	}
	return;
}

bool check_boundary(pixel** matrix , int pos_x , int pos_y , int x_size, int y_size){
	bool bound = false;
	//	ROI = matrix[pos_x][pos_y].seg_region;
	//printf("pos_x: %d pos_y: %d\n" , pos_x , pos_y);
	/*
	for (int j = 0 ; j < y_size ; j++){
		for (int i = 0 ; i < x_size ; i++){
			if (j != pos_y || i != pos_x) printf( "%3d",(matrix[i][j]).seg_region);//DEBUGGING
			else printf("  X");
		}
		printf("\n");//DEBUGGING
	}
	*/
	if (pos_x > 0) {
		//printf("x>0!\n");
		if(ROI.seg_region != matrix[pos_x-1][pos_y].seg_region) bound = true;
	}
	if (pos_x < x_size-1) {
		//printf("x<size-1!\n");
		if(ROI.seg_region != matrix[pos_x+1][pos_y].seg_region) bound = true;
	}
	if (pos_y > 0) {
		//printf("y>0!\n");
		if(ROI.seg_region != matrix[pos_x][pos_y-1].seg_region) bound = true;
	}
	if (pos_y < y_size-1) {
		//printf("y<size-1!\n");
		if(ROI.seg_region != matrix[pos_x][pos_y+1].seg_region) bound = true;
	}
	/*
	if(
	   (pos_x > 0) ? 		ROI.seg_region != matrix[pos_x-1][pos_y].seg_region:print_point() 
	|| (pos_x < x_size-1) ? ROI.seg_region != matrix[pos_x+1][pos_y].seg_region:print_point()
	|| (pos_y > 0) ? 		ROI.seg_region != matrix[pos_x][pos_y-1].seg_region:print_point()
	|| (pos_y < y_size-1) ? ROI.seg_region != matrix[pos_x][pos_y+1].seg_region:print_point())
	bound = true;
	*/
	
	/*
	if(pos_x > 0){
		//check left
	}
	if(pos_x < x_size-1){
		//check right
	}
	if(pos_y > 0){
		//check up
	}
	if(pos_y < y_size-1){
		//check down
	}
	*/
	/*if (bound)
	{
		print_point();
	}
	*/
	return bound;
}
