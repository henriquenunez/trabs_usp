#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int min(int a , int b){ /*retorna o valor minido entre dois parametros passados*/
  if (a < b) return a;
  else return b;
  }

int check_values(int num_values , int *seq , int *err){ /*Recebe a resposta do usuario, e compara com o vetor gerado anteriormente*/

  int answer[9];
  int index_val;
  int err_now = 0;

  for(index_val = 0 ; index_val < num_values; index_val++){
    scanf("%d" , &answer[index_val]);
    if ( !(seq[index_val] == answer[index_val]) ){ /*Caso o valor seja incorreto, uma variavel de erro e incrementada para cada iteracao*/
      err_now++;
    }
  }
  (*err) += err_now; /*soma-se o valor em uma variavel de erro no escopo da main, que e usada para calculo de pontuacao*/
  return err_now; /*retorna-se o valor de erros da iteracao*/
}

void disp_values(unsigned int time , int num_values , int *seq){ /*Mostra os valores do vetor na tela, de acordo com o tempo definido e o numero de valores*/

  int index_val;

  for(index_val = 0 ; index_val < num_values; index_val++){
    printf("%d" , seq[index_val]);
    if(index_val < (num_values - 1)) printf(" ");
  }
  printf("\n");
  /*fflush(stdout);*/ /*Forca a saida de dados da stdout*/
  /*sleep(time);*/ /*Ativa a espera do programa*/
  /*printf("\r                      \r");*/ /*Apaga a linha*/
}

void generate_values(int num_values , int *seq){ /*Gera os valores no vetor passado por referencia, de acordo com parametro de numero de valores*/

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
  int total = 0;
  int errors = 0;
  int last_errors;
  int sequence[9];

  int trials = 3;

  scanf("%d %c" , &seed , &option); /*Le a opcao de jogo e a semente de aleatoriedade*/
  srand(seed);

  switch(option){ /*Define os parametros correspondentes para a chamada das funcoes que irao seguir*/
    case 'F':
      num_seq = 3;
      num_val = 5;
      sleep_time = 5;
      break;
    case 'I':
      num_seq = 4;
      num_val = 7;
      sleep_time = 7;
      break;
    case 'A':
      num_seq = 5;
      num_val = 9;
      sleep_time = 10;
      break;
  }

  for(index_seq = 0 ; index_seq < num_seq; index_seq++){

    generate_values(num_val, &sequence[0]);

    while(trials){
      printf("Sequencia #%d:\n" , index_seq + 1 );
      disp_values(sleep_time , num_val, &sequence[0]);

      if( check_values(num_val , &sequence[0] , &errors) ){ /*Caso exista erro na resposta, diminui-se o numero de tentativas*/
        trials--;                                           /*e mostra-se a pontuacao que pode ser alcancada*/
        printf("Incorreto!\n");
        if(trials){
          printf("Tentativas disponiveis: %d\n" , trials);
          if(errors > num_val) errors = num_val; /*estabelce um limite para o numero de erros*/
          printf("Pontuacao: %d\n" , total + 10 * (num_val - errors));

        } else { /*Se as tentativas acabaram, atualiza-se o valor da pontuacao com o valor dos erros da ultima tentativa*/
          printf("Tentativas disponiveis: %d\n" , trials);
          total += 10 * (num_val - min(errors , last_errors));
          printf("Pontuacao: %d\n" , total);
        }
      } else { /*Se a resposta e correta, acresce-se a pontuacao de acordo com o numero de erros obtidos na rodada*/
        printf("Correto!\n");
        printf("Tentativas disponiveis: %d\n" , trials);
        if(errors > num_val) errors = num_val; /*estabelce um limite para o numero de erros*/
        total += 10 * (num_val - errors);
        printf("Pontuacao: %d\n" , total);
        break;
      }
      last_errors = errors; /*Erros da ultima tentativa*/
    }
    errors = 0; /*A quantidade de erros e zerada para a proxima sequencia*/
  }

  if(trials){ /*Mensagem caso o objetivo tenha sido cumprido*/
    printf("Otima memoria! Parabens!!!\n");
  } else {
    printf("Nao ha mais tentativas disponiveis... Tente novamente!\n");
  }
  return 0;
}
