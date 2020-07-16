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
    int32_t node_rrn; //Just a helper, is not written.
    int32_t level; //Level to leaves.
    int32_t n;     //Key number.
    key_values_t keyValues[BTREE_ORDER - 1];
    int32_t descendants[BTREE_ORDER];
};

/* HELPER RETURN TYPE*/
typedef enum _btree_node_ret
{
    BTR_NODE_OK,
    BTR_NODE_ERROR,
    BTR_NODE_KEY_FOUND,
    BTR_NODE_KEY_NOT_FOUND,
    BTR_NODE_PROMO,
    BTR_NODE_NO_PROMO //In this case we will spend a lot of money.
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

btr_node_ret_t __promote_key_write_btree(BTREE*,
					key_values_t,
					btree_node,
					btree_node,
					int);


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

//Just a helper one
void __print_node_vals(btree_node temp_node)
{
    printf("Node rrn: %d\n", temp_node.node_rrn);
    for(int i = 0 ; i < BTREE_ORDER-1 ; i++)
    {
	printf("%d key: %d val: %d\n", i, temp_node.keyValues[i].C,
					    temp_node.keyValues[i].P);

    }
    for(int i = 0 ; i < BTREE_ORDER ; i++)
    {
	printf("des: %d ", temp_node.descendants[i]);
    }
    printf("\n");
}

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

  newNode.node_rrn = rrn;
  return newNode;
}

void __write_node_btree(BTREE* this_btree, btree_node a_node)
{
    void* bin_data;
    bin_data = __node_to_bin_btree(a_node);
    fseek(this_btree->btree_file,
	  HEADER_SIZE + NODE_SIZE*a_node.node_rrn,
	  SEEK_SET);
    fwrite(bin_data, NODE_SIZE, 1, this_btree->btree_file);
    free(bin_data);
}

btree_node __new_node_zeroes_btree()
{
    btree_node ret_node;
    ret_node.n = 0;
    ret_node.level = 1;
    memset(ret_node.descendants, -1, sizeof(int32_t) * BTREE_ORDER);
    memset(ret_node.keyValues, -1, sizeof(key_values_t) * (BTREE_ORDER-1));

    return ret_node;
}

//Returns value.
int __value_from_key_node_btree(btree_node a_node, int key)
{
    int ret_val = -1;
    for(int i = 0 ; i < BTREE_ORDER-1 ; i++)
    {
	if(a_node.keyValues[i].C == key)
	{
	    ret_val = a_node.keyValues[i].P;
	    break;
	}
    }

    return ret_val;
}

/*BTREE ALGORITHM FUNCTIONS*/
btr_node_ret_t __search_btree(BTREE* this_btree,
			      int curr_rrn,
			      int search_key,
			      int* found_rrn,
			      int* found_index,
			      int* count)
{
    if (curr_rrn == -1) return BTR_NODE_KEY_NOT_FOUND;

    int i;
    btree_node curr_node = __get_node_rrn_btree(this_btree, curr_rrn);
    (*count)++;

    for (i = 0 ; i < curr_node.n ; i++)
    {
	if (search_key < curr_node.keyValues[i].C)
	{
	    //Key aint found, exit loop.
	    break;
	}
	if (search_key == curr_node.keyValues[i].C)
	{
	    *found_rrn = curr_rrn;
	    *found_index = i;
	    return BTR_NODE_KEY_FOUND;
	}
    }
    return __search_btree(this_btree,
			  curr_node.descendants[i],
			  search_key,
			  found_rrn,
			  found_index,
			  count);
}

