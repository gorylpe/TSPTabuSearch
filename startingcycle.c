#include "startingcycle.h"

void firstCycleAscending(int n, int* cycle) {
	for (int i = 0; i < n; ++i) {
		cycle[i] = i;
	}
}

void firstCycleNearest(int n, int* cycle, float** E) {
	firstCycleAscending(n, cycle);
	int max = n - 1;
	for (int i = 0; i < max; ++i) {
		int minIt = i + 1;
		double min = E(cycle[i],cycle[minIt]);
		for (int j = minIt + 1; j < n; ++j) {
			if (E(cycle[i],cycle[j]) < min) {
				minIt = j;
				min = E(cycle[i],cycle[j]);
			}
		}
		swap(&cycle[i + 1], &cycle[minIt]);
	}
}

void firstCycleNEH(int n, int* cycle, float** E) {
	firstCycleAscending(n, cycle);
	double len = E(0,1) + E(1,0);
	for (int i = 2; i < n; ++i) {
		int insertIt = i; //dla kolejnych i, cycle[i] = i
		double minLen = len - E(cycle[insertIt - 1],0) + E(cycle[i - 1],cycle[i]) + E(i,0); //cycle[insertIt % i] = 0 because last element of cycle is 0th;
		for (int j = insertIt - 1; j >= 1; --j) {
			double tmpLen = len - E(cycle[j - 1],cycle[j]) + E(cycle[j - 1],cycle[i]) + E(cycle[i],cycle[j]);
			if (tmpLen < minLen) {
				minLen = tmpLen;
				insertIt = j;
			}
		}
		if (insertIt < i) {
			memmove(&cycle[insertIt + 1], &cycle[insertIt], (i - insertIt) * sizeof(int));
			cycle[insertIt] = i;
		}
		len = minLen;
	}
}