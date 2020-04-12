#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

typedef struct _vector
{
    int size;
    void* data;
} VECTOR;

typedef struct _pair
{
    int first;
    int second;
} PAIR;

typedef struct _matrix
{
    int size;
    int **content;
} MATRIX;

struct _graph
{
    graph_type _type;
    union
    {
	VECTOR adj_list;
	MATRIX adj_matrix;
    };
};

MATRIX new_adj_matrix(int size)
{
    MATRIX ret_matrix;

    int **matrix_ptr;

    matrix_ptr = (int**) malloc (size * sizeof(int*));
    if (matrix_ptr == NULL); //deu caca

    for (int i = 0 ; i < size ; i++)
    {
	//already inserts zeroes into matrix
	matrix_ptr[i] = (int*) calloc (size, sizeof(int));
	if (matrix_ptr[i] == NULL); //deu caca
    }

    ret_matrix.size = size;
    ret_matrix.content = matrix_ptr;

    return ret_matrix;
}

void delete_adj_matrix(MATRIX *this_matrix)
{
    for (int i = 0 ; i < this_matrix->size ; i++)
    {
	free(this_matrix->content[i]);
    }

    free(this_matrix->content);

    this_matrix->size = 0;
    this_matrix->content = NULL;
}

GRAPH* new_graph(graph_type _type, int vertex_num)
{
    GRAPH* ret_ref;

    ret_ref = (GRAPH*) malloc (sizeof(GRAPH));
    ret_ref->_type = _type;

    if (_type & ADJ_MATRIX)
    {
	ret_ref->adj_matrix = new_adj_matrix(vertex_num);
    }else; //type is adj list

    return ret_ref;
}

void delete_graph(GRAPH* this_graph)
{
    if (this_graph->_type & ADJ_MATRIX)
    {
	//takes the address of the matrix in the graph
	delete_adj_matrix(&(this_graph->adj_matrix));
    }
    //this_graph->size = -1;
    free(this_graph);
}

err_t insert_edge(GRAPH* this_graph, vertex_n src, vertex_n dest)
{
    if (this_graph->_type & ADJ_MATRIX)
    {
	//if is not oriented, fill the opposite way
	if ((this_graph->_type & ORIENTED) == 0)
	    this_graph->adj_matrix.content[dest][src] = 1;
	this_graph->adj_matrix.content[src][dest] = 1;
    }
}

err_t remove_edge(GRAPH* this_graph, vertex_n src, vertex_n dest)
{
    if (this_graph->_type & ADJ_MATRIX)
    {
	//if is not oriented, remove the opposite way
	if ((this_graph->_type & ORIENTED) == 0)
	    this_graph->adj_matrix.content[dest][src] = 0;
	this_graph->adj_matrix.content[src][dest] = 0;
    }
}

void print_graph(GRAPH* this_graph)
{
    #define _size (this_graph->adj_matrix.size)

    if (this_graph->_type & ADJ_MATRIX)
    {
	for (int i = 0 ; i < _size ; i++)
	{
	    for (int j = 0 ; j < _size ; j++)
	    {
		printf("%d ", this_graph->adj_matrix.content[i][j]);
	    }
	    printf("\n");
	}
	printf("\n");
    }
    #undef _size
}
