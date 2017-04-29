#include "swap2opt.h"

#define ASPIRATION_IF_BETTER_THAN_GLOBAL

static inline float cycleLen2OptDiff(int* cycle, float** E, int al, int a, int b, int br) {
	float diff;
    //printf("(%d;%d) -> (%d;%d)", cycle[al], cycle[a], cycle[al], cycle[b]);
    //printf("diff: -%f-%f+%f+%f\n", E(cycle[al],cycle[a]), E(cycle[b],cycle[br]), E(cycle[al],cycle[b]), E(cycle[a],cycle[br]));
    diff = -(E(cycle[al],cycle[a]) + E(cycle[b],cycle[br]));
	diff += E(cycle[al],cycle[b]) + E(cycle[a],cycle[br]);
	return diff;
}

void swap2Opt(int n, int* dest, int* source, int al, int a, int b, int br) {
	/*
		little improvement
		memcpy is faster that assigning using for loop
		we should invert using loop smaller part of cycle
		inverting (a;b) is an equal operation on cycle as inverting (br;n-1)U(0;al)
	*/
	int halfN = n / 2;
	int braDiff = br - a;
	if (braDiff < halfN) {
		memcpy(dest, source, a * sizeof(int)); //size of (0;al) = (al - 0) + 1 = a, 
		for (int i = a, k = b; i <= b; ++i, --k) {
			dest[i] = source[k];
		}
		memcpy(dest + br, source + br, (n - br) * sizeof(int));
	}
	else {
		memcpy(dest + a, source + a, braDiff * sizeof(int));
		for (int i = br, k = al; i != al; --k) {
			dest[i] = source[k];
			if (k <= 0) k = n;
			++i;
			if (i >= n) i = 0;
		}
		dest[al] = source[br];
	}
}

int swap2OptNeighborhoodSize(int n) {
	return (n-3)*2 + (n-3)*(n-4)/2;
}

void chooseBestFromSwap2OptNeighborhood(int n, int* tmpCycle, float** E, int* bestA, int* bestB, float* bestLenDiff, bool** neighborhood, double tmpLen, double* bestCycleLen){
    /*
			2 opt neighborhood
			generally edges are (i-1;i) and (j;j+1)
			2 opt has sense only if [i;j] > 0 edges
			if i == j (2 directly neighbor edges)
				switching them makes no different (same cycle)
				fastest function for calculating length difference return bad value
					cutting of (i;i) = (j;j) verticle (making 0 length edge)
					connecting (i-1;j+1)

			guaranteed j+1 < n
			i-1 can be n-1!
		*/
    //1st case i = 0, i-1 = n-1, max reverse [0,[1;n-3]]
    for (int j = 1; j < n - 2; ++j) { //min different is (n-2;n-1) edge > 0 edges
        if (neighborhood[tmpCycle[j]][tmpCycle[0]] == true) {
            float lenDiff = cycleLen2OptDiff(tmpCycle, E, n - 1, 0, j, j + 1);
            //printf("(%d;0) (%d;%d) %f\n", n - 1, j, j + 1, lenDiff);
            if (lenDiff < *bestLenDiff) {
                *bestA = 0;
                *bestB = j;
                *bestLenDiff = lenDiff;
            }
        }
#ifdef ASPIRATION_IF_BETTER_THAN_GLOBAL
    	else { //aspiration
            float lenDiff = cycleLen2OptDiff(tmpCycle, E, n - 1, 0, j, j + 1);
            if(tmpLen + lenDiff < *bestCycleLen){
                *bestA = 0;
                *bestB = j;
                *bestLenDiff = lenDiff;
#ifdef LOGGING_ASPIRATION_CHECK
                printf("aspiration [%d;%d]\n", 0, j);
#endif
            }
        }
#endif
    }
    //2nd case i = 1, i-1=0,  max reverse [1,[2;n-2]]
    for (int j = 2; j < n - 1; ++j) { //min different is (n-1;0) edge > 0 edges
        if (neighborhood[tmpCycle[j]][tmpCycle[1]] == true) {
            float lenDiff = cycleLen2OptDiff(tmpCycle, E, 0, 1, j, j + 1);
            //printf("(0;1) (%d;%d) %f\n", j, j + 1, lenDiff);
            if (lenDiff < *bestLenDiff) {
                *bestA = 1;
                *bestB = j;
                *bestLenDiff = lenDiff;
            }
        }
#ifdef ASPIRATION_IF_BETTER_THAN_GLOBAL
        else { //aspiration
            float lenDiff = cycleLen2OptDiff(tmpCycle, E, 0, 1, j, j + 1);
            if(tmpLen + lenDiff < *bestCycleLen){
                *bestA = 1;
                *bestB = j;
                *bestLenDiff = lenDiff;
#ifdef LOGGING_ASPIRATION_CHECK
                printf("aspiration [%d;%d]\n", 1, j);
#endif
            }
        }
#endif
    }
    //3rd case (max reverse [[2;n-3],[3;n-2]]
    for (int i = 2; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            if (neighborhood[tmpCycle[j]][tmpCycle[i]] == true) {
                float lenDiff = cycleLen2OptDiff(tmpCycle, E, i - 1, i, j, j + 1);
                //printf("(%d;%d) (%d;%d) %f\n", i - 1, i, j, j + 1, lenDiff);
                if (lenDiff < *bestLenDiff) {
                    *bestA = i;
                    *bestB = j;
                    *bestLenDiff = lenDiff;
                }
            }
#ifdef ASPIRATION_IF_BETTER_THAN_GLOBAL
            else { //aspiration
                float lenDiff = cycleLen2OptDiff(tmpCycle, E, i - 1, i, j, j + 1);
                if(tmpLen + lenDiff < *bestCycleLen){
                    *bestA = i;
                    *bestB = j;
                    *bestLenDiff = lenDiff;
#ifdef LOGGING_ASPIRATION_CHECK
                    printf("aspiration [%d;%d]\n", i, j);
#endif
                }
            }
#endif
        }
    }
}
