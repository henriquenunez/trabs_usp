#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>

//Expects non null-terminated string, hence pat_size
long int *pattern_enhancer(const char* pattern, long int pat_size) //returns pattern enhancer
{
    long int *ret = (long int*) calloc(pat_size+1, sizeof(long int));
    long int pat_index = 0;
    long int suffix_match = -1;
    ret[0] = -1;

    while (pat_index < pat_size) //Will run through vec.
    {
        while (suffix_match >= 0 && 
               (pattern[pat_index] != pattern[suffix_match]))
                    suffix_match = ret[suffix_match];
        pat_index++;
        suffix_match++;

        ret[pat_index] = suffix_match;
    }

    return ret;
}

std::vector<long int> pattern_search(const char* pattern, long int *enhancer, long int pat_size, char* buf, long int buf_size)
{
    std::vector<long int> ret;

    long int i = 0, j = 0;
    while (i < buf_size)
    {
        while(j >= 0 && (buf[i] != pattern[j]))
            j = enhancer[j];

        i++; j++;

        if (j == pat_size) //This means no error occurred until now.
        {
            ret.push_back(i-j);
            j = enhancer[j];
        }
    }

    return ret;
}

int main()
{
    char* text = NULL;
    char* pattern = NULL;
    long int t_len = 0, pat_len = 0;
    long int *KMP_enh;
    std::vector<long int> search_occurences;

    //getline(&text, &t_len, stdin);
    //getline(&pattern, &pat_len, stdin);

    scanf("%ms", &text);
    scanf("%ms", &pattern);

    //Since getline stores the \n character, we must remove it.
    
    t_len = strlen(text);
    pat_len = strlen(pattern);

    KMP_enh = pattern_enhancer(pattern, pat_len);

    search_occurences = pattern_search(pattern, KMP_enh, pat_len, text, t_len);

    for (long int place : search_occurences)
        printf("O padrao foi encontrado na posicao %ld\n", place);

    free(text);
    free(pattern);
    free(KMP_enh);

    return 0;
}
