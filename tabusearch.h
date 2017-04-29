#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "tabulist.h"
#include "swap2opt.h"
#include "math.h"
#include "util.h"

void tabuSearch(int n, float** E, int* bestCycle, double* bestCycleLen, int tabuMax, int timeLimit);

