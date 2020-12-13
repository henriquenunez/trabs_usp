#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <utility>
#include <cstdlib>

#define MAX_N 100

int PRIMES[MAX_N+1]; //+1 for convenience

void sieve_of_eratosthenes()
{
    int i;

    memset(PRIMES, 0xFF, (MAX_N+1)*sizeof(int) );

    for (i = 2; i*i < MAX_N; i++)
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

std::pair<std::vector<int>, int> factoration(int val, std::vector<int> primes_vec)
{
    std::vector<int> factor_amount;
    std::vector<int>::iterator curr_prime, curr_prime_amount;
    int prime_n = 1;

    factor_amount.resize(primes_vec.size(), 0);

    for (int i = 2 ; i <= val ; i++) //Running through every component of factorial
    {
        int temp = i, temp_prime_n = 1;
        curr_prime = primes_vec.begin();
        curr_prime_amount = factor_amount.begin();

        //Now, decomposing it.
        while(temp != 1 && curr_prime != primes_vec.end())
        {
            if (temp % (*curr_prime) == 0)
            {
                temp /= *curr_prime;
                (*curr_prime_amount)++;
            }
            else
            {
                curr_prime++;
                curr_prime_amount++;
                if (prime_n < ++temp_prime_n) prime_n = temp_prime_n;
            }
        }
    }

    return std::make_pair(factor_amount, prime_n);
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

    int temp_int;
    std::pair<std::vector<int>, int> asw;

    size_t line_len = 0;
    char *line = NULL;

    while(1)
    {
        getline(&line, &line_len, stdin);
        sscanf(line, "%d", &temp_int);

        if (!temp_int) break;

        asw = factoration(temp_int, primes_vec);
        //Print output
        printf("%3d! =", temp_int);

        int wtf = 0;
        for (int i = 0 ; i < asw.second ; i++)
        {
            wtf++;
            if (wtf % 16 == 0) printf("\n      ");
            printf("%3d", asw.first[i]);
        }
        printf("\n");
    }

    free(line);

    return 0;
}
