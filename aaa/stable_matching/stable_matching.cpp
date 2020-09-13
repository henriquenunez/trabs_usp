#include <iostream>
#include <istream>
#include <queue>
#include <vector>
#include <utility>

int position_counter(std::vector<int> list, int val)
{
    for (unsigned int i = 0; i < list.size(); ++i)
        if (list[i] == val) return i;
    return -1;
}

//Engs -> engagements: <man, woman>
int find_from_pair_vec(std::vector<std::pair<int, int>> engs, int val)
{
    for (unsigned int i = 0; i < engs.size(); ++i)
        if (engs[i].second == val) return engs[i].first;
    return -1;
}

void stable_matching()
{
    int c_number; //Number of couples
    int temp;

    std::vector<std::pair<int, int>> engagements;
    std::vector<std::vector<int>> men_preferences, women_preferences;
    std::cin >> c_number;
    //std::cout << "Number of couples " << c_number << std::endl;

    //whether man is engaged, and women he has proposed to.
    std::vector<std::pair<bool, std::vector<bool>>> men_proposals;
    int single_man_counter = c_number;

    men_preferences.resize(c_number);
    women_preferences.resize(c_number);
    men_proposals.resize(c_number);

    for (int i = 0; i < c_number; ++i)
    {
        men_preferences[i].resize(c_number);
        women_preferences[i].resize(c_number);
        men_proposals[i].second.resize(c_number, false);
        men_proposals[i].first = false;
    }

    //std::cout << "WOMEN:" << std::endl;
    for (int i = 0; i < c_number; ++i) //Getting for women.
        for (int j = 0; j <= c_number; ++j)
        {
            std::cin >> temp;
            if (j != 0) //Ignoring first col.
            {
                women_preferences[i][j-1] = temp-1;
                //std::cout << "\nGot:" << women_preferences[i][j-1];
            }
        }

    //std::cout << "MEN:" << std::endl;
    for (int i = 0; i < c_number; ++i) //Getting for men.
        for (int j = 0; j <= c_number; ++j)
        {
            std::cin >> temp;
            if (j != 0) //Ignoring first col.
            {
                men_preferences[i][j-1] = temp-1;
                //std::cout << "\nGot:" << men_preferences[i][j-1];
            }
        }

    int curr_man_idx;

    //While are there single men and man hasnt proposed to all.
    while(single_man_counter > 0)
    {
        for (unsigned int i = 0 ; i < men_proposals.size() ; ++i) //Find not engaged guy.
            if (men_proposals[i].first == false) //This guy is not engaged.
            {
                curr_man_idx = i;
                //std::cout << "Curr man index " << curr_man_idx << "\n";
                /*for (int j = 0; j < men_preferences.size(); ++j)
                {
                    std::cout << men_preferences[curr_man_idx][j] << " ";
                }*/

                break;
            }

        //Try to engage.
        for (int i = 0; i < c_number; ++i) //Running on vector
        {
            int woman_number = men_preferences[curr_man_idx][i];

            if(men_proposals[curr_man_idx].second[woman_number] == false) //Find top priority.
            {
                //std::cout << "woman_number " << woman_number << "\n";
                men_proposals[curr_man_idx].second[woman_number] = true; //Engaged to that woman.

                //Woman check if this man is better.
                int curr_woman_fiance = find_from_pair_vec(engagements, woman_number);

                if (curr_woman_fiance != -1)
                {
                    //Lets compare if the new guy is better.
                    if(position_counter(women_preferences[woman_number], curr_man_idx) <
                        position_counter(women_preferences[woman_number], curr_woman_fiance))
                    {
                        for (unsigned int i = 0; i < engagements.size(); ++i)
                        {
                            if(engagements[i].first == curr_woman_fiance)
                            {
                                engagements.erase(engagements.begin() + i);
                                men_proposals[curr_woman_fiance].first = false;
                                single_man_counter++;
                                break;
                            }
                        }
                        engagements.push_back(std::make_pair(curr_man_idx, woman_number));
                        men_proposals[curr_man_idx].first = true;
                        single_man_counter--;
                    }
                }
                else //If there is no fiance at this point, just engage.
                {
                    //std::cout << "First proposal\n";
                    men_proposals[curr_man_idx].first = true;
                    engagements.push_back(std::make_pair(curr_man_idx, woman_number));
                    single_man_counter--;
		    break;
                }
            }
        }
    }
    for (unsigned int i = 0; i < engagements.size(); ++i)
    {
        std::cout << engagements[i].first+1 << " " << engagements[i].second+1 << std::endl;
    }

}

int main()
{
    int times;
    std::cin >> times;
    //std::cout << "times " << times << std::endl;

    while (times--) stable_matching();
}