void __split_node_btree(BTREE* this_btree,
			key_values_t inserted,
			int ins_r_child_rrn,
			btree_node* splitted_page,
			key_values_t* promoted_key,
			int* promoted_r_child_rrn,
			btree_node* new_page)
{
    #define SPLIT_LENGTH (BTREE_ORDER/2)
    key_values_t temp_keys[BTREE_ORDER];
    int32_t temp_descendants[BTREE_ORDER+1];
    int i, j = 0, ins_idx;

    memcpy(temp_keys,
	    (*splitted_page).keyValues,
	    sizeof(key_values_t)*(BTREE_ORDER-1));
    memcpy(temp_descendants,
	    (*splitted_page).descendants,
	    sizeof(int32_t)*(BTREE_ORDER));

    //Find in which position it should be.
    for(i = 0 ; i < BTREE_ORDER-1 ; i++)
	if(inserted.C < (*splitted_page).keyValues[i].C)
	    break;
    ins_idx = i;

    //Now copy everyone into those temp buffers.
    for(i = 0 ; i < BTREE_ORDER ; i++)
    {
	if(i == ins_idx)
	    continue;
	temp_descendants[i] = (*splitted_page).descendants[j];
	temp_keys[i] = (*splitted_page).keyValues[j];
	temp_descendants[i+1] = (*splitted_page).descendants[j+1];
	j++;
    }
    //Copy inserted key.
    temp_keys[ins_idx] = inserted;
    temp_descendants[ins_idx+1] = ins_r_child_rrn;

    *new_page = __new_node_zeroes_btree();
    (*new_page).node_rrn = this_btree->header_buffer.next_rrn++;

    //Now set promoted key and its child.
    *promoted_key = temp_keys[SPLIT_LENGTH];
    *promoted_r_child_rrn = (*new_page).node_rrn;

    //Setting everyone to null before copying.
    memset( (*splitted_page).keyValues,
	    -1,
	    sizeof(key_values_t)*(BTREE_ORDER-1));
    memset( (*splitted_page).descendants,
	    -1,
	    sizeof(int32_t)*BTREE_ORDER);

    //Copy keyvalues.
    memcpy((*splitted_page).keyValues,
	    temp_keys,
	    sizeof(key_values_t) * SPLIT_LENGTH);

    memcpy((*new_page).keyValues,
	    temp_keys + SPLIT_LENGTH + 1,
	    sizeof(key_values_t) * (SPLIT_LENGTH-1));

    //Copy descendants.
    memcpy((*splitted_page).descendants,
	    temp_descendants,
	    sizeof(int32_t) * (SPLIT_LENGTH+1));

    memcpy((*new_page).descendants,
	    temp_descendants + SPLIT_LENGTH + 1,
	    sizeof(int32_t) * (SPLIT_LENGTH));

    //Setting number of keys.
    (*splitted_page).n = SPLIT_LENGTH; //has 3 keys in this case.
    (*new_page).n = SPLIT_LENGTH-1; //has 2 keys in this case.

    //Level must be the same for both pages.
    (*new_page).level = (*splitted_page).level;

    #undef SPLIT_LENGTH
}

btr_node_ret_t __insert_key_val_btree(BTREE* this_btree,
				      int curr_rrn,
				      key_values_t inserted,
				      key_values_t* promoted,
				      int* right_child_rrn)
{
    if (curr_rrn == -1)
    {
	*promoted = inserted;
	*right_child_rrn = -1;
	return BTR_NODE_PROMO;
    }

    int i;
    btree_node curr_page = __get_node_rrn_btree(this_btree, curr_rrn);

    for (i = 0 ; i < curr_page.n ; i++)
    {
	if (inserted.C == curr_page.keyValues[i].C)
	    return BTR_NODE_ERROR;
	if (inserted.C < curr_page.keyValues[i].C)
	    break;
    }

    int recur_right_child_rrn;
    key_values_t recur_promo_key;
    btree_node new_page; //In case of overflow.

    //Calling recursively, until base case is reached.
    btr_node_ret_t rec_ret = __insert_key_val_btree(this_btree,
						    curr_page.descendants[i],
						    inserted,
						    &recur_promo_key,
						    &recur_right_child_rrn);
    if (rec_ret == BTR_ERROR || rec_ret == BTR_NODE_NO_PROMO)
	return rec_ret;

    if (curr_page.n < BTREE_ORDER-1) //There is space.
    {
	key_values_t temp_keys[BTREE_ORDER-1];
	int32_t temp_descendants[BTREE_ORDER];
	int j = 0;

	memset(temp_keys,
		-1,
		sizeof(key_values_t)*(BTREE_ORDER-1));
	memset(temp_descendants,
		-1,
		sizeof(int32_t)*(BTREE_ORDER));

	//Find in which position it should be.
	for(i = 0 ; i < BTREE_ORDER-1 ; i++)
	    if(recur_promo_key.C < curr_page.keyValues[i].C ||
		curr_page.keyValues[i].C == -1)
		break;
	int32_t ins_idx = i;

	//Now copy everyone into those temp buffers.
	for(i = 0 ; i < BTREE_ORDER-1 ; i++)
	{
	    if(i == ins_idx)
		continue;
	    temp_descendants[i] = curr_page.descendants[j];
	    temp_keys[i] = curr_page.keyValues[j];
	    temp_descendants[i+1] = curr_page.descendants[j+1];
	    j++;
	}
	//Copy inserted key.
	temp_keys[ins_idx] = recur_promo_key;
	temp_descendants[ins_idx+1] = recur_right_child_rrn;

        //Copy keyvalues.
        memcpy(curr_page.keyValues,
		temp_keys,
		sizeof(key_values_t)*(BTREE_ORDER-1));
        //Copy descendants.
        memcpy(curr_page.descendants,
		temp_descendants,
		    sizeof(int32_t)*(BTREE_ORDER));
	curr_page.n++;
	__write_node_btree(this_btree, curr_page);

	return BTR_NODE_NO_PROMO; //We cry because we wanted cheap things.
    }
    else
    {	//In this case, we have no space no we need to split.
	__split_node_btree(this_btree,
			    recur_promo_key,
			    recur_right_child_rrn,
			    &curr_page,
			    promoted,
			    right_child_rrn,
			    &new_page);
	__write_node_btree(this_btree, curr_page);
	__write_node_btree(this_btree,  new_page);

	return BTR_NODE_PROMO;
    }
}

