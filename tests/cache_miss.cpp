#include <vector>
#include <stdio.h>
#include <ctime>

typedef unsigned long long int uli;
typedef unsigned char byte;

const uli iterations = 100000000;

int main()
{
    byte *vec = new byte[iterations];

    printf ("Setting up vector in heap...\n");
    for (uli i = 0; i < iterations; i++)
        vec[i] = i%256;

    uli tmp = 0;

    // Minimizes cache misses
    std::clock_t start_min;
    double dur_min;

    printf ("Running minimum cache miss example...\n");

    start_min = std::clock();

    uli sum_min = 0;
    for (uli i = 0; i < iterations; i++)
    {
        tmp = (i + 1)/2;
        tmp = i%2 ? (-tmp + iterations) : tmp;
        sum_min += vec[i];
    }

    dur_min = (std::clock() - start_min) / (double) CLOCKS_PER_SEC;

    // Maximizes cache misses
    std::clock_t start_max;
    double dur_max;

    printf ("Running maximum cache miss example...\n");

    start_max = std::clock();

    uli sum_max = 0;
    for (uli i = 0; i < iterations; i++)
    {
        tmp = (i + 1)/2;
        tmp = i%2 ? (-tmp + iterations) : tmp;
        sum_max += vec[tmp];
    }

    dur_max = (std::clock() - start_max) / (double) CLOCKS_PER_SEC;

    printf ("Minimum cache miss time: %lf s\n", dur_min);
    printf ("Maximum cache miss time: %lf s\n", dur_max);
}
