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

const int moves[8][4]{
  {-1,0,0,0},
  {1,0,0,0},
  {0,-1,0,0},
  {0,1,0,0},
  {0,0,-1,0},
  {0,0,1,0},
  {0,0,0,-1},
  {0,0,0,1}
};

struct LockState
{
    int lock[4];
    int depth;
    int eheu;
};

void calc_eheu(LockState &a_state, int state[4])
{
    int count = 0;

    for (int i = 0 ; i < 4 ; i++)
    {
        int small = std::min(a_state.lock[i], state[i]);
        int large = std::max(a_state.lock[i], state[i]);
        int dif1 = large-small;
        int dif2 = small+10 - large;
        count += std::min(dif1,dif2);
    }

    a_state.eheu = count;
}

bool operator< (const LockState &a, const LockState &b)
{
    return (a.depth + a.eheu) > (b.depth + b.eheu);
}

bool check_goal(LockState a_state, int state[4])
{
    for (int i = 0 ; i < 4 ; i++)
	   if (a_state.lock[i] != state[i])
	       return false;
    return true;
}

bool check_valid(LockState a_state, int forbidden[10][10][10][10])
{
    int* lock = a_state.lock;
    if (forbidden[lock[0]][lock[1]][lock[2]][lock[3]] == 1)
        return false;
    return true;
}

LockState generate_state(LockState a_state, int change)
{
    LockState ret_lockstate;

    memcpy(ret_lockstate.lock, a_state.lock, 4 * sizeof(int));
/*
    int sum;
    if (change % 2 == 0) sum = -1;
    else sum = 1;

    ret_lockstate.lock[change / 2] =
        (a_state.lock[change / 2] + sum + 10) % 10;
*/
    for (int i = 0; i < 4; ++i)
    {
        int temp = ret_lockstate.lock[i] + moves[change][i];
        if (temp < 0) temp = 9;
        if (temp > 9) temp = 0;
        ret_lockstate.lock[i] = temp;
    }
/*
    ret_lockstate.lock[0] += moves[i][0];
    ret_lockstate.lock[1] += moves[i][1];
    ret_lockstate.lock[2] += moves[i][2];
    ret_lockstate.lock[3] += moves[i][3];
*/
    ret_lockstate.depth = a_state.depth + 1;

    return ret_lockstate;
}

int A_star_search(LockState init_state, int final_state[4], int forbidden[10][10][10][10])
{
    std::priority_queue<LockState> open_settings;
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
    	int* temp_lock = curr_state.lock;
    	closed_nodes[temp_lock[0]][temp_lock[1]][temp_lock[2]][temp_lock[3]] = 1;

    	if (check_goal(curr_state, final_state))
    	    return curr_state.depth;

    	//Generate all states based on this guy.
    	for (int i = 0 ; i < 8 ; i++)
    	{
    	    LockState gen_state = generate_state(curr_state, i);
            calc_eheu(gen_state, final_state);
    	    temp_lock = gen_state.lock;

    	    if (check_valid(gen_state, forbidden))
        		if (closed_nodes[temp_lock[0]]
        				        [temp_lock[1]]
        				        [temp_lock[2]]
        				        [temp_lock[3]] == 0)
                {
                    open_settings.push(gen_state);
                }
        		    
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

    int goal[4];//= {0, 0, 9, 9};

    while(tests--)
    {
        int forbidden_states[10][10][10][10] = {0};

    	//Init state
    	std::cin >> a >> b >> c >> d;
        
        LockState a_given_state;
        a_given_state.lock[0] = a;
        a_given_state.lock[1] = b;
        a_given_state.lock[2] = c;
        a_given_state.lock[3] = d;
        a_given_state.depth = 0;

    	std::cin >> a >> b >> c >> d;
    	goal[0] = a;
    	goal[1] = b;
    	goal[2] = c;
    	goal[3] = d;

    	std::cin >> forbes;

    	while(forbes--) //Adding forbidden states.
    	{
    		std::cin >> a >> b >> c >> d;
    		forbidden_states[a][b][c][d] = 1;
    	}

    	std::cout << A_star_search(a_given_state, goal, forbidden_states) << std::endl;
    }
}