/*
void __split_node_btree(BTREE* this_btree,
			key_values_t inserted,
			int ins_r_child_rrn,
			btree_node* splitted_page,
			key_values_t* promoted_key,
			int* promoted_r_child_rrn,
			btree_node* new_page)
*/
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

    #ifdef DEBUG_BTREE
    printf("\n>>> Num of keys: %d, Num of levels: %d\n",
    this_btree->header_buffer.key_number,
    this_btree->header_buffer.level_number);
    #endif

  free(this_btree);
}

btree_err_t insertKeyValBTree(BTREE *this_btree, int key, int value)
{
    key_values_t kvp; //Setting key for insertion.
    kvp.C = key;
    kvp.P = value;
    key_values_t promoted_key; //In case of root overflow.
    int32_t promoted_key_r_child;
    btr_node_ret_t ins_ret_code;

    //If we just created tree, set new node as root.
    if(this_btree->header_buffer.root_node == -1)
    {
	btree_node new_root_node = __new_node_zeroes_btree();
	new_root_node.node_rrn = this_btree->header_buffer.next_rrn++;
	__write_node_btree(this_btree, new_root_node);
	this_btree->header_buffer.root_node = new_root_node.node_rrn;
	this_btree->header_buffer.level_number = 1;
    }

    ins_ret_code = __insert_key_val_btree(this_btree,
					  this_btree->header_buffer.root_node,
					  kvp,
					  &promoted_key,
					  &promoted_key_r_child);

    if (ins_ret_code == BTR_NODE_PROMO)
    {
	//Root suffered overflow.
	btree_node new_root_node = __new_node_zeroes_btree();
	new_root_node.node_rrn = this_btree->header_buffer.next_rrn++;

	new_root_node.keyValues[0] = promoted_key;
					//Previous root node.
	new_root_node.descendants[0] = this_btree->header_buffer.root_node;
	new_root_node.descendants[1] = promoted_key_r_child;

	new_root_node.n = 1; //Only one key inserted.

	//Level number increases.
	this_btree->header_buffer.level_number++;
	new_root_node.level = this_btree->header_buffer.level_number;
	__write_node_btree(this_btree, new_root_node);
	this_btree->header_buffer.root_node = new_root_node.node_rrn;
    }

    if(ins_ret_code == BTR_NODE_ERROR)
	return BTR_ERROR;

    this_btree->header_buffer.key_number++;
    return BTR_OK;
}

int getValByKeyBTree(BTREE *this_btree, int key, int* num_iter)
{
    int found_rrn;
    int found_index;

    //We must do a simple search.
    btr_node_ret_t ret = __search_btree(this_btree,
					this_btree->header_buffer.root_node,
					key,
					&found_rrn,
					&found_index,
					num_iter);

    if(ret == BTR_NODE_KEY_FOUND) //Then key was found.
    {
	btree_node node_cont_key = __get_node_rrn_btree(this_btree, found_rrn);
	//Now search the node.
	for(int i = 0 ; i < node_cont_key.n ; i++)
	    if(node_cont_key.keyValues[i].C == key)
		return node_cont_key.keyValues[i].P; //The value we want to seek.
    }
    return -1;
}

/*
Doesn't everyone belong
In the arms of the sacred
Why do we pretend we're wrong?
Has our young courage faded?

Shots were fired on the street
By the church where we used to meet
Angel down, angel down
Why do people just stand around?
*/

