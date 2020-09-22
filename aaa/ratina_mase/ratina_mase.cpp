#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>

#include <cstdio>
#include <cmath>

#define N_MOVES 4
int moves[4][2] = {
   0,-1, // Up
   1, 0, // Right
   0, 1, // Down
  -1, 0  // Left
};

void print_map(const std::vector<std::vector<int>> &map, int x, int y){
  std::cout << "========="<<std::endl;
  for(int i = 0 ; (unsigned int)i < map.size() ; i++){
    std::cout << "=";
    for(int j = 0 ; (unsigned int)j < map.size() ; j++){
      if(i == x && j == y){
        std::cout << "*";
      }else if(map[i][j] == 1){
        std::cout << "#";
      }else if(i == j && i == map.size()-1){
        std::cout << "!";
      }else if(map[i][j] == 2){
        std::cout << "\033[31;1m.\033[0m";
      }else{
        std::cout << ".";
      }
    }
    std::cout<<"="<<std::endl;
  }
  std::cout << "========="<<std::endl;
  std::cout << "\r\033[9A";
}

void search_path(   int& no_paths,
		    int maze_order,
		    std::vector< std::vector<int> >& maze,
		    std::pair<int, int> location)
{
    //print_map(maze, location.first, location.second);

    if(location.first == maze_order-1 && location.second == maze_order-1)
    {
	no_paths++;
	return;
    }

    int new_x, new_y;

    maze[location.first][location.second] = 2;
    for(int i = 0 ; i < N_MOVES ; i++)
    {
	new_x = location.first + moves[i][0];
	new_y = location.second + moves[i][1];

	if( new_x < (int)maze_order &&
	    new_y < (int)maze_order &&
	    new_x >= 0 &&
	    new_y >= 0 &&
	    maze[new_x][new_y] == 0)
	{
	    search_path(no_paths,
			maze_order,
			maze,
			std::make_pair(new_x, new_y));
	    //Erase wall
	}
    }
    maze[location.first][location.second] = 0;
}

int main()
{
    int temp_c;
    std::cin >> temp_c;

    std::vector<std::vector<int>> labrynth(temp_c);

    for(int i = 0 ; i < temp_c ; i++)
    {
	labrynth[i] = std::vector<int>(temp_c);
    }

    for(int i = 0 ; i < temp_c ; i++)
	for(int j = 0 ; j < temp_c ; j++)
	    std::cin >> labrynth[i][j];

    int no_paths = 0;
    search_path(no_paths, temp_c, labrynth, std::make_pair(0,0));
    std::cout << no_paths << std::endl;
}

