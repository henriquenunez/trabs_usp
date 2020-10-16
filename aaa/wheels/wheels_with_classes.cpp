#include <iostream>
#include <unordered_set>
#include <queue>
#include <utility>
#include <sstream>
#include <algorithm>

#include <stdlib.h>
#include <cstring>
/*
|----|----|----|----|
|    |    |    |    |
| 1  | 2  | 3  | 4  |
|    |    |    |    |
|----|----|----|----|
*/

#define mod(a, b) (((a)%(b) < 0) ? (((a)%(b)) + (b)) : ((a)%(b)))

class LockState
{
    public:
    int lock[4];
    int final_state[4];
    int depth;
    bool valid;
    //std::unordered_set<std::string> forbidden;
    int forbidden_mat[10][10][10][10] = {0};

    LockState(int _init_state[], int _final_state[])
    {
	memcpy(lock, _init_state, 4 * sizeof(int));
	memcpy(final_state, _final_state, 4 * sizeof(int));
	depth = 0;
    }

    //Adds prohibited state.
    void add_forbidden(int f_state[])
    {
	//forbidden.insert(serialize_state(f_state));
	forbidden_mat[f_state[0]][f_state[1]][f_state[2]][f_state[3]] = 1;
    }

    /*
    -
    0	2   4	6

    1	3   5	8
    + */
    LockState generate_state(int change)
    {
	LockState new_lockstate = *this;

	int sum;
	if (change % 2 == 0) sum = -1;
	else sum = 1;

	new_lockstate.lock[change / 2] =
	    (new_lockstate.lock[change / 2] + sum + 10) % 10;
	new_lockstate.set_depth(this->depth + 1);

	return new_lockstate;
    }

    std::string serialize_curr_state()
    {
	return serialize_state(this->lock);
    }

    static std::string serialize_state(int state[])
    {
	std::stringstream ret("");

	for (int i = 0 ; i < 4 ; i++)
	    ret << state[i];

	return ret.str();
    }

    void set_depth(int _depth)
    {
	depth = _depth;
    }

    int calculate_heuristic() const
    {
	int count = 0;

	for (int i = 0 ; i < 4 ; i++)
	{
	    int small = std::min(lock[i], final_state[i]);
	    int large = std::max(lock[i], final_state[i]);
	    int dif1 = large-small;
	    int dif2 = small+10 - large;
	    count += std::min(dif1,dif2);
	}
	    //count += mod((lock[i] - final_state[i]), 10);

	return count;
    }

    int* get_lock()
    {
	return lock;
    }

    bool operator< (const LockState &oth) const
    {
	return (this->calculate_heuristic() + this->depth) >
	(oth.calculate_heuristic() + oth.get_depth());
    }

    int get_depth() const
    {
	return depth;
    }

    bool check_goal()
    {
	for (int i = 0 ; i < 4 ; i++)
	    if (lock[i] != final_state[i])
		return false;
	return true;
    }

    bool check_valid()
    {
	if(forbidden_mat[lock[0]][lock[1]][lock[2]][lock[3]] == 1)
	    return false;
	return true;
    }
};

int A_star_search(LockState init_state)
{
    std::priority_queue<LockState> open_settings;
    //std::unordered_set<std::string> closed_settings;
    int closed_nodes[10][10][10][10] = {0};

    //Init priority queue.
    LockState curr_state = init_state;
    open_settings.push(init_state);

    while (!open_settings.empty())
    {
	//Pop from queue.
	curr_state = open_settings.top();
	open_settings.pop();

	//Add to visited.
	int* temp_lock = curr_state.get_lock();
	closed_nodes[temp_lock[0]][temp_lock[1]][temp_lock[2]][temp_lock[3]] =1;

	if (curr_state.check_goal())
	    return curr_state.get_depth();

	//Generate all states based on this guy.
	for (int i = 0 ; i < 8 ; i++)
	{
	    LockState gen_state = curr_state.generate_state(i);
	    temp_lock = gen_state.get_lock();

	    if (gen_state.check_valid())
		if (closed_nodes[temp_lock[0]]
				[temp_lock[1]]
				[temp_lock[2]]
				[temp_lock[3]] == 0)
		    open_settings.push(gen_state);
	}
    }


    return -1; //In case no path found.
}

int main()
{
    int tests;
    int forbes;
    int a, b, c, d;

    std::cin >> tests;

    int temp_set_1[4];//= {0, 0, 9, 9};
    int temp_set_2[4];//= {0, 1, 1, 1};

    while(tests--)
    {
	//Init state
	std::cin >> a >> b >> c >> d;
	temp_set_1[0] = a;
	temp_set_1[1] = b;
	temp_set_1[2] = c;
	temp_set_1[3] = d;

	std::cin >> a >> b >> c >> d;
	temp_set_2[0] = a;
	temp_set_2[1] = b;
	temp_set_2[2] = c;
	temp_set_2[3] = d;

	LockState a_given_state = LockState(temp_set_1, temp_set_2);

	std::cin >> forbes;

	while(forbes--) //Adding forbidden states.
	{
		std::cin >> a >> b >> c >> d;
		temp_set_1[0] = a;
		temp_set_1[1] = b;
		temp_set_1[2] = c;
		temp_set_1[3] = d;

		a_given_state.add_forbidden(temp_set_1);
	}

	std::cout << A_star_search(a_given_state) << std::endl;
    }
}

