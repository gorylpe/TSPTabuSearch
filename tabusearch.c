#include "tabusearch.h"

//#define LOGGING
#ifdef LOGGING
#define LOGGING_TABU
#endif

void tabuSearch(int n, float** E, int* bestCycle, double* bestCycleLen, int tabuMax, int timeLimit) {
	Tabu* tabu;
    tabu = malloc(sizeof(Tabu));
    initTabu(&tabu, tabuMax, n);

	int* tmpCycle = malloc(n * sizeof(int));
	int* tmpCycleSecondary = malloc(n * sizeof(int));
	double tmpLen = *bestCycleLen;
	memcpy(tmpCycle, bestCycle, n * sizeof(int));

	bool** neighborhood2Opt = malloc(n * sizeof(bool*));
    for (int i = n - 1; i >= 0; --i) {
        neighborhood2Opt[i] = malloc(n * sizeof(bool));
    }

	int operations = 0;

	long time = clock();
	for (; clock() - time < timeLimit; ++operations) {
#ifdef LOGGING
		printf("\n----------------------\nLoop: %d\n", operations);
		printCycle(stdout, n, tmpCycle);
		printf(" len = %f\n", tmpLen);
		printf("2opt neighborhood\n");
#endif
        int bestA, bestB;
        float bestLenDiff = INFINITY;

        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
				neighborhood2Opt[i][j] = true;
			}
		}
        set2OptNeighborhoodUsingTabuList(n, tabu, neighborhood2Opt);

        chooseBestFromSwap2OptNeighborhood(n, tmpCycle, E, &bestA, &bestB, &bestLenDiff, neighborhood2Opt, tmpLen, bestCycleLen);

        push(tmpCycle[bestA], tmpCycle[bestB], operations + tabuMax, tabu);

#ifdef LOGGING
		printf("\nswap2opt [%d;%d] [%d;%d]\n", tmpCycle[bestA > 0 ? bestA - 1 : n - 1], tmpCycle[bestA], tmpCycle[bestB], tmpCycle[bestB + 1]);
		printf("diff = %f\n", bestLenDiff);
#endif
		//rewrite new cycle
		swap2Opt(n, tmpCycleSecondary, tmpCycle, bestA > 0 ? bestA - 1 : n - 1, bestA, bestB, bestB + 1);
		//and swap pointers
		int* swapCycle = tmpCycle;
		tmpCycle = tmpCycleSecondary;
		tmpCycleSecondary = swapCycle;

		tmpLen += bestLenDiff;

#ifdef LOGGING
		printf("after swap\n");
		printCycle(stdout, n, tmpCycle);
		printf(" len = %d\n", (int)tmpLen);
#endif

		if (tmpLen < *bestCycleLen) {
			memcpy(bestCycle, tmpCycle, n * sizeof(int));
			*bestCycleLen = tmpLen;
		}

		checkCadency(n, tabu, operations);

#ifdef LOGGING_TABU
		printf("Tabu's\n");
		for (int i = 0; i < tabu->tabuMax; ++i) {
			Node* node = tabu->nodes[i];
			printf("[%d;%d]\n", node->val[0], node->val[1]);
		}
		printf("\n");
#endif

#ifdef LOGGING
        if(operations >= 10) break;
#endif
    }
#ifdef LOGGING
	printf("Loops searching:%d\n", operations);
#endif
	freeTabu(tabu);
	free(tmpCycle);
	free(tmpCycleSecondary);
    for (int i = 0; i < n; ++i) {
        free(neighborhood2Opt[i]);
    }
    free(neighborhood2Opt);
}
