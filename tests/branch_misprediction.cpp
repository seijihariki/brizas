#include <vector>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <algorithm>

typedef unsigned long long int uli;
typedef unsigned char byte;

const uli iterations = 100000000;

int main ()
{
    byte *vec = new byte[iterations];

    printf ("Setting up vector in heap...\n");
    srand(time(0));

    for (uli i = 0; i < iterations; i++)
        vec[i] = rand()%256;

    uli tmp = 0;

    // Minimizes cache mispredictions
    std::clock_t start_min;
    double dur_min;

    printf ("Running minimum branch misprediction example...\n");

    start_min = std::clock();

    uli sum_min = 0;
    for (uli i = 0; i < iterations; i++)
    {
        if (vec[i] > 128)
            sum_min ++;
        else
            sum_min --;
    }

    dur_min = (std::clock() - start_min) / (double) CLOCKS_PER_SEC;

    // Maximizes cache mispredictions
    std::clock_t start_max;
    double dur_max;

    printf ("Sorting vector...\n");
    std::sort(vec, vec + iterations);

    printf ("Running maximum branch misprediction example...\n");

    start_max = std::clock();

    uli sum_max = 0;
    for (uli i = 0; i < iterations; i++)
    {
        if (vec[i] > 128)
            sum_max ++;
        else
            sum_max --;
    }

    dur_max = (std::clock() - start_max) / (double) CLOCKS_PER_SEC;

    printf ("Minimum branch misprediction time: %lf s\n", dur_min);
    printf ("Maximum branch misprediction time: %lf s\n", dur_max);
}
