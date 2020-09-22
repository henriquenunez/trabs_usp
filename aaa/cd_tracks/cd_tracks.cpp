#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>

#include <cstdio>
#include <cmath>
#include <cstdio>
#include <unistd.h>
#include <deque>

std::vector<int> sel_best_vector(std::vector<int> a, std::vector<int> b, int goal)
{
    int a_sum = 0, b_sum = 0;
    for (int i : a)
	a_sum+=i;
    for (int i : b)
	b_sum+=i;

    a_sum = goal - a_sum;
    b_sum = goal - b_sum;

    if (a_sum < 0) return b;
    if (b_sum < 0) return a;
    if (a_sum < b_sum) return a;
    else return b;
}

void fit_tracks(int& best_time,
		std::vector<int> tracks,
		int goal,
		std::vector<int>& solution_tracks,
		std::vector<int> curr_list,
		int curr_time,
		int it)
{
    /*std::cout << "Curr time: " << curr_time << "goal " << goal << std::endl;

    for(int b : curr_list)
    {
	std::cout << b << " ";
    }*/

    if(curr_time > goal) return;

//    std::cout << std::endl;

    //Check if we achieved a better solution.
    if (curr_time > best_time)
    {
	solution_tracks.clear();
	//std::cout << "Good solution:\n";
	for (int a : curr_list)
	{
	    solution_tracks.push_back(a);
	    //std::cout << a << std::endl;
	}

	best_time = curr_time;
    }

    //Base case
    if ((unsigned int)it >= tracks.size()) //If past end.
	return; //Whether sum is greater than it should be.


    //sleep(1);
    //Two posibilities: either include or not the curr element.

    std::vector<int> keep(curr_list);
    keep.push_back(tracks[it]); //Inserting current element.
    fit_tracks(best_time,
		tracks,
		goal,
		solution_tracks,
		keep,
		curr_time + tracks[it],
		it+1);

    std::vector<int> skip(curr_list);
    fit_tracks(best_time,
		tracks,
		goal,
		solution_tracks,
		skip,
		curr_time,
		it+1);
}

void sort_tracks(int tape_len, int track_n)
{
    std::vector<int> tracks;
    int temp;

    for (int i = 0 ; i < track_n ; i++)
    {
	std::cin >> temp;
	tracks.push_back(temp);
    }

    //std::vector<int>::iterator curr_elem = tracks.begin();
    int curr_elem = 0;
    std::vector<int> a_vec; //Empty vec.
    std::vector<int> solution_v;
    int best_time = 0;


    fit_tracks(best_time, tracks, tape_len, solution_v, a_vec, 0, curr_elem);

    for (int a : solution_v)
    {
	std::cout << a << " ";
    }
    std::cout << "sum:" << best_time << std::endl;
}

int main()
{
    int temp_c, temp_s;
    while(scanf("%d %d", &temp_c, &temp_s) == 2)
    {
	sort_tracks(temp_c, temp_s);
    }
}

