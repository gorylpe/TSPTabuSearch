# TSPTabuSearch

# Introduction

Travelling Salesman Problem in C with Tabu Search.
Project created for Metaheuristic algorithms course.

# Efficiency

Output differs from optimum for about **4%** for average case.
Program works for about **n/20** seconds where n is the size of data (number of cities).

# Implementation details

## First solution

First solution is found using greedy algorithm "Nearest Insertion".
Computation complexity of this algorithm is O(n^2).

## Next improvements

This program uses metaheuristic Tabu Search.

Neighborhood is defined by 2opt swaps.

Tabu list length is calculated using birthday paradox.
List has as much swaps as collision probability is 50%.
It was selected empirically based on results, tests and intuition.