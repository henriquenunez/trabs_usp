#include <stdio.h>
#include <stdlib.h>

int score(){

}

int check_values(int num_values , int *seq){
  
  int answer[9];
  int index_val;
  int err = 0;
  
  for(index_val = 0 ; index_val < num_values; index_val++){
    scanf("%d" , &answer[index_val]);
    printf("to ak\n");
    if ( seq[index_val] == answer[index_val] ){
      printf("acerto!!!!! mizeravi\n");
    } else {
      err++;
      printf("Errou!!!!! fdp\n");
    }     
  }
  return err;
}

void generate_values(int num_values , int *seq){
 
  int index_val;
  
  for(index_val = 0 ; index_val < num_values; index_val++){
    seq[index_val] = rand() % 10;
    printf("%d " , seq[index_val]);
  }
  
  printf("\n");  
}

int main(){
    int seed;
    int index_seq;
    int num_seq;
    int num_val;
    int sleep_time;
    int *total = 0;
    int sequence[9];
    char option;
    
    
    scanf("%d %c" , &seed , &option);
    srand(seed);
    

    switch(option){
      case 'F':
        num_seq = 3;
        num_val = 5;
        sleep_time = 5;
        break;
      case 'M':
        num_seq = 5;
        num_val = 5;
        sleep_time = 5;
        break;
      case 'A':
        num_seq = 7;
        num_val = 5;
        sleep_time = 5;
        break;
    }

    for(index_seq = 0 ; index_seq < num_seq; index_seq++){
      generate_values(num_val, &sequence[0]);
      check_values(num_val , &sequence[0]);
    }
}
