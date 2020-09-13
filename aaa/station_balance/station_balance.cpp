#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>

#include <cstdio>
#include <cmath>

void centrifugues(int c, int s)
{
    std::vector<int> specimen_masses;
    std::vector<std::pair<int, int> > chambers;

    int temp;

    for(int i = 0 ; i < s ; i++)
    {
	std::cin >> temp;
	specimen_masses.push_back(temp);
    }

    for(int i = 0 ; i < (2*c) - s ; i++)
    {
	specimen_masses.push_back(0);
    }

    std::sort(specimen_masses.begin(), specimen_masses.end());

    double average, imbalance=0; //Average of mass per chamber.

    //Two iterators: one for beginning, and one for reversed beginning.
    std::vector<int>::iterator it_begin = specimen_masses.begin();
    std::vector<int>::reverse_iterator rev_it_begin = specimen_masses.rbegin();

    std::vector<int>::iterator it_end = specimen_masses.end();

    average = (double)std::accumulate(it_begin, it_end, 0)/(double)s;

    //std::cout << average << std::endl;
    for(int j = 0 ; j < c ; j++) //Form pairs;
    {
	chambers.push_back(std::make_pair(*it_begin, *rev_it_begin));
	++it_begin;
	++rev_it_begin;
    }

    //Print my stuff.

    int chamb_num = 0;
    for(std::pair<int, int> specs : chambers)
    {
	std::cout << "\n " << chamb_num++ << ":";

	if (specs.first > 0)
	    std::cout << " " << specs.first;
	if (specs.second > 0)
	    std::cout << " " << specs.second;

	imbalance += std::fabs((specs.first+specs.second) - average);
    }
    printf("\nIMABALANCE = %.5lf\n\n", imbalance);

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

