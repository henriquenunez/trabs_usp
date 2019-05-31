/*Created by Henrique Hiram Libutti Núñez ©2019 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*Defining constants for analysis*/

char *GOOD_WORDS[] = {
	"bom", 
	"maravilhoso", 
	"otimo", 
	"sensacional", 
	"excelente", 
	"adorei", 
	"gostei", 
	"amei", 
	"eficiente", 
	"boa", 
	"maravilhosa", 
	"otima",
    '\0'
    };

char *BAD_WORDS[] = {
	"detestei", 
	"odiei", 
	"ruim", 
	"pessimo", 
	"terrivel", 
	"raiva", 
	"odio", 
	"pessima", 
	"lento", 
	"lenta", 
	"fragil", 
	"desisti",
    '\0'
    };
        
char *INV_WORDS[] = {
    "nao",
    "jamais",
    "nunca",
    '\0'
    };

typedef struct _bag{
	char* word;
	int times;
    int bad_meaning;
    int good_meaning;
    } bag;    
    
typedef struct _products{
	char* name;
	bag* review;
    int bad_words;
    int good_words;
    } products;
    
int check_in_bag(char* test_word , bag* this_bag , int bag_size);
int check_type(char* test_word , char** type);
products read_entry();
bag* store_in_bag(char *review , int max_size);
    
int main(){
	int nreviews;
	int nquestions;
	int index;
	products* entry = (products*) malloc(sizeof(products));
	
	scanf("%d%d" , &nreviews , &nquestions);

	for (index = 0 ; index < nreviews ; index++){
        entry[index] = read_entry();
        entry = (products*) realloc (entry , (index+1) * sizeof(products));
	}

    return 0;
    }

products read_entry(){
    
    products this_product;
    char* input = (char*) malloc(400 * sizeof(char) ); /*input of max size*/
    char* prod = (char*) malloc(400 * sizeof(char) );
    char* review = (char*) malloc(400 * sizeof(char) );
    char* ptr_split;
    long int rem_size;
    long int len;
    this_product.name = (char*) malloc( 400 * sizeof(char) );
    
    fgets(input , 400 , stdin);
    prod = strtok(input , ";");
    review = strtok(NULL , "Ø");
    this_product.name = prod;
    
    printf("prod:%s\nreview:%s\n" , this_product.name , review);
    
    len = strlen(this_product.name);
    printf("size is %ld from:" , len);
    
    printf("%s" , this_product.name);
    
    rem_size = 400 - len + 1;
    printf("\nremaining size is %ld" , rem_size);
    store_in_bag(review , rem_size);
    
    return this_product;
    }

bag* store_in_bag(char *review , int max_size){ /*max size of remaining text*/
    int bag_size = 1;
    int check_return;
    char * word;
    bag* words_in_review = (bag*) malloc (200 * sizeof(bag));
    
    printf ("Splitting string \"%s\" into tokens:\n", review);
    
    word = strtok ( review ," ");
    while (word != NULL)
    {
        printf ("word: %s\n", word);
        
        check_return = check_in_bag(word , words_in_review , bag_size - 1);
        if (check_return == -1){
            words_in_review[bag_size-1].word = (char*) malloc (20*sizeof(char));
            //words_in_review = (bag*) realloc (words_in_review , bag_size * sizeof(bag));
            
            words_in_review[bag_size-1].word = word;
            printf("in bag : %s \n" , words_in_review[bag_size-1].word);
            bag_size++;
            
            words_in_review[bag_size-1].word = NULL;
            words_in_review[bag_size-1].times = 1;
            
            printf("words number:%d\n" , bag_size);
                               
        } else {
            words_in_review[check_return].times++;
            printf("word: %s already in bag! , first appeared in: %d , times:%d\n" , word , check_return , words_in_review[check_return].times);
        }
        
        word = strtok (NULL, " ");
    
    }
    
    return words_in_review;
    }
    
int check_in_bag(char* test_word , bag* this_bag , int bag_size){
	int i;
	for (i = 0 ; i < bag_size ; i++){
        if(this_bag[i].word == NULL) {
            break;
            }
		if(strcmp(test_word , this_bag[i].word) == 0){
			return i;
		}
	}
    printf("not in bag...\n");
    return -1;
    }    
    
