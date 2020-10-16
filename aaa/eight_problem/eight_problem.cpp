#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include <queue>
#include <unordered_set>
#include <sstream>
#include <unistd.h>

#include <cstdio>
#include <cmath>

#define MOVEMENTS 4

int moves[4][2] =
{
    -1,  0, //UP
     0,  1, //RIGHT
     1,  0, //DOWN
     0, -1  //LEFT
};

char charmoves[4] =
{
    'u',
    'r',
    'd',
    'l'
};

int right_ij[9][2] = 
{
    2, 2, //0

    0, 0, //1
    0, 1, //2
    0, 2, //3
    1, 0, //4
    1, 1, //5
    1, 2, //6
    2, 0, //7
    2, 1  //8
};

void int_swap(int *a, int *b)
{
    if(*a != *b)
    {
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
    }
}

class BoardState
{
    private:
    
    int board[3][3];
    int depth;
    int null_x, null_y;
    int heuristic_weight; //Misplaced weight.
    std::string move_string;

    void board_to_arr(int vec[])
    {
    	for (int i = 0 ; i < 9 ; i++)
    	    vec[i] = this->board[i/3][i%3];
    }

    void set_depth(int _depth)
    {
        this->depth = _depth;
    }

    public:

    bool valid;

    BoardState(int init_array[9])
    {
    	//Init board.
    	for (int i = 0 ; i < 9 ; i++)
    	{
    	    if (init_array[i] == 0) //Set null position.
    	    {
    		null_x = i/3; null_y = i%3;
    	    }
    	    board[i/3][i%3] = init_array[i];
    	}

    	heuristic_weight = 0;
        depth = 0;
        move_string = std::string();   
    }

    ~BoardState() {}

    void print_board()
    {
    	if(this->valid)
    	for (int i = 0 ; i < 3 ; i++)
    	{
    	    for (int j = 0 ; j < 3 ; j++)
    	    {
    		std::cout << board[i][j] << " ";
    	    }
    	    std::cout << "\n";
    	}
    	else
    	    std::cout << "Invalid!\n";
    }

    std::string serialize()
    {
        std::stringstream ret("");

        for (int i = 0 ; i < 9 ; i++)
            ret << board[i/3][i%3];

        return ret.str();
    }

    //Checks number of misplaced tiles.
    int check_manhattan()
    {
    	int val;
    	int right_i, right_j;
    	int eheu = 0;

    	//Fill heuristic weight accordingly.
    	for (int i = 0 ; i < 3 ; i++)
            for (int j = 0 ; j < 3 ; j++)
        	{
        	    val = board[i][j];

        	    right_i = right_ij[val][0];
        	    right_j = right_ij[val][1];
        	    
                //std::cout << "val' is: " << val << "(" << right_i << ", " << right_j << ")\n";

        	    //Now, compute difference between right indexes and curr indexes.
        	    eheu += std::abs(right_i - i) + std::abs(right_j - j);
            }

        return eheu;
    }

    /*
    1 2 3
    4 5 7
    0 8 6
    sabemos que i(7) = 2
    sabemos que j(7) = 0

    x x x
    x x x
    7 x x
    mas nosso '7' tem i = 1 e j = 2
    então manhattan('7') = abs(1 - 2) + abs(2 - 0)
    */

    void set_move_string(std::string a)
    {
        move_string = a;
        //std::cout << "Move string is: " << move_string << "\n";
    }

    std::string get_move_string()
    {
        return move_string;
    }

    bool operator< (const BoardState &another) const
    {
        return this->get_loss() > another.get_loss(); 
    }

    int get_loss() const
    {
        return heuristic_weight;
    }

    int calc_loss_func()
    {
	   heuristic_weight = check_manhattan() + depth;
	   return heuristic_weight;
    }

    bool check_solvable()
    {
	   //For this, we can count inversions.
	   int temp_arr[9];
	   board_to_arr(temp_arr);
       int inv = 0;

       for (int i = 0; i < 8 ; ++i)
       {
            for (int j = i+1; j < 9 ; ++j)
            {
                /*
                1 0 0 
                0 0 0 
                0 0 0 
                */
                if (temp_arr[i] != 0 && temp_arr[j] != 0 && temp_arr[i] > temp_arr[j])
                {
                    inv++;
                }
            }
       }

       if (inv % 2 == 0) return true;

	   return false;
    }

