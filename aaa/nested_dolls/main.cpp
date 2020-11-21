#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#include <cstdio>
#include <cstdlib>
#include <cstring>

//<Width, height> pair.
typedef std::pair<int, int> Doll;

/*typedef struct _dolls
{
    int w; 0
    int h; 1
} Doll;
*/

typedef std::vector<Doll> DollVec;

//10 20 30 40 40
//15 15 30 40 50

//Checks whether a fits in b.
//#define fits(a, b) ((std::get<0>(a) < std::get<0>(b) && std::get<1>(a) < std::get<1>(b)) ? true : false)
#define fits(a, b) !((std::get<1>(a) < std::get<1>(b)) ? true : false)
//#define fits(a, b) ((a.h < b.h) ? true : false)

void __gen_in_sol_vec(int ***vec_ref, int n)
{
    *vec_ref = (int**) malloc(n * sizeof(int*));

    for (int i = 0 ; i < n ; i++)
    {
	(*vec_ref)[i] = (int*) calloc(n, sizeof(int));
	(*vec_ref)[i][i] = 1;
    }
}

void __free_in_sol_vec(int ***vec_ref, int n)
{
    for (int i = 0 ; i < n ; i++)
	free((*vec_ref)[i]);
    free(*vec_ref);
    *vec_ref = NULL;
}

void __print_sol_vec(int **vec_ref, int n)
{
    for (int  i = 0 ; i < n ; i++)
    {
	for (int j = 0 ; j < n ; j++)
	{
	    printf(" %d", vec_ref[j][i]);
	}

	printf("\n");
    }
}

int __remove_elems_lis(DollVec &vec)
{
    int num_of_elems = vec.size();

    int *lis_sol_vec; //Vector of actual solutions.
    int **is_in_sol_vec;

    __gen_in_sol_vec(&is_in_sol_vec, num_of_elems);

    lis_sol_vec = (int*) calloc(num_of_elems, sizeof(int));
    lis_sol_vec[0] = 1; //Base case.

    int best_sol_index = 0;

    for (int i = 1 ; i < num_of_elems ; i++) //For each element on array.
    {
	lis_sol_vec[i] = 1;
	//if (delete_in_vec[i] == 1) continue;

	/*  Test whether the subsequence
	    from this position to curr.
	*/
	//printf("Testing doll: %d:%d\n", std::get<0>(vec[i]), std::get<1>(vec[i]));

	//int winning_index = -1;

	for (int j = 0 ; j < i ; j++)
	{
	    //if (delete_in_vec[j] == 1) continue;

	    if ( fits(vec[j], vec[i]) )
	    {
		/*printf("%d:%d fits in %d:%d\n",
		    std::get<0>(vec[j]), std::get<1>(vec[j]),
		    std::get<0>(vec[i]), std::get<1>(vec[i]));*/

		if (lis_sol_vec[j] + 1 > lis_sol_vec[i])
		{
		    lis_sol_vec[i] = lis_sol_vec[j] + 1;

		    //winning_index = j; //So we can copy solution.
		}
	    }
	    /*else
		printf("%d:%d does not fit in %d:%d\n",
		    std::get<0>(vec[j]), std::get<1>(vec[j]),
		    std::get<0>(vec[i]), std::get<1>(vec[i]));*/
	}

	//OTIMIZAÇÕES - PAI TA ON*/
	/*if (winning_index > -1)
	{
	    //Copy which elements are in solution
	    memcpy( is_in_sol_vec[i],
		    is_in_sol_vec[winning_index], num_of_elems * sizeof(int));

	    is_in_sol_vec[i][i] = 1;
	}*/

	if (lis_sol_vec[i] > lis_sol_vec[best_sol_index])
	    best_sol_index = i;
    }

/*
    //__print_sol_vec(is_in_sol_vec, num_of_elems);

    int ret = 0; //return value is the number of deleted.

    //printf("Best solution index: %d, value %d\n", best_sol_index, ret);

    //Removing entries from doll vector.
    for (int i = 0 ; i < num_of_elems ; i++)
    {
	//printf("Removing at index %d\n", i);
	if (is_in_sol_vec[best_sol_index][i] > 0)
	{
	    //printf("Erasing %d %d!\n", best_sol_index, i);
	    vec.erase(vec.begin() + i);
	    //delete_in_vec[i] = 1;
	    ret++;
	}
    }
*/

    int ret = lis_sol_vec[best_sol_index];

    //Freeing stuff.
    free(lis_sol_vec);
    __free_in_sol_vec(&is_in_sol_vec, num_of_elems);

    return ret;
}

//Longest Increasing Subsequence.
int LIS(DollVec &vec)
{
    /*
    int counter = 0;
    int deleted_num = 0;

    int* delete_in_vec = (int*) calloc(vec.size(), sizeof(int));

    while(1)
    {
	//if (deleted_num >= vec.size()) break;
	if (vec.size() <= 0) break;

	    //Uma lis uma vez.
	deleted_num += __remove_elems_lis(vec, delete_in_vec);
	counter++;
    }

    free(delete_in_vec);

    return counter;
    */
    return 0;
}

bool cmp_mat(Doll &a, Doll &b)
{
//[](Doll &a, Doll &b){return std::get<0>(a) < std::get<0>(b);}
    return std::get<0>(a) < std::get<0>(b) ||
	(std::get<0>(a) == std::get<0>(b) && std::get<1>(a) > std::get<1>(b) );
    //return a.w < b.w || (a.w == b.w && a.h > b.h);
}

int matroska()
{
    int dolls;
    std::cin >> dolls;
    DollVec doll_vec;
    int temp_w, temp_h;

    //Doll temp_doll;

    for (int i = 0 ; i < dolls ; i++)
    {
        std::cin >> temp_w >> temp_h;
	//temp_doll.w = temp_w;
	//temp_doll.h = temp_h;

        doll_vec.push_back(std::make_pair(temp_w, temp_h));
        //doll_vec.push_back(temp_doll);
    }

    //First, sort by width.
    std::sort(doll_vec.begin(),
		doll_vec.end(),
		cmp_mat);

    //for (auto doll : doll_vec)
	//printf("%d === %d\n", std::get<0>(doll), std::get<1>(doll));

    return __remove_elems_lis(doll_vec);
}

int main()
{
    int times;
    std::cin >> times;

    while (times--)
    {
	//printf("NEW INNNNNNNNN\n\n\n\n\n");
        printf("%d\n", matroska());
    }
}
