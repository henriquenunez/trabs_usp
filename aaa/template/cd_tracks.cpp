#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>

#include <cstdio>
#include <cmath>

void sort_tracks()
{

    }

int main()
{
    int temp_c, temp_s, set_count=0;
    while(scanf("%d %d", &temp_c, &temp_s) == 2)
    {
	std::cout << "Set #" << set_count++;
	centrifugues(temp_c, temp_s);
    }
}

