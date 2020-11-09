#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include <cstdio>
#include <cstring>

int merge(int vec[], int lower, int mid, int upper)
{
    const int left_size  = mid - lower + 1;
    const int right_size = upper - mid;
    
    int *left_vec, *right_vec;
    int inversions = 0;
    
    left_vec  = (int*) malloc(sizeof(int) * (mid - lower + 1));
    right_vec = (int*) malloc(sizeof(int) * (upper - mid));
    
    for (int i = 0 ; i < left_size ; i++)
        left_vec[i] = vec[i + lower];
    
    for (int i = 0 ; i < right_size ; i++)
        right_vec[i] = vec[i + mid + 1];
    
    int i, j, k;
    i = j = 0;
    
    for(k = lower ; i < left_size && j < right_size ; k++)
    {
        if (left_vec[i] <= right_vec[j])
        {
            vec[k] = left_vec[i++];
        }
        else
        {
            //Count inversions here
            inversions += left_size - i;
            vec[k] = right_vec[j++];
        }
    }
    
    while(i < left_size) vec[k++] = left_vec[i++];
    while(j < right_size) vec[k++] = right_vec[j++];
    
    free(left_vec);
    free(right_vec);
    
    return inversions;
}

int count_inversions(int vec[], int lower, int upper)
{
    int invs = 0;
    int mid = (upper + lower)/2;
    
    //std::cout << "L:" << lower << " U:" << upper << "\n";
    
    if (lower < upper)
    {
        invs += count_inversions(vec, lower, mid);
        invs += count_inversions(vec, mid + 1, upper);
        invs += merge(vec, lower, mid, upper);
    }
    
    return invs;
}

int main()
{
    int times;
    
    //std::cin >> times;
    
    //char* input_line;
    //char* temp_num;
    //size_t line_size;
    
    scanf("%d ", &times);
    
    //std::string temp_string, line;
    
    int* temp_vals;
    
    while (times--)
    {
        //std::cout << "Times: " << times << "\n";
        
        //std::getline(std::cin, line);
        //getline(&input_line, &line_size, stdin);
        
        std::vector<std::string> vals;
        //std::stringstream ss(line);
        int val_counter = 0;
        
        //printf("Got: %s", input_line);
        
        scanf("%d", &val_counter);
        
        //temp_num = strtok(input_line, " ");
        /*
        while(true)
        {
            if (temp_num == NULL)
                break;
            
            //printf("Splitted: %s\n", temp_num);
            vals.push_back(std::string(temp_num));
            val_counter++;
            
            temp_num = strtok(NULL, " \n");
        }
        */
        temp_vals = (int*) malloc(sizeof(int) * val_counter);
        
        for (int i = 0 ; i < val_counter; i++)
        {
            scanf("%d", temp_vals+i);
            //std::cout << temp_vals[i] << " ";
        }
        //std::cout << "\n";
        printf("%d\n", count_inversions(temp_vals, 0, val_counter-1));
        /*
        for (int i = 0 ; i < val_counter; i++)
        {
            std::cout << temp_vals[i] << " ";
        }*/
        
        //std::cout << "\n";
        
        free(temp_vals);
    }
}