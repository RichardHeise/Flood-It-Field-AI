#include "floodlib.h"
#include <algorithm>
using namespace std;

#define MAX_ESCOPOS 3

float h(matriz m, int cores);

void resolve (matriz m, int cores);

char buscaMelhorJogada (matriz m, int cores);

float preveJogada (matriz m, int cores, int escopos);
