#include "tabulist.h"

void initTabu(Tabu** tabu, int tabuMax, int n) {
	(*tabu)->tabuMax = tabuMax;
	(*tabu)->it = 0;
	(*tabu)->nodes = malloc(tabuMax * sizeof(Node*));
	for (int i = 0; i < tabuMax; ++i) {
		Node* node = malloc(sizeof(Node));
		node->cadence = -1;
		(*tabu)->nodes[i] = node;
	}
}

void freeTabu(Tabu* tabu) {
	for (int i = 0; i < tabu->tabuMax; ++i) {
		free(tabu->nodes[i]);
	}
	free(tabu->nodes);
}

void push(int a, int b, int cadence, Tabu* tabu) {
	Node* node = tabu->nodes[tabu->it];
	node->val[0] = a;
	node->val[1] = b;
	node->cadence = cadence;
	tabu->it = (tabu->it + 1) % tabu->tabuMax;
}

void set2OptNeighborhoodUsingTabuList(int n, Tabu *tabu, bool **neighborhood) {
	Node* node;
	for (int i = 0; i < tabu->tabuMax; ++i) {
		node = tabu->nodes[i];
		if (node->cadence != -1) { //if node is not free
            int a = node->val[0];
            int b = node->val[1];
			neighborhood[a][b] = false;
			neighborhood[b][a] = false;
		}
	}
}

void checkCadency(int n, Tabu* tabu, int k) {
	Node* node;
	for (int i = 0; i < tabu->tabuMax; ++i) {
		node = tabu->nodes[i];
		if (node->cadence == k) {
			node->cadence = -1;
		}
	}
}
