// Simple evolutive system

#include <unordered_map>

typedef unsigned int uint;

struct Terrain
{
    Terrain(uint size)
    {
        this->size = size;
        terrain = new char[size*size];
    }

    ~Terrain()
    {
        delete terrain;
    }

    char* terrain;
    uint size;

    char* terrain_at(uint lat, uint lon)
    {
        return terrain + (lat * size) + lon;
    }

    //std::unordered_map<> trees;
};

/* Gene table:

age_to_maturity: age until tree can leave its seeds

*/

struct gene_table
{
    age_to_maturity

    static gene_table cross_over(const &a, const &b)
    {
        gene_table new_gene_table;

        //actually perform crossover.
        return new_gene_table;
    }
};

class Tree
{
public:
    Tree(Terrain &a_terrain) : terrain(a_terrain)
    {
        age = 0;
        strength = 0;
    }

    void run_year()
    {
        if (age < genes.age_to_maturity)
        {
            //Grow.
            strength += 1;
        }
        else
        {
            drop_seeds();
        }
    }

    void drop_seeds()
    {
        // Seed number = 4, for now.


    }

private:
    //Tree properties
    gene_table genes;
    int age;
    int strength;

    Terrain &terrain;
};

evaluate()
{

}

run_year()
{

}

int main(int argc, char const *argv[])
{
    
    return 0;
}