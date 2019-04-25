#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void score(int num_values , int errors , int *total , int *actual){
  
  int max = 10 * num_values;
  
  return;
}

int check_values(int num_values , int *seq){
  
  int answer[9];
  int index_val;
  int err = 0;
  
  for(index_val = 0 ; index_val < num_values; index_val++){
    scanf("%d" , &answer[index_val]);
    if ( !(seq[index_val] == answer[index_val]) ){
      err++;
    }     
  }
  return err;
}

void disp_values(unsigned int time , int num_values , int *seq){
 
  int index_val;
  
  for(index_val = 0 ; index_val < num_values; index_val++){
    printf("%d " , seq[index_val]);
  }
  fflush(stdout);
  sleep(time);
  printf("\r                      \r");
}

void generate_values(int num_values , int *seq){
 
  int index_val;
  
  for(index_val = 0 ; index_val < num_values; index_val++){
    seq[index_val] = rand() % 10;
  }
}

int main(){

  int seed;
  char option;

  int index_seq;
  int num_seq;
  int num_val;
  
  unsigned int sleep_time;
  int *total = 0;
  int sequence[9];
  
  int trials = 3;
  
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

    while(trials){
      printf("Sequencia #%d:\n" , index_seq + 1 );
      disp_values(sleep_time , num_val, &sequence[0]);
      if( check_values(num_val , &sequence[0]) ){
        trials--;
        printf("Erou!\n");
      } else {
        printf("Ah mizeravi!\n");
        break;
      }
    }
    printf("TU PODE FAZER %d\n" , trials);
    //TODO printf("TANTOS PONTOS O KRLL %d\n" , *total);
  }
  
  if(trials){
    printf("BOM DMS ZIKA!\n");
  }
}
