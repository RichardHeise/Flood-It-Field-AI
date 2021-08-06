#include "matriz.h"

using namespace std;
#define MAX 40000

typedef pair<int, int> coordenada;

void floodFill (matriz *m, char novaCor, coordenada inicio);

int flood (matriz *m, coordenada c, char corAnt, char novaCor);

int resolveu (matriz m);
