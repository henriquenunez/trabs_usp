#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

const char* FORMAT_STR =\
"Nome: %s\nMarca: %s\nCódigo de barras: %s\nPreço: %.2f£\n";

#define OK 0

/*
//#define DEGUB
#ifndef DEBUG
#define __DEBUG //
#else
#define __DEBUG
#endif
*/

#define __DEBUG ;

/*SIZE OF STRUCT ON DISK IS 57, DUE TO MEMORY ALIGNMENT IT RETURNS 60*/
#define REGISTER_SIZE 57
typedef struct _register
{
    char name[20];
    char brand[20];
    char barcode[13];
    float    price;
} REGISTER;

/*Basic data structure*/
typedef struct _vector
{
    void*  data;
    size_t size;
} VECTOR;

/*For choosing operation*/
typedef enum _operation
{
    WRITE_ENTRIES = 0,
    READ_ENTRIES = 1,
    stop = 2
} OPERATION;

/*Getting operation*/
OPERATION input_operation()
{
    OPERATION op;
    unsigned int in;
    scanf("%u", &in);
    op = in;

    return op;
}

void clear_vec(VECTOR *this_vec)
{
    if(this_vec->size != 0)
    {
	free(this_vec->data);
        this_vec->data = NULL;
	this_vec->size = -1;
    }
}

/*Bulk operations*/
VECTOR read_entries(FILE* fp, int n_first);
int write_entries(FILE* fp);

/*IO*/
REGISTER input_register();
void output_register(REGISTER this_register);
void print_registers(VECTOR registers_vec);

/*One register operations*/
REGISTER read_register(FILE* fp);
void write_register(FILE* fp, REGISTER this_register);

/*Utilities*/
size_t file_check_size(FILE* fp);
char* get_barcode(char* barcode_address);

int main()
{
    FILE* fp;
    OPERATION op;
    VECTOR data_holder;
    char STOP = 0;

    do
    {
	//read option
	printf("Insert operation:\n0 for inserting register\n1 for reading \
registers\n2 for stop\n");
	op = input_operation();
	switch(op)
	{
	    case WRITE_ENTRIES:
	        fp = fopen("products.bin", "wb");
		write_entries(fp);
		fclose(fp);
		break;
	    case READ_ENTRIES:
	        fp = fopen("products.bin", "rb");
		data_holder = read_entries(fp, 0);
		printf("\n********REGISTERS********\n");
		print_registers(data_holder);
		//things
		//things
		fclose(fp);
		break;
	    case stop:
		printf("stop");
		STOP = 1;
	}
    }while(!STOP);

    return 0;
}


/*-------ONE REGISTER OPERATIONS--------*/
//Inserts ONE register in the file
void write_register(FILE* fp, REGISTER this_register)
{
    fwrite( this_register.name,    sizeof(char), 20, fp);
    fwrite( this_register.brand,   sizeof(char), 20, fp);
    fwrite( this_register.barcode, sizeof(char), 13, fp);
    fwrite(&this_register.price,  sizeof(float),  1, fp);
}

//Reads ONE register from file
REGISTER read_register(FILE* fp)
{
    REGISTER this_register;
    memset(&this_register, 0, sizeof(REGISTER));
    if (feof(fp) == EOF) printf("Deu merda!\n");
//__DEBUG printf("Reading on %ld\n", ftell(fp));

    fread( this_register.name,    sizeof(char), 20, fp);
    fread( this_register.brand,   sizeof(char), 20, fp);
    fread( this_register.barcode, sizeof(char), 13, fp);
    fread(&this_register.price,  sizeof(float),  1, fp);

    return this_register;
}

/*-------I/O STDIN/STDOUT--------*/
//I know this function is super insecure, but it's just a proof of concept. :3
REGISTER input_register()
{
    REGISTER this_register;
    char tempName[21];
    char tempBrand[21];
    char tempBarcode[21];
    float tempPrice;

    scanf(" %s %s %s %f", tempName, tempBrand, tempBarcode, &tempPrice);

//__DEBUG printf("Got 1 register!\n");

    memcpy(this_register.name, tempName, 20);
    memcpy(this_register.brand, tempBrand, 20);
    memcpy(this_register.barcode, tempBarcode, 13);
    this_register.price = tempPrice;

    return this_register;
}

