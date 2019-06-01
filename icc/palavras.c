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
    int bag_size;
    int meaning;
    } products;

int check_in_bag(char* test_word , bag* this_bag , int bag_size);
int check_type(char* test_word , char** type);
products read_entry();
bag* store_in_bag(char *review , int max_size , products* prod);
float review_type(char* prod , products* entries , int type , int num_entries);
void free_entries(products* entries , int num_entries);
void query(products* entries , int num_entries);
void free_BoW(bag* review , int num_entries);

int main(){
	int nreviews;
	int nquestions;
	int index;
	
    scanf(" %d %d " , &nreviews , &nquestions);
	
    products* entry = (products*) malloc(nreviews * sizeof(products));
	
	for (index = 0 ; index < nreviews ; index++){
        entry[index] = read_entry();
        /*entry = (products*) realloc (entry , (index+1) * sizeof(products));*/
	}
    
    printf("delbem\n");
    
    for (index = 0 ; index < nquestions; index++){
        /*review_type("Impressora Epson " , entry , POSITIVE , nreviews);*/
        query(entry , nreviews);
    }
    return 0;
    }

products read_entry(){
    
    /*TODO: CHECK IF BAG ALREADY EXISTS*/
    
    products this_product;
    char* input = NULL; /*(char*) malloc(400 * sizeof(char) ); /*input of max size*/
    long int t = 0;
    char* prod = (char*) malloc(400 * sizeof(char) );
    char* review = (char*) malloc(400 * sizeof(char) );
    char* ptr_split;
    long int rem_size;
    long int len;
    this_product.name = (char*) malloc( 400 * sizeof(char) );
    
    getline(&input , &t , stdin);
    prod = strtok(input , ";");
    review = strtok(NULL , "Ø");
    sscanf(prod , "%s[^;];" , this_product.name);
    this_product.name = prod; /*use sscanf for removing whitespace*/
    
    printf("prod:%s.###review:%s\n" , this_product.name , review);
    
    len = strlen(this_product.name);
    printf("size is %ld from:" , len);
    
    printf("%s\n" , this_product.name);
    
    rem_size = 400 - len + 1;
    store_in_bag(review , rem_size , &this_product);
    printf("meaning is :%d\n" , this_product.meaning);
    return this_product;
    }

bag* store_in_bag(char *review , int max_size , products* prod){ /*max size of remaining text*/
    prod->meaning = 0;
    int bag_size = 1;
    int iteration = 0; /*iteration upon the received string*/
    int inv_aux = -4; /*initialize, otherwise the meaning will be changed unproperly, aka "INVERTENDO OPINIOES"*/
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
                    prod->meaning += (check_type(word , GOOD_WORDS) - check_type(word , BAD_WORDS))*(-1);
                    inv_aux = 0;
                } 
                else {
                    prod->meaning += (check_type(word , GOOD_WORDS) - check_type(word , BAD_WORDS));
                    inv_aux = 0;
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
    
    words_in_review = (bag*) realloc (words_in_review , sizeof(words_in_review) / sizeof(bag));
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
        /*printf("testing... %s\n" , type[i]);*/
        if (strcmp(type[i] , test_word) == 0) {
            /*printf("just found the type!!\n");*/
            return 1;
            }
        i++;
        }
    return 0;
    }

float review_type(char* prod , products* entries , int type , int num_entries){
    
    int i;
    int num_prod = 0;
    int num_of_type = 0;
    float ratio;
    //printf("UNDER TEST:%s. %d" , "Impressora Epson" , strcmp(prod , "Impressora Epson"));
    for (i = 0 ; i < num_entries ; i++){
        printf("testing:%s. with n:%s. result:%d" , entries[i].name , prod , strcmp(entries[i].name , prod));
        if(strcmp(entries[i].name , prod) == 0){
            num_prod++;
            printf("found %s %d times\n", prod , num_prod);
            if( (entries[i].meaning > 0 && type > 0) || (entries[i].meaning < 0 && type < 0) ) { /*checks wether meaning and type have the same sign*/
                num_of_type++;
            }
        }
    }
    printf("%d %d reviews\n", num_of_type , type);
    ratio = ((float)num_of_type/(float)num_prod);
    printf("found %d entries, of which %d were of the desired type, what equals to %.2f%%\n" , num_prod , num_of_type, ratio);
    return ratio;
    }

void query(products* entries , int num_entries){
        char* input = NULL; /*(char*) malloc(400 * sizeof(char) ); /*input of max size*/
        char* command = NULL;
        char* buffer = NULL;
        char* prod_name = (char*) calloc (50 , 50 * sizeof(char));
        bool query_type;
        long int t = 0;
        
        getline(&input , &t , stdin);
        printf("query:%s.\n" , input);
        
        
        command = strtok(input , " ");
        printf("command:%s.\n" , command);
        
        if (strcmp(command , "palavra") == 0){
            command = strtok(NULL , " ");
            printf("palavra:%s.\n" , command);
            /*check word*/
        } else {
            command = strtok(NULL , " ");
            printf("quantos:%s.\n" , command);
        }
        
        strtok(NULL , " "); /* em */
        
        buffer = strtok(NULL , " \n");
        strcat(prod_name , buffer);
        buffer = strtok(NULL , " \n");
        strcat(prod_name , " ");
        
        while(buffer != NULL){
            strcat(prod_name , buffer);
            strcat(prod_name , " ");
            buffer = strtok(NULL , " \n");
        }
            
        printf("query type: %d , name:%s.\n" , query_type , prod_name);    
            
        if(query_type){ /*palavra X*/
            /**/
        } else { /*quantos X*/
            if (strcmp(command , "positivos") == 0){
                review_type(prod_name , entries , POSITIVE , num_entries);
            } else {
                review_type(prod_name , entries , NEGATIVE , num_entries);
            }
        }
        /*
         * for (i = 0 ; i < num_entries ; i++){
        printf("NAME: %s" , entries[i].name);
        if(strcmp(entries[i].name , prod) == 0){
            num_prod++;
            printf("found %s %d times\n", prod , num_prod);
            if( (entries[i].meaning > 0 && type > 0) || (entries[i].meaning < 0 && type < 0) ) { /*checks wether meaning and type have the same sign
                }
                }
            }
         */
    }
    
void free_entries(products* entries , int num_entries){
    
    }
void free_BoW(bag* review , int num_entries){
    
    }    
