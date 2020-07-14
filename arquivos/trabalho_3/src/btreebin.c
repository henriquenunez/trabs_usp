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

int __search_node_by_key_btree(BTREE* this_btree,
				int key,
				btr_node_ret_t *ret_type,
				int *parent_node_rrn,
        int *counter);
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

btree_node __new_node_zeroes_btree()
{
    btree_node ret_node;
    ret_node.n = 0;
    ret_node.level = 1;
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


btr_node_ret_t __insert_key_val_at_node_l_r_btree(btree_node *a_node,
						    int key,
						    int value,
						    btree_node l_node,
						    btree_node r_node)
{
    if(a_node->n == BTREE_ORDER-1) //If node has maximum num of keys.
	return BTR_NODE_FULL;

    key_values_t temp_key_vals[BTREE_ORDER-1];
    int32_t temp_descendants[BTREE_ORDER];
    int i,j = 0;
    char inserted = false;
    int idx_ins;

    //Find index in which new kvp should be placed.
    for(i = 0 ; i < BTREE_ORDER-1 ; i++)
    {
	if(!inserted && (key < a_node->keyValues[j].C || a_node->keyValues[j].C == -1))
	{
	    idx_ins = i;
	    inserted = true;
	}
	else
	    j++;
    }

    #ifdef DEBUG_BTREE
    printf("Insertion index: %d\n", idx_ins);
    #endif

    //Now copy values
    j=0;
    for(i = 0 ; i < BTREE_ORDER-1; i++)
    {
	if(i == idx_ins) continue;
	temp_key_vals[i] = a_node->keyValues[j];
	temp_descendants[i] = a_node->descendants[j];
	temp_descendants[i+1] = a_node->descendants[j+1];
	j++;
    }

    //Insert only new key so it overrides prev
    temp_key_vals[idx_ins].C = key;
    temp_key_vals[idx_ins].P = value;
    temp_descendants[idx_ins] = l_node.node_rrn;
    temp_descendants[idx_ins+1] = r_node.node_rrn;

/*
if(!inserted && (key < a_node->keyValues[j].C || a_node->keyValues[j].C == -1))
	{
	    temp_key_vals[i].C = key;
	    temp_key_vals[i].P = value;
	    temp_descendants[i] = l_node.node_rrn;
	    temp_descendants[i+1] = r_node.node_rrn;
	    inserted = true;
	}
	else
	{
	    temp_key_vals[i] = a_node->keyValues[j];
	    temp_descendants[i] = a_node->descendants[j];
	    temp_descendants[i+1] = a_node->descendants[j+1];
	    j++;
	}*/
    a_node->n++;

    //Replace previous keyValues.
    memcpy(a_node->keyValues,
	    temp_key_vals,
	    (BTREE_ORDER-1)*sizeof(key_values_t));

    //Replace previous descendants.
    memcpy(a_node->descendants,
	    temp_descendants,
	    BTREE_ORDER * sizeof(int32_t));

    return BTR_NODE_OK;
}


btr_node_ret_t __split_node_l_r_btree(BTREE* this_btree,
				    btree_node *a_node,
				    key_values_t kvp, //Key:value to insert.
				    btree_node l_child, //Children of
				    btree_node r_child, //overflower key.
				    int parent_node_rrn)
{
    #define SPLIT_LENGTH ((int)(BTREE_ORDER/2))

    //We already know that the node must be split.
    key_values_t temp_key_vals[BTREE_ORDER]; //One more for the new key.
    int32_t temp_descendants[BTREE_ORDER+1];

    //Order keys, find median.
    int i,j = 0;
    char inserted = false;
    int idx_ins;

    //Find index in which new kvp should be placed.
    for(i = 0 ; i < BTREE_ORDER ; i++)
    {
	if(!inserted && (j >= BTREE_ORDER-1 || kvp.C < a_node->keyValues[j].C))
	{
	    idx_ins = i;
	    inserted = true;
	}
	else
	    j++;
    }

    //Copying values into temps.
    j=0;
    for(i = 0 ; i < BTREE_ORDER; i++)
    {
	if(i == idx_ins) continue;
	temp_key_vals[i] = a_node->keyValues[j];
	temp_descendants[i] = a_node->descendants[j];
	temp_descendants[i+1] = a_node->descendants[j+1];
	j++;
    }

    //Insert only new key so it overrides prev.
    temp_key_vals[idx_ins] = kvp;
    temp_descendants[idx_ins] = l_child.node_rrn;
    temp_descendants[idx_ins+1] = r_child.node_rrn;

    //The promoted key is always at this index.
    key_values_t promoted_key = temp_key_vals[SPLIT_LENGTH];

    //With values split, assign to 2 different nodes.
    btree_node l_node = __new_node_zeroes_btree(); //Same as original node.
    btree_node r_node = __new_node_zeroes_btree(); //Newly created node.

    l_node.n = SPLIT_LENGTH; //Key num on l and r node.
    r_node.n = SPLIT_LENGTH-1;

    //Set rrn of left node to the same of the original one.
    l_node.node_rrn = a_node->node_rrn;

    //Set rrn of the right node to the same of the new one.
    r_node.node_rrn = this_btree->header_buffer.next_rrn++;

    //Replace previous keyValues.
    memcpy(l_node.keyValues,
	    temp_key_vals,
	    sizeof(key_values_t) * SPLIT_LENGTH);

    //Replace previous descendants.
    memcpy(l_node.descendants,
	    temp_descendants,
	    sizeof(int32_t) * (SPLIT_LENGTH+1) );

    //Replace previous keyValues.
    memcpy(r_node.keyValues,
	    temp_key_vals + SPLIT_LENGTH + 1,
	    sizeof(key_values_t) * (SPLIT_LENGTH - 1) );

    //Replace previous descendants.
    memcpy(r_node.descendants,
	    temp_descendants + SPLIT_LENGTH + 1,
	    sizeof(int32_t) * SPLIT_LENGTH );

/*
    printf("Sorted keys: ");
    for(i = 0 ; i < BTREE_ORDER ; i++)
    {
	//In case key is the highest one.
	if(!inserted && (j >= BTREE_ORDER-1 ||  kvp.C < a_node->keyValues[j].C) )
	{
	    temp_key_vals[i] = kvp;
	    inserted = true;
	}
	else
	{
	    temp_key_vals[i] = a_node->keyValues[j++];
	}
	printf("%d:%d ", temp_key_vals[i].C, temp_key_vals[i].P);
    }


    //We already have the promoted key. Time to copy.

    #ifdef DEBUG_BTREE
    printf("\nMedian: %d:%d\n", temp_key_vals[SPLIT_LENGTH].C,
				temp_key_vals[SPLIT_LENGTH].P);
    #endif

    memset(l_key_vals, -1, sizeof(key_values_t)*(BTREE_ORDER-1));
    memcpy(l_key_vals,
	    temp_key_vals,
	    sizeof(key_values_t) * SPLIT_LENGTH);

    memset(r_key_vals, -1, sizeof(key_values_t)*(int)(BTREE_ORDER-1));
    memcpy(r_key_vals,
	    temp_key_vals + SPLIT_LENGTH+1,
	    sizeof(key_values_t) * (SPLIT_LENGTH-1));

    #ifdef DEBUG_BTREE
    printf("L          R:\n");
    for(i = 0 ; i < BTREE_ORDER-1 ; i++)
    {
	printf("%2d:%2d  %2d:%2d\n", l_key_vals[i].C,l_key_vals[i].P,
				    r_key_vals[i].C,r_key_vals[i].P);
    }
    #endif

    //With values split, assign to 2 different nodes.
    btree_node l_node = __new_node_zeroes_btree();
    btree_node r_node = __new_node_zeroes_btree();

    l_node.n = SPLIT_LENGTH; //Key num on l and r node.
    r_node.n = SPLIT_LENGTH-1;

    //Copying l and r kvps to nodes.
    memcpy(l_node.keyValues,
	    l_key_vals,
	    (BTREE_ORDER-1)*sizeof(key_values_t));

    memcpy(r_node.keyValues,
	    r_key_vals,
	    (BTREE_ORDER-1)*sizeof(key_values_t));

    //Now, need to copy l and r descendants...
    memcpy(l_node.descentants,)

    //Set rrn of left node to the same of the original one.
    l_node.node_rrn = a_node->node_rrn;

    //Set rrn of the right node to the same of the new one.
    r_node.node_rrn = this_btree->header_buffer.next_rrn++;
*/
    //Promote key to parent node.
    __promote_key_write_btree(this_btree,
				promoted_key,
				l_node,
				r_node,
				parent_node_rrn);

    return BTR_NODE_OK;
}


btr_node_ret_t __promote_key_write_btree(BTREE* this_btree,
					key_values_t promoted,
					btree_node l_node,
					btree_node r_node,
					int parent_node_rrn)
{
    btree_node parent_node;
    btr_node_ret_t op_res;
    void *node_bin;
    int counter;

    #ifdef DEBUG_BTREE
    printf("Promoting key...\n");
    #endif

    if(parent_node_rrn == -1)
    {
	#ifdef DEBUG_BTREE
	printf("New parent node...\n");
	#endif
	//Create a new parent node. This means we need to increase the level.
	parent_node = __new_node_zeroes_btree();
	parent_node.node_rrn = this_btree->header_buffer.next_rrn++;
	parent_node.level = l_node.level+1;

	//A new parent node always implies in a new root.
	this_btree->header_buffer.root_node = parent_node.node_rrn;

	this_btree->header_buffer.level_number++;
    }
    else
    {
	#ifdef DEBUG_BTREE
	printf("Parent node exists\n");
	#endif
	parent_node = __get_node_rrn_btree(this_btree, parent_node_rrn);
    }

	    #ifdef DEBUG_BTREE
    printf("Parent node rrn: %d\n", parent_node.node_rrn);
	#endif

    //Try to insert key at parent.
    op_res = __insert_key_val_at_node_l_r_btree(&parent_node,
						promoted.C,
						promoted.P,
						l_node,
						r_node);
    #ifdef DEBUG_BTREE
    __print_node_vals(parent_node);
    #endif

    if(op_res == BTR_NODE_FULL) //Then it's chained overflow...
    {
	#ifdef DEBUG_BTREE
	printf("Parent full during promotion!\n");
	#endif
/*
btr_node_ret_t __split_node_l_r_btree(BTREE* this_btree,
				    btree_node *a_node,
				    key_values_t kvp, //Key value to insert.
				    btree_node l_child,
				    btree_node r_child,
				    int parent_node_rrn)
*/
	int32_t parent_parent_rrn;
	__search_node_by_key_btree(this_btree,
				    parent_node.keyValues[0].C,
				    &op_res,
				    &parent_parent_rrn,
            &counter);
	__split_node_l_r_btree(this_btree,
				&parent_node,
				promoted,
				l_node,
				r_node,
				parent_parent_rrn);
    }

    //Flush changes.

    //Writing updated parent.
    fseek(this_btree->btree_file,
	    HEADER_SIZE + NODE_SIZE * parent_node.node_rrn,
	    SEEK_SET);
    node_bin = __node_to_bin_btree(parent_node);
    fwrite(node_bin, NODE_SIZE, 1, this_btree->btree_file);
    free(node_bin);

    //Writing updated l_child.
    fseek(this_btree->btree_file,
	    HEADER_SIZE + NODE_SIZE * l_node.node_rrn,
	    SEEK_SET);
    node_bin = __node_to_bin_btree(l_node);
    fwrite(node_bin, NODE_SIZE, 1, this_btree->btree_file);
    free(node_bin);

    //Writing new r_child.
    fseek(this_btree->btree_file,
	    HEADER_SIZE + NODE_SIZE * r_node.node_rrn,
	    SEEK_SET);
    node_bin = __node_to_bin_btree(r_node);
    fwrite(node_bin, NODE_SIZE, 1, this_btree->btree_file);
    free(node_bin);

    return BTR_NODE_OK;
}

btr_node_ret_t __split_node_btree(BTREE* this_btree,
				    btree_node *a_node,
				    key_values_t kvp, //Key value to insert.
				    int parent_node_rrn)
{
    #define SPLIT_LENGTH ((int)(BTREE_ORDER/2))

    //We already know that the node must be split.
    key_values_t temp_key_vals[BTREE_ORDER]; //One more for the new element.
    key_values_t l_key_vals[BTREE_ORDER-1]; //Keys on left node.
    key_values_t r_key_vals[BTREE_ORDER-1]; //Keys on right node.

    //Order keys, find median.
    int i,j = 0;
    char inserted = false;

    #ifdef DEBUG_BTREE
    printf("Sorted keys: ");
    #endif
    for(i = 0 ; i < BTREE_ORDER ; i++)
    {
	//In case key is the highest one.
	if(!inserted && (j >= BTREE_ORDER-1 ||  kvp.C < a_node->keyValues[j].C) )
	{
	    temp_key_vals[i] = kvp;
	    inserted = true;
	}
	else
	{
	    temp_key_vals[i] = a_node->keyValues[j++];
	}
	#ifdef DEBUG_BTREE
	printf("%d:%d ", temp_key_vals[i].C, temp_key_vals[i].P);
	#endif
    }

    #ifdef DEBUG_BTREE
    printf("\nMedian: %d:%d\n", temp_key_vals[SPLIT_LENGTH].C,
				temp_key_vals[SPLIT_LENGTH].P);
    #endif

    memset(l_key_vals, -1, sizeof(key_values_t)*(BTREE_ORDER-1));
    memcpy(l_key_vals,
	    temp_key_vals,
	    sizeof(key_values_t) * SPLIT_LENGTH);

    memset(r_key_vals, -1, sizeof(key_values_t)*(int)(BTREE_ORDER-1));
    memcpy(r_key_vals,
	    temp_key_vals + SPLIT_LENGTH+1,
	    sizeof(key_values_t) * (SPLIT_LENGTH-1));

    #ifdef DEBUG_BTREE
    printf("L          R:\n");
    for(i = 0 ; i < BTREE_ORDER-1 ; i++)
    {
	printf("%2d:%2d  %2d:%2d\n", l_key_vals[i].C,l_key_vals[i].P,
				    r_key_vals[i].C,r_key_vals[i].P);
    }
    #endif

    //With values split, assign to 2 different nodes.
    btree_node l_node = __new_node_zeroes_btree();
    btree_node r_node = __new_node_zeroes_btree();

    l_node.n = SPLIT_LENGTH; //Key num on l and r node.
    r_node.n = SPLIT_LENGTH-1;

    //Copying l and r kvps to nodes.
    memcpy(l_node.keyValues,
	    l_key_vals,
	    (BTREE_ORDER-1)*sizeof(key_values_t));

    memcpy(r_node.keyValues,
	    r_key_vals,
	    (BTREE_ORDER-1)*sizeof(key_values_t));

    //Set rrn of left node to the same of the original one.
    l_node.node_rrn = a_node->node_rrn;

    //Set rrn of the right node to the same of the new one.
    r_node.node_rrn = this_btree->header_buffer.next_rrn++;

    //Promote key to parent node.
    __promote_key_write_btree(this_btree,
				temp_key_vals[SPLIT_LENGTH],
				l_node,
				r_node,
				parent_node_rrn);

    return BTR_NODE_OK;
}

/*BTREE ALGORITHM FUNCTIONS*/

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

//Searchs for node containing a given key.
int __search_node_by_key_btree(BTREE* this_btree,
				int key,
				btr_node_ret_t *ret_type,
				int *parent_node_rrn,
        int *counter) //Parent will be returned here.
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
      (*counter)++;
	if(temp_search_node_rrn == -1)
	{
	    *ret_type = BTR_NODE_KEY_NOT_FOUND;
	    return prev_search_node_rrn;
	}

	*parent_node_rrn = prev_search_node_rrn;
	prev_search_node_rrn = temp_search_node_rrn;

	#ifdef DEBUG_BTREE
	printf(">>>Searching on rrn %d\n", temp_search_node_rrn);
	#endif

	temp_search_node =
	    __get_node_rrn_btree(this_btree, temp_search_node_rrn);

	for(i = 0 ; i < BTREE_ORDER-1 ; )
	{
	    #ifdef DEBUG_BTREE
	    printf(">>>>>Comparing %d with %d\n", key, temp_search_node.keyValues[i].C);
	    #endif

	    if(key == temp_search_node.keyValues[i].C)
	    {
		//Found key, stop searching.
		*ret_type = BTR_NODE_KEY_FOUND;
		return temp_search_node.node_rrn;
	    }

	    if(key < temp_search_node.keyValues[i].C)
	    {
		//Then, should go to descendants.
		temp_search_node_rrn = temp_search_node.descendants[i];
		break;
	    }

	    //In case we have reached end of node.
	    if(temp_search_node.keyValues[i].C == -1)
	    {
		temp_search_node_rrn = temp_search_node.descendants[i];
		break;
	    }
	    temp_search_node_rrn = temp_search_node.descendants[++i];
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

    #ifdef DEBUG_BTREE
    printf("\n>>> Num of keys: %d, Num of levels: %d\n",
    this_btree->header_buffer.key_number,
    this_btree->header_buffer.level_number);
    #endif

  free(this_btree);
}

btree_err_t insertKeyValBTree(BTREE *this_btree, int key, int value)
{
    void* node_bin;
    btree_node temp_node;
    key_values_t key_val_to_insert;
    int parent_insertion_node_rrn;
    btr_node_ret_t operation_res;
    int counter = 0;

    key_val_to_insert.C = key;
    key_val_to_insert.P = value;

    //First we must search...

    #ifdef DEBUG_BTREE
    printf("Begin searching...\n");
    #endif

    int rrn = __search_node_by_key_btree(this_btree,
					    key,
					    &operation_res,
					    &parent_insertion_node_rrn,
              &counter);

    #ifdef DEBUG_BTREE
    printf("Result type is %d, rrn is %d, parent %d\n", operation_res,
							rrn,
							parent_insertion_node_rrn);
    #endif

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
	#ifdef DEBUG_BTREE
	printf("Split needed!\n");
	#endif
	__split_node_btree(this_btree,
			    &temp_node,
			    key_val_to_insert,
			    parent_insertion_node_rrn);
    }
    else
    {
	#ifdef DEBUG_BTREE
	printf("Split not needed!\n");
	#endif

	if(ftell(this_btree->btree_file) != HEADER_SIZE + rrn * NODE_SIZE)
	    fseek(this_btree->btree_file,
		    HEADER_SIZE + rrn * NODE_SIZE,
		    SEEK_SET);

	node_bin = __node_to_bin_btree(temp_node);
	fwrite(node_bin, NODE_SIZE, 1, this_btree->btree_file);
	free(node_bin);
    }

    //Increase counter
    this_btree->header_buffer.key_number++;

    return BTR_OK;
}

