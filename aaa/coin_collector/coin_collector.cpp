/* The thing we need to do is that, for each coin,
 * beginnng with the larger ones, we need to check whether
 * there is a sum that is greater to that one. If so, we cannot
 * match that set of coins in a single withdrawal.
 */

#include <vector>
#include <iostream>
#include <algorithm>

int solve(std::vector<int> coin_types, int curr_index, int curr_sum)
{
    if (curr_index + 1 < coin_types.size())
    {

	if(curr_sum + coin_types[curr_index] >= coin_types[curr_index+1])
	{
	    return solve(coin_types, curr_index+1, curr_sum);
	}
	else
	{
	    return 1 + solve(coin_types,
				curr_index+1, curr_sum +
				coin_types[curr_index]);
	}
    }

    return 1;
}

int coin_collector() // "Main" function of the problem.
{
    std::vector<int> country_coins, max_withdrawal;
    int n, temp;
    std::cin >> n;
    for(int i = 0 ; i < n ; i++)
    {
	std::cin >> temp;
	#ifdef DEBUG
	    std::cout << "Got:" << temp << std::endl;
	#endif
	country_coins.push_back(temp);
    }

    //Since input is sorted, walk on vec.
    //Begins with lowest number;
/*    for(std::vector<int>::iterator it = country_coins.begin();
	it != country_coins.end();
	++it)
    {
	//int curr_sum = 0, curr_count = 0;

	#ifdef DEBUG
	    std::cout << "Trying:" << *it << std::endl;
	#endif

    }
*/
    //1 for first and last
    return 1 + solve(country_coins, 1, 1);
    //Get the highest value;
    /*std::vector<int>::iterator max_dif_coin_n_it;
    max_dif_coin_n_it = std::max_element(max_withdrawal.begin(),
					max_withdrawal.end());

    return *max_dif_coin_n_it;*/

}

int main()
{
    int times;
    std::cin >> times;
    #ifdef DEBUG
	std::cout << "Times: " << times << "\n";
    #endif
    while(times--) std::cout << coin_collector() << std::endl;
    return 0;
}



