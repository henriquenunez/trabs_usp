#ifndef GRAPH_H
#define GRAPH_H

typedef struct _graph GRAPH;
typedef unsigned int vertex_n;

typedef enum
{
	AJD_MATRIX,
	ADJ_LIST
} graph_type;

GRAPH* new_graph(graph_type);
err_t insert_edge(GRAPH*, vertex_n, vertex_n);
err_t remove_edge(GRAPH*, vertex_n, vertex_n);
void print_adj_matrix(GRAPH*);
void delete_graph();

#endif