    BoardState generate_state(int mov)
    {
    	int temp_board[3][3];
    	int temp_array[9];
    	int new_i = null_x, new_j = null_y;
    	bool valid = true;

    	for (int i = 0 ; i < 3 ; i++)
    	    for (int j = 0 ; j < 3 ; j++)
    		  temp_board[i][j] = this->board[i][j]; //Copying board.

    	//std::cout << "Before change: (" << new_i << ", " << new_j << ")\n";

        //UDLR
    	new_i += moves[mov][0]; new_j += moves[mov][1];

    	//std::cout << "After change: (" << new_i << ", " << new_j << ")\n";

    	if(new_i < 0 || new_i > 2 || new_j < 0 || new_j > 2)
    	    valid = false;

    	if (valid) //Swap positions...
    	    int_swap(&temp_board[null_x][null_y], &temp_board[new_i][new_j]);

    	//Fill temp array;
    	for (int i = 0 ; i < 9 ; i++)
    	    temp_array[i] = temp_board[i/3][i%3];

    	BoardState ret_board = BoardState(temp_array);
        ret_board.set_depth(this->depth + 1);
    	ret_board.valid = valid;
        ret_board.set_move_string(this->get_move_string() + charmoves[mov]);

        ret_board.calc_loss_func();

        //std::cout << "Generated state: " << ret_board.get_move_string() << "Loss function: " << ret_board.calc_loss_func() << "\n";
        //usleep(20000);

    	return ret_board;
    }
};

/*
PODEMOS PENSAR NO GRAFO COMO

INIT_STATE
ABRE 4 POSSIBILIDADES [UP, DOWN, LEFT, RIGHT]

*/

std::string A_star(BoardState init_state)
{
    std::priority_queue<BoardState> next_states;
    std::unordered_set<std::string> visited;

    BoardState curr_state = init_state;

    next_states.push(curr_state);
    visited.insert(curr_state.serialize());

    while(!next_states.empty())
    {
    	//Pop state.
    	curr_state = next_states.top();
    	next_states.pop();

	    //Check if goal.
	    if (curr_state.check_manhattan() == 0)
	    {
    		//std::cout << "Is goal!" << std::endl;

    		return curr_state.get_move_string(); //Returns movement string.
	    }

	    //Generate descendants.
	    for (int i = 0 ; i < 4 ; i++)
        {
            BoardState descendant = curr_state.generate_state(i);
            //TODO skip if visited.
            if (descendant.valid && 
                visited.count(descendant.serialize()) == 0 )
                {
                    visited.insert(descendant.serialize());    
                    next_states.push(descendant);
                }
        }
    }

    return std::string("batata");
}

//Todo check solvable.

void tests()
{
    int arr[9] = {1,2,3,4,5,6,7,8,0};

        BoardState a_board = BoardState(arr);
        std::cout << "Is ok? " << a_board.check_manhattan() << "\n";
        a_board.print_board();
        std::cout << a_board.get_move_string() << "\n";

        //Calling up three times.
        BoardState another_board = a_board.generate_state(0);
        std::cout << another_board.serialize() << "\n";
        another_board.print_board();

        another_board = another_board.generate_state(0);
        std::cout << another_board.serialize() << "\n";
        another_board.print_board();

        another_board = another_board.generate_state(0);
        if (!another_board.valid) std::cout << "Invalid board\n";
        another_board.print_board();

        //BoardState another_board = a_board.generate_state(0).generate_state(0);
        //another_board.print_board();
}

int main()
{
    int arr[9];
    char temp;
    char temps[2] = {0};
    int times;

//#define DEB

#ifdef DEB
    tests();
#endif

#ifndef DEB

    std::cin >> times;

    while(times--)
    {
    	for (int i = 0 ; i < 9 ; i++)
    	{
    	    std::cin >> temp;
    	    //std::cout << "Got: " << temp << "\n";
    	    
            temps[0] = temp;
    	    if (temp == 'x')
    	    {
    		//std::cout << "XXXXX\n";
    		arr[i] = 0;
    	    }
    	    else
    		arr[i] = atoi(temps);
    	}

        BoardState init_state(arr);
        //init_state.print_board();
        if (!init_state.check_solvable())
        {
            std::cout << "unsolvable\n";
            if (times > 0)
                std::cout << "\n";
            continue;
        }

        std::string batata = A_star(init_state);
        //reverse(batata.begin(), batata.end());

        std::cout << batata << "\n";
        if (times > 0)
            std::cout << "\n";
    }

#endif
}

