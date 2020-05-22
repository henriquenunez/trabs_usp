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

    printf("size and nops\n");
    //Gets size and number of ops
    scanf("%d %d", &size, &nops);
    printf("size: %d and nops: %d\n", size, nops);

    a_graph = new_graph(a_graph_type, size);

    while(nops--)
    {
	printf("ins edge\n");
	scanf("%d %d", &src, &dest);
	printf("Got edge: %d->%d\n", src, dest);
	if (src < 0 || dest < 0) break;
	insert_edge(a_graph, src, dest);
	print_graph(a_graph);
    }

    printf("osp ocne again\n");
    //getting again number of operations
    scanf("%d", &nops);
    printf("%d operations!\n", nops);

    while(nops--)
    {
	printf("inserti operation 1 ins, 2 del, 3 print\n");
	scanf("%d", &op);
	printf("got %d as operation\n", op);
	switch(op)
	{
	    case 1:
		printf("ins edge\n");
	    	scanf("%d %d", &src, &dest);
		printf("Ins edge: %d->%d\n", src, dest);
		insert_edge(a_graph, src, dest);
		break;
	    case 2:
		printf("rem edge\n");
	    	scanf("%d %d", &src, &dest);
		printf("Rem edge: %d->%d\n", src, dest);
		remove_edge(a_graph, src, dest);
		break;
	    case 3:
		printf("Graph:\n");
		print_graph(a_graph);
		break;
	}
    }
    print_graph(a_graph);
    delete_graph(a_graph);

    return 0;
}
