#include "btreebin.h"

#include <stdbool.h>
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

typedef struct
{
    int32_t C;
    int32_t P;
} key_values_t;

struct _btree_node
{
    int32_t level; //Level to root.
    int32_t n;     //Key number.
    key_values_t keyValues[BTREE_ORDER - 1];
    int32_t descendants[BTREE_ORDER];
};

/* HELPER RETURN TYPE*/

typedef enum _btree_node_ret
{
    BTR_NODE_OK,
    BTR_NODE_KEY_FOUND,
    BTR_NODE_KEY_NOT_FOUND,
    BTR_NODE_FULL
} btr_node_ret_t;

/*TOP LEVEL DATA STRUCTURE*/
struct _btree_handle
{
  FILE *btree_file;           //File handler.
  btree_header header_buffer; //Updates on header will be written here.
  btree_node nodes_buffer[3]; //Space on main memory for running algorithms.
};

/*I/O FUNCTIONS*/

//Transforms header into a byte vector.
void *__header_to_bin_btree(btree_header a_header)
{
  void *ret_data = malloc(HEADER_SIZE);
  size_t offset = 0;

  memcpy(ret_data, &(a_header.status), sizeof(char));
  offset += sizeof(char);

  memcpy(ret_data + offset, &(a_header.root_node), sizeof(int32_t));
  offset += sizeof(int32_t);

  memcpy(ret_data + offset, &(a_header.level_number), sizeof(int32_t));
  offset += sizeof(int32_t);

  memcpy(ret_data + offset, &(a_header.next_rrn), sizeof(int32_t));
  offset += sizeof(int32_t);

  memcpy(ret_data + offset, &(a_header.key_number), sizeof(int32_t));
  offset += sizeof(int32_t);

  //Setting garbage here.
  memset(ret_data + offset, '$', HEADER_SIZE - offset);

  return ret_data;
}

//Transforms node into a byte vector.
void *__node_to_bin_btree(btree_node a_node)
{
  void *ret_data = malloc(NODE_SIZE);
  size_t offset = 0;

  memcpy(ret_data, &(a_node.level), sizeof(int32_t));
  offset += sizeof(int32_t);

  memcpy(ret_data + offset, &(a_node.n), sizeof(int32_t));
  offset += sizeof(int32_t);

  //Copying key/value pairs into node vector.
  for (int i = 0; i < BTREE_ORDER - 1; i++)
  {
    memcpy(ret_data + offset, &(a_node.keyValues[i].C), sizeof(int32_t));
    offset += sizeof(int32_t);
    memcpy(ret_data + offset, &(a_node.keyValues[i].P), sizeof(int32_t));
    offset += sizeof(int32_t);
  }

  //Copying descendant rrn into node vector.
  for (int i = 0; i < BTREE_ORDER; i++)
  {
    memcpy(ret_data + offset, &(a_node.descendants[i]), sizeof(int32_t));
    offset += sizeof(int32_t);
  }

  return ret_data;
}

btree_header __bin_to_header_btree(void *bin_data)
{
  btree_header ret;

  size_t offset = 0;

  memcpy(&(ret.status), bin_data + offset, sizeof(char));
  offset += sizeof(char);

  memcpy(&(ret.root_node), bin_data + offset, sizeof(int32_t));
  offset += sizeof(int32_t);

  memcpy(&(ret.level_number), bin_data + offset, sizeof(int32_t));
  offset += sizeof(int32_t);

  memcpy(&(ret.next_rrn), bin_data + offset, sizeof(int32_t));
  offset += sizeof(int32_t);

  memcpy(&(ret.key_number), bin_data + offset, sizeof(int32_t));
  offset += sizeof(int32_t);

  return ret;
}

btree_node __bin_to_node_btree(void *bin_data)
{
  btree_node ret;
  size_t offset = 0;

  memcpy(&(ret.level), bin_data, sizeof(int32_t));
  offset += sizeof(int32_t);

  memcpy(&(ret.n), bin_data + offset, sizeof(int32_t));
  offset += sizeof(int32_t);

  //Copying key/value pairs into node vector.
  for (int i = 0; i < BTREE_ORDER - 1; i++)
  {
    memcpy(&(ret.keyValues[i].C), bin_data + offset, sizeof(int32_t));
    offset += sizeof(int32_t);
    memcpy(&(ret.keyValues[i].P), bin_data + offset, sizeof(int32_t));
    offset += sizeof(int32_t);
  }

  //Copying descendant rrn into node vector.
  for (int i = 0; i < BTREE_ORDER; i++)
  {
    memcpy(&(ret.descendants[i]), bin_data + offset, sizeof(int32_t));
    offset += sizeof(int32_t);
  }

  return ret;
}

/*HEADER FUNCTIONS*/

