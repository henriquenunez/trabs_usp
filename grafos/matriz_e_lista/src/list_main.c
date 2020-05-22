#include <stdio.h>
#include "graph.h"

int main()
{
    GRAPH *a_graph;
    graph_type a_graph_type = ADJ_LIST;
    int nops;
    int size;
    int src, dest;
    int op;

    //Gets size and number of ops
    scanf(" %d %d ", &size, &nops);

    a_graph = new_graph(a_graph_type, size);

    while(nops--)
    {
	scanf(" %d %d ", &src, &dest);
	if (src < 0 || dest < 0) break;
	insert_edge(a_graph, src, dest);
	//print_graph(a_graph);
    }

    //getting again number of operations
    scanf(" %d ", &nops);
    //printf("%d operations!\n", nops);

    while(nops--)
    {
	scanf("%d", &op);
	//printf("got %d as operation\n", op);
	switch(op)
	{
	    case 1:
	    	scanf(" %d %d ", &src, &dest);
		insert_edge(a_graph, src, dest);
		break;
	    case 2:
	    	scanf(" %d %d ", &src, &dest);
		remove_edge(a_graph, src, dest);
		break;
	    case 3:
		print_graph(a_graph);
		break;
	}
    }
    delete_graph(a_graph);

    return 0;
}
