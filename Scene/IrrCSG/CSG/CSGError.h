#ifndef CSGERROR_H
#define CSGERROR_H
#include "../../../../../config.h"
#ifdef CSG
#include <stdio.h>

void heapAllocationFailure();
void externalError();
void triangleSplitError();
void debug(char msg[]);

#endif
#endif
