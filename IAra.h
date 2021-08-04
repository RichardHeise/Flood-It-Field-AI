#include "floodlib.h"
#include <algorithm>
using namespace std;

#define MAX_ESCOPOS 3

void showq(deque<coordenada> gq);

vector<char> resolveFlood (matriz *m, int cores);

char buscaMelhorJogada (matriz m, int cores);

float preveJogada (matriz m, int cores, int escopos);
