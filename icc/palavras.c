/*Created by Henrique Hiram Libutti Núñez ©2019 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*Defining constants for analysis*/

#define POSITIVE 1
#define NEGATIVE -1

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
    "STOP"
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
    "STOP"
    };
        
char *INV_WORDS[] = {
    "nao",
    "jamais",
    "nunca",
    "STOP"
    };

/*Structs for storing the product information and its related bag of words*/    
    
typedef struct _bag{
	char* word;
	int times;
    int bad_meaning;
    int good_meaning;
    } bag;    
    
typedef struct _products{
	char* name;
	bag* review;
    int meaning;
    int bad_words;
    int good_words;
    } products;

int check_in_bag(char* test_word , bag* this_bag , int bag_size);
int check_type(char* test_word , char** type);
products read_entry();
bag* store_in_bag(char *review , int max_size , products prod);
float review_type();

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
    store_in_bag(review , rem_size , this_product);
    
    return this_product;
    }

bag* store_in_bag(char *review , int max_size , products prod){ /*max size of remaining text*/
    int bag_size = 1;
    int iteration = 0;
    int inv_aux;
    int check_return;
    char * word;
        
    bag* words_in_review = (bag*) malloc (200 * sizeof(bag));
    
    word = strtok ( review ," ");
    
    while (word != NULL){
        
        iteration++;
        
        if (check_type(word , INV_WORDS)){ /*checks if the analysis nneds to be inverted*/
            inv_aux = iteration; /*Stores the iteration(position in review) for */
            } 
            else {
                if(iteration <= inv_aux+4){
                    printf("im sorry to interject you but...\n");
                    prod.meaning = (check_type(word , GOOD_WORDS) - check_type(word , BAD_WORDS))*(-1);
                    if (prod.meaning) printf("deu ruim na volta as aulas\n");
                } 
                else {
                    prod.meaning = (check_type(word , GOOD_WORDS) - check_type(word , BAD_WORDS));
                    }            
                }
        
        check_return = check_in_bag(word , words_in_review , bag_size - 1); /*checks wether the word was already entered or not*/
        
        if (check_return == -1){ /*creates new bag entry, if the word was not found*/
            
            words_in_review[bag_size-1].word = (char*) malloc (20*sizeof(char));
            words_in_review[bag_size-1].word = word;
            
            bag_size++;
            words_in_review[bag_size-1].word = NULL;
            words_in_review[bag_size-1].times = 1;
                               
            } else {
                words_in_review[check_return].times++;
                }
        
        word = strtok(NULL, " ");
    
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
    return -1;
    }    
    
int check_type(char* test_word , char** type){
    int i = 0;
    while(strcmp(type[i] , "STOP") != 0){
        printf("testing... %s\n" , type[i]);
        if (strcmp(type[i] , test_word) == 0) {
            printf("just found the type!!\n");
            return 1;
            }
        i++;
        }
    return 0;
}