// Creates new header
void __init_header_btree(BTREE *this_btree){
    #define H this_btree->header_buffer
    H.status = '0';
    H.key_number = 0;
    H.level_number = 0;
    H.next_rrn = 0;
    H.root_node = -1;
    #undef H
}

//Reads header from file.
void __read_header_btree(BTREE *this_btree)
{
  char temp[HEADER_SIZE]; //MAYBE NOT OK.

  //Read bytes.
  fseek(this_btree->btree_file, 0, SEEK_SET);
  fread(temp, HEADER_SIZE, 1, this_btree->btree_file);
  this_btree->header_buffer = __bin_to_header_btree(temp);
}

//Writes header to file.
void __write_header_btree(BTREE *this_btree)
{
  void *temp;

  temp = __header_to_bin_btree(this_btree->header_buffer);
  fseek(this_btree->btree_file, 0, SEEK_SET);
  fwrite(temp, HEADER_SIZE, 1, this_btree->btree_file);

  free(temp);
}

/* NODE FUNCTIONS */

// Read node at rrn
btree_node __get_node_rrn_btree(BTREE *this_btree, int rrn)
{

  // Seek correct position in file
  fseek(this_btree->btree_file, rrn * NODE_SIZE + HEADER_SIZE, SEEK_SET);

  // Read and put in void array
  void *buffer = malloc(NODE_SIZE);
  fread(buffer, NODE_SIZE, 1, this_btree->btree_file);

  // Transforms bytes into struct
  btree_node newNode = __bin_to_node_btree(buffer);

  // Frees buffer and returns node
  free(buffer);
  return newNode;
}

btree_node __new_node_zeroes_btree()
{
    btree_node ret_node;
    ret_node.n = 0;
    ret_node.level = -1;
    memset(ret_node.descendants, -1, sizeof(int32_t) * BTREE_ORDER);
    memset(ret_node.keyValues, -1, sizeof(key_values_t) * BTREE_ORDER-1);

    return ret_node;
}

btr_node_ret_t __insert_key_val_at_node_btree(btree_node *a_node, int key, int value)
{
    if(a_node->n == BTREE_ORDER-1) //If node has maximum num of keys.
	return BTR_NODE_FULL;

    key_values_t temp_key_vals[BTREE_ORDER-1];
    int i,j = 0;
    char inserted = false;

    //If node has space, insert in correct order and increase num keys.
    for(i = 0 ; i < BTREE_ORDER-1 ; i++)
    {
	if(!inserted && (key < a_node->keyValues[j].C || a_node->keyValues[j].C == -1))
	{
	    temp_key_vals[i].C = key;
	    temp_key_vals[i].P = value;
	    inserted = true;
	    //continue;
	}
	else
	{
	    temp_key_vals[i] = a_node->keyValues[j++];
	}
    }

    a_node->n++;
    //Replace previous keyValues.
    memcpy(a_node->keyValues,
	    temp_key_vals,
	    (BTREE_ORDER-1)*sizeof(key_values_t));

    return BTR_NODE_OK; 
}

/*BTREE ALGORITHM FUNCTIONS*/

/*
//Returns index on file.
int __scan_node_for_key(btree_node a_node, int key, btr_node_ret_t *ret_type)
{
    int i;

    //Begin scan on node.
    for(i = 0 ; i < BTREE_ORDER-1 ; i++)
    {
	if(key == a_node.keyValues[i].C) //Key matches
	{
	    *ret_type = BTR_INDEX_VALUE; //Return is rrn on indexed file.
	    return a_node.keyValues[i].P;
	}

	//If key is of lower val, use i to search on descendants.
	if(key < a_node.keyValues[i].C)
	    break;
    }

    *ret_type = BTR_NODE_RRN;

    //In case search result is -1, node doesnt exist yet.
    return a_node->descendants[i];
}*/

//Searchs for node containing a given key.
int __search_node_by_key_btree(BTREE* this_btree, int key, btr_node_ret_t *ret_type)
{
  btree_node temp_search_node;
  int temp_search_node_rrn;
  int prev_search_node_rrn;
  int i;

    //Begin scanning by root node.
    temp_search_node_rrn = this_btree->header_buffer.root_node;
    prev_search_node_rrn = -1;

    while(1)
    {
	if(temp_search_node_rrn == -1)
	{
	    *ret_type = BTR_NODE_KEY_NOT_FOUND;
	    return prev_search_node_rrn;
	}

	prev_search_node_rrn = temp_search_node_rrn;
	
	printf("Searching on rrn %d\n", temp_search_node_rrn);


	temp_search_node =
	    __get_node_rrn_btree(this_btree, temp_search_node_rrn);

	for(i = 0 ; i < BTREE_ORDER-1 ; )
	{
	    if(key < temp_search_node.keyValues[i].C)
	    {
		//Then, should go to descentants.
		temp_search_node_rrn = temp_search_node.descendants[i];
		break;
	    }

	    if(key == temp_search_node.keyValues[i].C)
	    {
		//Found key, stop searching.
		*ret_type = BTR_NODE_KEY_FOUND;
		return temp_search_node_rrn;
	    }

	    temp_search_node_rrn = temp_search_node.descendants[++i];
	}
    }
  }
}

