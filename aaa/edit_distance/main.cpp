#include <cstdio>
#include <algorithm>

#include <iostream>

void __allocate_matrix(int*** mat, int n, int m)
{
    *mat = (int**) malloc(n * sizeof(int*));

    for (int i = 0 ; i < n ; i++)
        (*mat)[i] = (int*) malloc(n * sizeof(int));
}

void __free_mat(int** mat, int n)
{
    for (int i = 0 ; i < n ; i++)
        free(mat[i]);

    free(mat);
}

#define CALC_DIFF(a) (a - 'a' + 1)

int edit(char* v1, int n1, char* v2, int n2) //Count editions on vec.
{
    int** memo;

    __allocate_matrix(&memo, n1+1, n2+1);
    //n1 rows, n2 cols.

    for (int i = 0 ; i <= n1 ; i++)
    {
        for (int j = 0 ; j <= n2 ; j++)
        {
            //Initialize.
            if (i==0)
            {
                memo[i][j] = CALC_DIFF(v2[j]);
                continue;
            }
            if (j==0)
            {
                memo[i][j] = CALC_DIFF(v1[i]);
                continue;
            }

            if (v1[i-1] == v2[j-1]) memo[i][j] = memo[i-1][j-1];
            else
                memo[i][j] = std::min(memo[i-1][j], // Remove from.
                                      memo[i][j-1]);
        }
    }

    int ret = memo[n1][n2];

    __free_mat(memo, n1+1);

    return ret;
}

int main()
{
    int times;
    std::cin >> times;

    int max_n;
    int* v1;
    int* v2;

    for (int i = 1 ; i <= times ; i++)
    {
        scanf("%d", &max_n);
        v1 = (int*) malloc(max_n * sizeof(int));
        v2 = (int*) malloc(max_n * sizeof(int));

        for (int j = 0 ; j < max_n ; j++)
        {
            scanf("%d", v1+j);
        }

        for (int j = 0 ; j < max_n ; j++)
        {
            scanf("%d", v2+j);
        }
        printf("Case %d: %d\n", i , edit(v1, max_n, v2, max_n));

        free(v1);
        free(v2);
    }
}

