#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"

#define MAX(a, b) ((a > b) ? a : b)

const char alphabet[] = {
'a','A',
'b','B',
'c','C',
'd','D',
'e','E',
'f','F',
'g','G',
'h','H',
'i','I',
'j','J',
'k','K',
'l','L',
'm','M',
'n','N',
'o','O',
'p','P',
'q','Q',
'r','R',
's','S',
't','T',
'u','U',
'v','V',
'w','W',
'x','X',
'y','Y',
'z','Z',
'\0'// \0 beause its a string after all
};

enum _csv_error {
    OK,
    FILE_NOT_OPEN,
    WRONG_READ,
    END_OF_FILE
};

/*Information of a csv file*/
struct _csv_file {
    FILE* fp;
    enum _read_state {
	BEGIN,
	COMMA,
	BETWEEN_COMMA
    } read_state;
    size_t max_field_size;
    void* read_buffer;
    int last_byte;
    csv_err_t last_error;
};

typedef enum _field_type {
    INTEGER,
    CHARACTER,
    FLOAT,
    STRING
} field_t;

CSV_FILE* openCsvFile(const char* filename) {
    CSV_FILE* ret_pointer = (CSV_FILE*) malloc(sizeof(CSV_FILE));

    ret_pointer->fp = fopen(filename, "rb");
    ret_pointer->read_state = BEGIN;
    ret_pointer->max_field_size = 0;
    ret_pointer->read_buffer = NULL;

    return ret_pointer;
}

csv_err_t __read_next_field(CSV_FILE* this_file, field_t type, void* cont) {

    size_t start_pos = ftell(this_file->fp);
    size_t next_pos;
    char temp;
    char* contains_letters;

    #define DELTA_FIELD (next_pos - start_pos)

    if (this_file->read_state != COMMA &&
	this_file->read_state != BEGIN) {

    }

    while (this_file->last_byte = fgetc(this_file->fp)) {
	//printf("got: {%c}", this_file->last_byte);
	if (this_file->last_byte == EOF) {
	    //Toggle end of file and error
	    return END_OF_FILE;
	}
	if (this_file->last_byte == ',' || this_file->last_byte == '\n') {
	    //excluding last character: ',' or '\n'
	    next_pos = ftell(this_file->fp) - 1;
	    break;
	}
    }

    /*Checks if there is need to update buffer, and updates it*/
    if ( MAX(DELTA_FIELD + 1, this_file->max_field_size)
			    != this_file->max_field_size) {

	if(this_file->read_buffer != NULL)
    	    free(this_file->read_buffer);
        this_file->max_field_size = DELTA_FIELD + 1;
	this_file->read_buffer = malloc(DELTA_FIELD + 1);
    }

    /*Sets buffer to 0*/
    memset(this_file->read_buffer, 0, this_file->max_field_size);

    /*Goes back to start, and reads corresponding data*/
    fseek(this_file->fp, start_pos, 0);
    fread(this_file->read_buffer,
	    sizeof(char),
	    DELTA_FIELD,
	    this_file->fp);
    /*Seeks one more byte to skip ',' or trailing '\n'*/
    fseek(this_file->fp, 1, SEEK_CUR);

    /*Writes 0 so string operations can work*/
    //((char*)this_file->read_buffer)[this_file->max_field_size] = '\0';

    if (contains_letters = strpbrk((char*)this_file->read_buffer, alphabet)){
	//printf("Contains letters! {%c}\n", *contains_letters);
    }

    /*Treats data accordingly*/
    switch (type) {
	case INTEGER:
	    if (contains_letters)
		return WRONG_READ;
	    *(int*)cont = atoi((char*)this_file->read_buffer);
	    break;
	case STRING:
	    *(char**)cont = this_file->read_buffer;
	    break;
	case FLOAT:
	    if (contains_letters)
		return WRONG_READ;
	    *(float*)cont = atof((char*)this_file->read_buffer);
	    break;

    }

    return OK;
    #undef DELTA_FIELD
}

int getNextInt(CSV_FILE* this_file) {
    int ret_val;

    if (__read_next_field(this_file, INTEGER, &ret_val) != OK)
	return -1;

    return ret_val;
}

float getNextFloat(CSV_FILE* this_file) {
    float ret_val;

    __read_next_field(this_file, FLOAT, &ret_val);

    return ret_val;
}

char* getNextString(CSV_FILE* this_file) {
    char* ret_val;

    __read_next_field(this_file, STRING, &ret_val);

    return ret_val;
}

void closeCsvFile(CSV_FILE* this_file) {
    fclose(this_file->fp);
    free(this_file->read_buffer);
    free(this_file);
}

#undef MAX

