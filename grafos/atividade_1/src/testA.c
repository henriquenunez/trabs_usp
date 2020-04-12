#include <stdio.h>
#include "graph.h"

int main()
{
    GRAPH *a_graph;
    graph_type a_graph_type = 0;
    int a;
    int size;

    printf("Insert type:\n1 for adj matrix\n2 for adj list\n");
    scanf("%d", &a);
    if (a == 1) a_graph_type |= ADJ_MATRIX;
    else a_graph_type |= ADJ_LIST;

    printf("Insert size here\n");
    scanf("%d", &size);

    a_graph = new_graph(a_graph_type, size);
    print_graph(a_graph);

    int src, dest;
    while(1)
    {
	printf("Insert from to:\n");
	scanf("%d %d", &src, &dest);
	if (src < 0 || dest < 0) break;
	insert_edge(a_graph, src, dest);
	print_graph(a_graph);
    }
    //insert_edge()
    delete_graph(a_graph);

    return 0;
}
