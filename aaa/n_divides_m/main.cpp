#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <utility>
#include <cstdlib>
#include <unordered_map>

/*  We must only check values up to sqrt(2^31-1)
 *  Since we're able to say whether it's a prime or not, by the factors.
 * */
#define MAX_N 46341

void sieve_of_eratosthenes(int *PRIMES, std::vector<int> &primes_vec)
{
    primes_vec.clear();
    int i;

    //Setting everyone to 1
    memset(PRIMES, 0xFF, (MAX_N+1)*sizeof(int) );

    for (i = 2; i <= MAX_N; i++)
    {
        if (!PRIMES[i]) continue;
        int j = i*2;

        while (j < MAX_N)
        {
            PRIMES[j] = 0;
            j += i;
        }
    }
}

/* How many times a prime p
 * occurs in n!
 * */
int prime_factors_on_factorial(int n)
{
    int ret = 0;

    return ret;
}

void prime_factors(long int val, std::vector<int> &primes_vec, std::unordered_map<int, int> &factors)
{
    std::vector<int> factor_amount;
    std::vector<int>::iterator curr_prime, curr_prime_amount;
    int prime_n = 1;

    factor_amount.resize(primes_vec.size(), 0);

    curr_prime = primes_vec.begin();
    curr_prime_amount = factor_amount.begin();

    //Now, decomposing it.
    while(val != 1 && curr_prime != primes_vec.end())
    {
        //printf("Val is : %d\n", val);
        if (val % (*curr_prime) == 0)
        {
            val /= *curr_prime;

            // Check if prime exists in map
            // and add to it.
            if (curr_prime in map)
            {
                factors[curr_prime]++;
            }
            else
            {
                factors[curr_prime] = 1;
            }

            (*curr_prime_amount)++;
        }
        else
        {
            curr_prime++;
            curr_prime_amount++;
            prime_n++;
        }
    }

    if (curr_prime == primes_vec.end())
        return std::make_pair(factor_amount, 0);

    return std::make_pair(factor_amount, prime_n);
}

// m divides n! ??
bool check_divides(long int n, long int m, std::vector<int> &primes_vec)
{
    if (m <= n) return true;
    if (m == 0) return false;

    //Maps a value.
    // Let's find the factorial of the divisor first.
    
    std::unordered_map<int, int> m_factors;
    prime_factors(m, primes_vec, m_factors);

    //Print
    /*
    for(int a : asw_m.first)
        printf("%3d ", a);
    printf("\n");
    */

    // Now, to check if divides, lets first check if
    // there is no larger prime on n than in m.
    if (asw_m.second > asw_n.second || asw_m.second == 0) return false;

    for (int i = 0 ; i < asw_m.second ; i++)
    {
        //printf("Trying %d!\n", i);
        if (asw_n.first[i] < asw_m.first[i])
            return false;
    }

    return true;
}

int main()
{
    std::vector<int> primes_vec;

    //Initialize primes.
    sieve_of_eratosthenes();

    for (int i = 2 ; i <= MAX_N ; i++)
    {
        if (PRIMES[i])
        {
            primes_vec.push_back(i);
            //printf("%d ", i);
        }
    }

    long int n, m;

    size_t line_len = 0;
    char *line = NULL;

    while(getline(&line, &line_len, stdin) > 0)
    {        
        printf("Input was {%s}\n", line);
        sscanf(line, "%ld %ld", &n, &m);
        printf("%ld %s %ld!\n", m, check_divides(n, m, primes_vec) ? "divides" : "does not divide", n);
    }

    free(line);

    return 0;
}