//Prints register fields
void output_register(REGISTER this_register)
{
    char tempName[21] = {0};
    char tempBrand[21] = {0};
    char tempBarcode[14] = {0};
    float tempPrice;

    memcpy(tempName,    this_register.name,    20);
    memcpy(tempBrand,   this_register.brand,   20);
    memcpy(tempBarcode, this_register.barcode, 13);
	   tempPrice    = this_register.price;


    printf(FORMAT_STR,  tempName,
			tempBrand,
		        tempBarcode,
		        tempPrice);
}

/*FRONT END FUNCTIONS*/

//writes entries until stop condition
int write_entries(FILE* fp)
{
    REGISTER this_register;
    do
    {
	//read entry
	this_register = input_register();
	if(this_register.price == -1)
	{
//__DEBUG	    printf("End register detected...\n");
	    return OK;
	}
	//insert into file
	write_register(fp, this_register); //TODO error checking
	//if return code != OK return .....

    }while(1);

    return OK;
}

//reads entries until stop condition
VECTOR read_entries(FILE* fp, int n_first)
{
    VECTOR ret_vec;
    REGISTER* register_seq;
    int index = 0;
    //int num_regs; //number of registries
    size_t file_size;

    #define NUM_REGS ((float)file_size/(float)REGISTER_SIZE)

    file_size = file_check_size(fp);

//__DEBUG printf("Number of bytesREG: %dB\n", REGISTER_SIZE);
//__DEBUG printf("Size   of    file : %ldB\n" , file_size);
//__DEBUG printf("Number of  records: %f\n" , NUM_REGS);

    //not a whole file. ERROR
//    if ( ((int)NUM_REGS - NUM_REGS) != 0) //return ERROR;

    register_seq = (REGISTER*) malloc (sizeof(REGISTER) *
			(int)(NUM_REGS) > n_first ? (int)(NUM_REGS) : n_first);

    //resolves n_first > number of entries, and n_first = 0 (entire file)
    if(n_first != 0)
        n_first = n_first < (int)NUM_REGS ? n_first : (int)NUM_REGS;
    else n_first = (int)NUM_REGS;

    //TEMPORARY
    REGISTER temp;

    while(feof(fp) != EOF && index < n_first)
    {
	temp = read_register(fp);
//__DEBUG	printf("reading number %d\n", index); fflush(stdout);
	//output_register(temp);
	register_seq[index] = temp;//read_register(fp);
	index++;
    }

    //loads data into vector, along with the size
    ret_vec.data = (void*)register_seq;
    ret_vec.size = index;

    #undef NUM_REGS

    return ret_vec;
}

//This function will DESTROY DATA!
void print_registers(VECTOR registers_vec)
{
    for(int i = 0 ; i < registers_vec.size ; i++)
    {
	printf("\n#%d\n", i);
	output_register( *((REGISTER*) registers_vec.data + i) );
    }
    clear_vec(&registers_vec);
}

/*--------UTILS--------*/

//returns the number of registers within the file
size_t file_check_size(FILE* fp)
{
    size_t size;
    fpos_t save_state; //current location
    unsigned char temp;

    //retrieve current pos
    fgetpos(fp, &save_state);
    fseek(fp, 0L, SEEK_SET);
    do
    {
	fread(&temp, sizeof(char), 1, fp);//fseek(fp, 1, SEEK_CUR);
//__DEBUG printf("Byte is %d\n", temp);
//__DEBUG printf("SEEK_CUR: %ld\n", ftell(fp));
    }while(!feof(fp));
    size = ftell(fp);
//__DEBUG printf("file bytes is: %ld\n", size);
    fsetpos(fp, &save_state);

    return size;
}

//Utility for transforming barcode sequence into printable string
char *get_barcode(char* barcode_address)
{
    char barcode_string[14] = {0};
    char *ret_addr;

    for (int i = 0; i < 13; i++) barcode_string[i] = barcode_address[i];

    ret_addr = barcode_string;

    return ret_addr;
}

