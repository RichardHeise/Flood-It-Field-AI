#include "floodlib.h"
#include <algorithm>
using namespace std;

#define MAX_ESCOPOS 1

float h(matriz m, int cores);

vector<char> resolveFlood (matriz *m, int cores);

vector<char> resolve (matriz m, int cores);

char buscaMelhorJogada (matriz m, int cores);

float preveJogada (matriz m, int cores, int escopos);
