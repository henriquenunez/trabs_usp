#include <cstdio>
#include <cstdlib>

#include <unistd.h>

struct positions
{
    int shorter;
    int taller;
};

//Start and end are inclusive -> [a,b].
struct positions find_height_index(int* height_vec, int start, int end, int thresh)
{
    int l_index = start; //Left
    int r_index = end; //Right
    int m_index; //Mid index
    struct positions ret
    {
        .shorter = -1,
        .taller = -1
    };
    
    //printf("Thresh: %d\n", thresh);
    
    while (true)
    {
        m_index = (l_index + r_index)/2;
        
        //printf("l: %d m: %d r: %d\n", l_index, m_index, r_index);
        if (m_index == l_index || m_index == r_index)
            break;
        
        if (height_vec[m_index] <= thresh)
        {
            //printf("Probing %d, L index: %d\n", height_vec[m_index], m_index);
            l_index = m_index;
            continue;
        }
        
        if (height_vec[m_index] > thresh)
        {
            //printf("Probing %d, R index: %d\n", height_vec[m_index], m_index);
            r_index = m_index;
            continue;
        }
    }
    
    //Will return index of the value immediately g.t. thresh.
    
    for(int i = m_index ; i <= end ; i++)
        if (height_vec[i] > thresh)
    {
        ret.taller = height_vec[i];
        break;
    }
    
    for(int i = m_index ; i >= start ; i--)
        if (height_vec[i] < thresh)
    {
        ret.shorter = height_vec[i];
        break;
    }
    
    return ret;
}

int main()
{
    int macacas;
    int *macacas_height;
    int luchu;
    int temp1;
    
    scanf("%d", &macacas);
    macacas_height = (int*) malloc(sizeof(int) * macacas);
    for (int i = 0 ; i < macacas ; i++)
        scanf("%d", macacas_height+i);
    
    scanf("%d", &luchu);
    for (int i = 0 ; i < luchu ; i++)
    {
        scanf("%d", &temp1); //Luchu's height.
        struct positions data;
        
        data = find_height_index(macacas_height, 0, macacas-1, temp1);
        
        if (data.shorter != -1)
        {
            printf("%d ", data.shorter);
        }
        else
        {
            printf("X ");
        }
        
        if (data.taller != -1)
        {
            printf("%d\n", data.taller);
        }
        else
        {
            printf("X\n");
        }
        
    }
    
}
