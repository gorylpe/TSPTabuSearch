#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "startingcycle.h"
#include "tabusearch.h"

void mainProgram(FILE* input, FILE* output, FILE* error){
    int n;
    fscanf(input, "%d", &n);

    float** E;
    int timeLimit = n * CLOCKS_PER_SEC / 20;

    //save memory
    E = malloc(n * sizeof(float*));
    for (int i = n - 1; i >= 0; --i) {
        E[i] = malloc((i + 1) * sizeof(float));
    }
    initializeEdges(n, E, input);

    int* cycle = malloc(n * sizeof(int));
    firstCycleNEH(n, cycle, E);

    double* cycleLength = malloc(sizeof(double));
    *cycleLength = cycleLen(n, cycle, E);

    //birthday paradox, probability > i.e. 50% to find the same neighbor
    tabuSearch(n, E, cycle, cycleLength, calculateBirthdayParadoxValue(swap2OptNeighborhoodSize(n), 0.5), timeLimit);

    //printCycle(n, cycle);

    fprintf(output, "%f\n", *cycleLength);
    int start;
    for (start = 0; start < n && cycle[start] != 0; ++start);
    for (int i = 0; i < n; ++i) {
        fprintf(error, "%d\n", cycle[(start + i)%n] + 1);
    }
    fprintf(error, "%d\n", cycle[start] + 1);

    for (int i = 0; i < n; ++i) {
        free(E[i]);
    }
    free(E);
    free(cycle);
    free(cycleLength);
}

int main(int argc, char* argv[])
{
	FILE* input = stdin;
	FILE* output = stdout;
	FILE* error = stderr;

	srand(time(NULL));

    if(argc > 1)
        input = fopen(argv[1], "r");

    mainProgram(input, output, error);
    //testTabuSize();
    //testMaxIterationsWithoutNewBest();
    //testMaxIterationsWithoutNewBestOnFile(input);

    if(argc > 1)
        fclose(input);

	return 0;
}

