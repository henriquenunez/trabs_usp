#include "btreebin.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*DEFINITIONS*/
typedef struct _btree_header btree_header;
typedef struct _btree_node btree_node;

#define HEADER_SIZE 72
#define NODE_SIZE 72
#define BTREE_ORDER 6

/*HEADER AND NODE*/

struct _btree_header
{
    char status;
    int32_t root_node;
    int32_t level_number;
    int32_t next_rrn;
    int32_t key_number;
};

struct _btree_node
{
    int32_t level;  //Level to root.
    int32_t n;	    //Key number.
    struct {
	int32_t C;
	int32_t P;
    } keyValues[BTREE_ORDER-1];
    int32_t descendants[BTREE_ORDER];
};

/*TOP LEVEL DATA STRUCTURE*/
struct _btree_handle
{
    FILE* btree_file;		//File handler.
    btree_header header_buffer; //Updates on header will be written here.
    btree_node nodes_buffer[3];	//Space on main memory for running algorithms.
}; 

/*I/O FUNCTIONS*/

//Transforms header into a byte vector.
void* __header_to_bin_btree(btree_header a_header)
{
    void* ret_data = malloc(HEADER_SIZE);
    size_t offset = 0;

    memcpy(ret_data, &(a_header.status), sizeof(char));
    offset += sizeof(char);

    memcpy(ret_data+offset, &(a_header.root_node), sizeof(int32_t));
    offset += sizeof(int32_t);

    memcpy(ret_data+offset, &(a_header.level_number), sizeof(int32_t));
    offset += sizeof(int32_t);

    memcpy(ret_data+offset, &(a_header.next_rrn), sizeof(int32_t));
    offset += sizeof(int32_t);

    memcpy(ret_data+offset, &(a_header.key_number), sizeof(int32_t));
    offset += sizeof(int32_t);

    //Setting garbage here.
    memset(ret_data+offset, '$', HEADER_SIZE-offset);

    return ret_data;
}

//Transforms node into a byte vector.
void* __node_to_bin_btree(btree_node a_node)
{
    void* ret_data = malloc(NODE_SIZE);
    size_t offset = 0;

    memcpy(ret_data, &(a_node.level), sizeof(int32_t));
    offset += sizeof(int32_t);

    memcpy(ret_data+offset, &(a_node.n), sizeof(int32_t));
    offset += sizeof(int32_t);

    //Copying key/value pairs into node vector.
    for(int i = 0 ; i < BTREE_ORDER-1 ; i++)
    {
	memcpy(ret_data+offset, &(a_node.keyValues[i].C), sizeof(int32_t));
	offset += sizeof(int32_t);
	memcpy(ret_data+offset, &(a_node.keyValues[i].P), sizeof(int32_t));
	offset += sizeof(int32_t);
    }

    //Copying descendant rrn into node vector.
    for(int i = 0 ; i < BTREE_ORDER ; i++)
    {
	memcpy(ret_data+offset, &(a_node.descendants[i]), sizeof(int32_t));
	offset += sizeof(int32_t);
    }

    return ret_data;
}

btree_header __bin_to_header_btree(void* bin_data)
{
    btree_header ret;

    size_t offset = 0;

    memcpy(&(ret.status), bin_data+offset, sizeof(char));
    offset += sizeof(char);

    memcpy(&(ret.root_node), bin_data+offset, sizeof(int32_t));
    offset += sizeof(int32_t);

    memcpy(&(ret.level_number), bin_data+offset, sizeof(int32_t));
    offset += sizeof(int32_t);

    memcpy(&(ret.next_rrn), bin_data+offset, sizeof(int32_t));
    offset += sizeof(int32_t);

    memcpy(&(ret.key_number), bin_data+offset, sizeof(int32_t));
    offset += sizeof(int32_t);


    return ret;
}

btree_node __bin_to_node_btree(void* bin_data)
{
    btree_node ret;
    size_t offset = 0;

    memcpy(&(ret.level), bin_data, sizeof(int32_t));
    offset += sizeof(int32_t);

    memcpy(&(ret.n), bin_data+offset, sizeof(int32_t));
    offset += sizeof(int32_t);

    //Copying key/value pairs into node vector.
    for(int i = 0 ; i < BTREE_ORDER-1 ; i++)
    {
	memcpy(&(ret.keyValues[i].C), bin_data+offset, sizeof(int32_t));
	offset += sizeof(int32_t);
	memcpy(&(ret.keyValues[i].P), bin_data+offset, sizeof(int32_t));
	offset += sizeof(int32_t);
    }

    //Copying descendant rrn into node vector.
    for(int i = 0 ; i < BTREE_ORDER ; i++)
    {
	memcpy(&(ret.descendants[i]), bin_data+offset, sizeof(int32_t));
	offset += sizeof(int32_t);
    }

    return ret;
}

/*HEADER FUNCTIONS*/

//Reads header from file.
void __read_header_btree(BTREE* this_btree)
{
    char temp[HEADER_SIZE]; //MAYBE NOT OK.

    //Read bytes.
    fseek(this_btree->btree_file, 0, SEEK_SET);
    fread(temp, HEADER_SIZE, 1, this_btree->btree_file);
    this_btree->header_buffer = __bin_to_header_btree(temp);
}

//Writes header to file.
void __write_header_btree(BTREE* this_btree)
{
    void* temp;
    
    temp = __header_to_bin_btree(this_btree->header_buffer);
    fseek(this_btree->btree_file, 0, SEEK_SET);
    fwrite(temp, HEADER_SIZE, 1, this_btree->btree_file);

    free(temp);
}

/*BTREE ALGORITHM FUNCTIONS*/

//Searchs for node containing a given key. If no node found returns -1.
int __search_node_cont_key_btree()
{
    return 0;
}

/*EXPOSED FUNCTIONS*/

BTREE* openBTree(const char* filename, btree_err_t* err)
{
    BTREE* ret_btree;

    return ret_btree;
}

void closeBTree(BTREE* this_btree)
{

}

btree_err_t insertKeyValBTree(BTREE* this_btree, int key, int value)
{
    return OK;
}

int getValByKeyBTree()
{
    return 0;
}

