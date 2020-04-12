#ifndef GRAPH_H
#define GRAPH_H

typedef struct _graph GRAPH;
typedef unsigned int vertex_n;
typedef void err_t;
/*
typedef enum
{
	ADJ_MATRIX,
	ADJ_LIST
} graph_type;
*/

typedef unsigned char graph_type;

#define ADJ_MATRIX 0b000000001
#define ADJ_LIST   0b000000010
#define ORIENTED   0b000000100

GRAPH* new_graph(graph_type, int);
err_t insert_edge(GRAPH*, vertex_n, vertex_n);
err_t remove_edge(GRAPH*, vertex_n, vertex_n);
void print_graph(GRAPH*);
void delete_graph(GRAPH*);

#endif
