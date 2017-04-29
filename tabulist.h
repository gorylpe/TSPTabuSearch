#pragma once
#include "util.h"
#include <stdbool.h>

typedef struct TNode {
	int val[2];
	int cadence; //if 0 then null
} Node;

typedef struct TTabu { //ZMIENIC
	int tabuMax;
	int length;
	int it;
	Node** nodes;
} Tabu;

void initTabu(Tabu** tabu, int tabuMax, int n);

void freeTabu(Tabu* tabu);

void push(int a, int b, int cadence, Tabu* tabu);

void pushConstCadence(int a, int b, Tabu* tabu);

void set2OptNeighborhoodUsingTabuList(int n, Tabu *tabu, bool **neighborhood);

void checkCadency(int n, Tabu* tabu, int k);