int* getValByKeyBTree(BTREE *this_btree, int key)
{
    btree_node temp_node;
    btr_node_ret_t search_result;

    #ifdef DEBUG_BTREE
    printf("Begin searching for value\n");
    #endif
    int rrn, parent_rrn, i = 0;
    rrn = __search_node_by_key_btree(this_btree, key, &search_result, &parent_rrn, &i);

    #ifdef DEBUG_BTREE
    printf("Result type is %d, rrn is %d\n", search_result, rrn);
    #endif

    int *ret_val = (int*) malloc(2*sizeof(int));
    if(search_result == BTR_NODE_KEY_FOUND)
    {
	temp_node = __get_node_rrn_btree(this_btree, rrn);

	#ifdef DEBUG_BTREE
	printf("Key found!\n");
	//Begin searching node for given key.
	printf(">>printing node!\n");
	__print_node_vals(temp_node);
	#endif
	ret_val[0] = __value_from_key_node_btree(temp_node, key);

	//ret_val = __value_from_key_node_btree(temp_node, key);

	#ifdef DEBUG_BTREE
	if(ret_val[0] == -1)
	{
	    printf("Deu ruim!\n");
	}
	printf("Queried key: %d, value is %d\n", key, ret_val[0]);
	#endif
	/*#ifdef DEBUG_BTREE
	printf("Queried key: %d, value is %d\n", key, ret_val);
	#endif*/
    }

    ret_val[1] = i;

    return ret_val;
}
