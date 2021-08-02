#include "matriz.h"
#include <deque>

using namespace std;
#define MAX 40000

typedef pair<int, int> coordenada;

void floodFill (matriz *m, char novaCor, coordenada inicio);

int flood (matriz *m, int posX, int posY, char corAnt, char novaCor);

int resolveu (matriz m);
