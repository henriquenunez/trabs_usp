#include <cstdio>
#include <algorithm>

#include <iostream>
#include <cstring>

void __allocate_matrix(int*** mat, int n, int m)
{
    *mat = (int**) malloc(n * sizeof(int*));

    for (int i = 0 ; i < n ; i++)
        (*mat)[i] = (int*) calloc(m, sizeof(int));
}

void __free_mat(int** mat, int n)
{
    for (int i = 0 ; i < n ; i++)
        free(mat[i]);

    free(mat);
}

void print_mat(int** mat, int row, int col)
{
    for (int i = 0 ; i < row ; i++)
    {
        for (int j = 0 ; j < col ; j++)
        {
            printf("%4d ", mat[i][j]);
        }
        printf("\n");
    }
}

#define ORD(a) (a - 96)

int edit(char* v1, int n1, char* v2, int n2) //Count editions on vec.
{
    int** memo;

    __allocate_matrix(&memo, n1+1, n2+1);
    //n1 rows, n2 cols.

    memo[0][0] = 0;

    for (int i = 0 ; i <= n1 ; i++)
    {
        for (int j = 0 ; j <= n2 ; j++)
        {

            if (i == 0 && j == 0) continue;

            if (j > 0 && i > 0 && v1[i-1] == v2[j-1])
            {
                memo[i][j] = memo[i-1][j-1];
            }
            else
            if (i==0)
            {
                memo[i][j] = memo[i][j-1] + ORD(v2[j-1]);
            }
            else
            if (j==0)
            {
                memo[i][j] = memo[i-1][j] + ORD(v1[i-1]);
            }
            else
            {
                memo[i][j] = std::min(memo[i-1][j] + ORD(v1[i-1]),
                                      std::min(memo[i][j-1] + ORD(v2[j-1]),
                                               memo[i-1][j-1] + std::abs(v1[i-1] - v2[j-1])
                                               )
                                      );
            }

            //print_mat(memo, n1+1, n2+1);
        }
    }

    int ret = memo[n1-1][n2-1];

    __free_mat(memo, n1+1);

    return ret;
}

int main()
{
    char *v1 = NULL, *v2 = NULL;
    size_t l1 = 0, l2 = 0;

    //getline(&v1, &l1, stdin);
    //getline(&v2, &l2, stdin);

    scanf("%ms", &v1);
    scanf("%ms", &v2);

    //printf("Got: %s\n", v1);
    //printf("Got: %s\n", v2);

    l1= strlen(v1)+1 ;
    l2= strlen(v2)+1 ;

    printf("%d\n", edit(v1, l1, v2, l2));

    free(v1);
    free(v2);

    return 0;
}

