#pragma once
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "util.h"
/*
	al = a - 1;
	br = b + 1;
	swap2opt is swapping endpoints of edges a and b in this way:
	(a-1;a) -> (a-1;b)
	(b;b+1) -> (a;b+1)
	a and b are switched so a->b tour has to be reversed
	(...,a-2,a-1,a,a1+1,...,b-1,b,b+1,...) into (...,a-2,a-1,b,b-1,b-2,...,a+2,a+1,a,b+1,b+2,...)

	should be guaranteed br >= 2 and <= n - 1
	al can be equal n-1
*/
void swap2Opt(int n, int* dest, int* source, int al, int a, int b, int br);

int swap2OptNeighborhoodSize(int n);

void chooseBestFromSwap2OptNeighborhood(int n, int* tmpCycle, float** E, int* bestA, int* bestB, float* bestLenDiff, bool** neighborhood, double tmpLen, double* bestCycleLen);
