#include <iostream>

#include <cstdlib>
#include <cstring>

int coins()
{
    int value, coin_n, *coins;
    unsigned int *required_coins;
    
    std::cin >> value >> coin_n;
    
    coins = (int*) malloc(sizeof(int) * coin_n);
    required_coins = (unsigned int*) malloc(sizeof(unsigned int) * value+1);
    
    required_coins[0] = 0;
    //Fills with largest uint possible.
    memset(required_coins+1, -1, sizeof(unsigned int) * value);
    
    for(int i = 0 ; i < coin_n ; i++)
        scanf("%d", coins+i);
    
    for(int i = 1 ; i <= value ; i++)
    {
        for(int j = 0 ; j < coin_n ; j++)
        {
            int coin_value = coins[j];
            
            if(i >= coin_value)
            {
                int new_amount = i - coin_value;
                required_coins[i] = 
                    (required_coins[new_amount]+1) < required_coins[i] ? 
                    (required_coins[new_amount]+1) : required_coins[i];
            }
        }
    }
    
    return required_coins[value];
}

int main()
{
    int times;
    std::cin >> times;
    
    while(times--)
        printf("%d\n", coins());
}