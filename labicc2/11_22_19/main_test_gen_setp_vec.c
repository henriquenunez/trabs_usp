#include <stdio.h>
#include <stdlib.h>

#include "shell_sort_predef.h"

int main()
{
	int vec_size, steps, *vec;
	scanf("%d", &vec_size);
	gen_step_vector(vec_size, &steps);

	return 0;
}