/*EXPOSED FUNCTIONS*/

BTREE *openBTree(const char *filename, btree_err_t *err)
{
  *err = BTR_OK;

  // Allocate struct
  BTREE *ret_btree = (BTREE *)malloc(sizeof(BTREE));

  // Open file
  ret_btree->btree_file = fopen(filename, "r+b");

  // File does not exist, create file
  if (ret_btree->btree_file == NULL)
  {

    ret_btree->btree_file = fopen(filename, "w+bx");
    __init_header_btree(ret_btree);
    *err = BTR_NEW_FILE;
  }
  else
  { // File exists

    // Read header from file
    __read_header_btree(ret_btree);

    // Check file consistency
    if (ret_btree->header_buffer.status != '1')
    {
      // Inconsistent, clear memory and return null
      fclose(ret_btree->btree_file);
      free(ret_btree);
      *err = BTR_CORRUPTED;
      return NULL;
    }

    // Loads root node
    ret_btree->nodes_buffer[0] = __get_node_rrn_btree(ret_btree,
                                                      ret_btree->header_buffer.root_node);
  }

  // Failed to create file
  if (ret_btree->btree_file == NULL)
  {
    closeBTree(ret_btree);
    *err = BTR_ERROR;
    return NULL;
  }

  //After all error checking, set status to '0' and update on file.
  ret_btree->header_buffer.status = '0';
  __write_header_btree(ret_btree);

  return ret_btree;
}

void closeBTree(BTREE *this_btree)
{
  // Updates header to consistent, closes file and frees struct
  this_btree->header_buffer.status = '1';
  __write_header_btree(this_btree);
  fclose(this_btree->btree_file);
  free(this_btree);
}

btree_err_t insertKeyValBTree(BTREE *this_btree, int key, int value)
{
    void* node_bin;
    btree_node temp_node;
    btr_node_ret_t operation_res;

    //First we must search...
    
    printf("Begin searching...\n");
    int rrn = __search_node_by_key_btree(this_btree, key, &operation_res);
    printf("Result type is %d, rrn is %d\n", operation_res, rrn);

    if(rrn == -1) //If rrn is -1, btree was empty
    {
	//Create a new node and call it root.
	temp_node = __new_node_zeroes_btree();
	__insert_key_val_at_node_btree(&temp_node, key, value);

	fseek(this_btree->btree_file, HEADER_SIZE, SEEK_SET);

	//Set root node.
	this_btree->header_buffer.root_node = 0;

	//Set number of nodes.
	this_btree->header_buffer.next_rrn++;
	this_btree->header_buffer.key_number++;
	
	//Write node at rrn 0
	node_bin = __node_to_bin_btree(temp_node);
	fwrite(node_bin, NODE_SIZE, 1, this_btree->btree_file);
	free(node_bin);

	return BTR_OK;
    }

    temp_node = __get_node_rrn_btree(this_btree, rrn);

    //Found suitable node. Lets try to insert.
    operation_res = __insert_key_val_at_node_btree(&temp_node, key, value);

    //In case of overflow...
    if(operation_res == BTR_NODE_FULL)
    {
	printf("Split needed!\n");
    }
    else
    {
	printf("Split not needed!\n");
	
	//Increase counter
	this_btree->header_buffer.key_number++;

	if(ftell(this_btree->btree_file) != HEADER_SIZE + rrn * NODE_SIZE)
	    fseek(this_btree->btree_file,
		    HEADER_SIZE + rrn * NODE_SIZE,
		    SEEK_SET);
	
	node_bin = __node_to_bin_btree(temp_node);
	fwrite(node_bin, NODE_SIZE, 1, this_btree->btree_file);
	free(node_bin);
    }

    return BTR_OK;
}

int getValByKeyBTree(BTREE *this_btree, int key)
{
    btree_node temp_node;
    btr_node_ret_t search_result;
/*
    //Reading node rrn 2.
    temp_node = __get_node_rrn_btree(this_btree, 2);

  //Reading node rrn 2.
  temp_node = __get_node_rrn_btree(this_btree, 2);

  printf("Node 2\n");

    }
*/
    printf("Begin searching...\n");
    int rrn;
    rrn = __search_node_by_key_btree(this_btree, key, &search_result);

  printf("Result type is %d, rrn is %d\n", search_result, rrn);

  return 0;
}
