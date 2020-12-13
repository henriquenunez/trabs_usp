#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int common = 100;

void* func(void* threadid)
{
    int id = *(int*)threadid;
    printf("A %ld\n", id);
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    int n_threads = 2;
    if (argc > 1)
	n_threads = atoi(argv[1]);

    pthread_t* th_ids = malloc(sizeof(pthread_t) * n_threads);

    for (int i = 0 ; i < n_threads ; i++)
	pthread_create(th_ids+i, NULL, func, &i);

    for (int i = 0 ; i < n_threads ; i++)
	pthread_join(th_ids[i], NULL);

    free(th_ids);
}

