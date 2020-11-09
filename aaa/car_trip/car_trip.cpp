#include <cstdio>
#include <cstring>
#include <cstddef>

#include <vector>

#define MAX_WEIGHT 200
#define MAX_SUITCS 20

int max_w[MAX_SUITCS +1][MAX_WEIGHT +1];

void print_mat(int max_w[MAX_SUITCS +1][MAX_WEIGHT +1], int suitcs, int weight)
{
    for (int i = 0 ; i <= suitcs ; i++)
    {
        for (int j = 0 ; j <= weight ; j++)
        {
            printf("[%d] ", max_w[i][j]);
        }
        printf("\n");
    }
    getchar();
}

// WARNING: PASS INDEX AS ONE MORE.
int wssp(int index, int max_weight, std::vector<int> vec, int max_w[MAX_SUITCS +1][MAX_WEIGHT +1])
{
    //printf("Received %d and %d\n", index, max_weight);
    //print_mat(max_w);
    //print_mat(max_w, 5, 20);
    
    if (index == 0 || max_weight == 0)
        return 0;
    
    if (max_w[index][max_weight] != -1)
        return max_w[index][max_weight];
    
    if(vec[index-1] > max_weight)
        max_w[index][max_weight] = wssp(index-1, max_weight, vec, max_w);
    else
    {
        //Fill matrix.
        max_w[index][max_weight] =
            std::max(vec[index-1] + wssp(index-1,
                                         max_weight-vec[index-1],
                                         vec,
                                         max_w),
                     wssp(index-1,
                          max_weight,
                          vec,
                          max_w));
        //printf("wssp: %d\n", max_w[index][max_weight]);
    }
    
    return max_w[index][max_weight];
}

bool car_trip()
{
    memset(max_w, -1, sizeof max_w);
    
    size_t l_len;
    char *line;
    
    int total = 0;
    int index = 0;
    
    std::vector<int> nums;
    getline(&line, &l_len, stdin);
    
    char *num_str = strtok(line, " ");
    
    while(num_str != NULL)
    {
        int temp;
        sscanf(num_str, "%d", &temp);
        
        //printf("Got: {%s}\n", num_str);
        
        total += temp;
        nums.push_back(temp);
        
        index++;
        
        num_str = strtok(NULL, " ");
    }
    
    if (total % 2 != 0)
        return false;
    
    int ret_wssp = wssp(index, total/2, nums, max_w);
    //printf(">> %d : %d\n", total/2, ret_wssp);
    
    if (ret_wssp == (total/2))
        return true;
    
    return false;
}

int main()
{
    int times;
    
    scanf("%d ", &times);
    
    while (times--)
        if(car_trip())
        printf("YES\n");
    else
        printf("NO\n");
    
}
