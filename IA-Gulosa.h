#include "floodlib.h"

#define MAX_ESCOPOS 4

using namespace std;

void showq(deque<coordenada> gq);

deque<coordenada> descobreBorda (matriz *m, int posX, int posY);

int borda (matriz *m, deque<coordenada> *fb, deque<coordenada> *fv, coordenada c, char corAtual);

int encontraPosicao (deque<coordenada> f, coordenada  c);

pair<char, int> escolheCor (matriz *m, coordenada c);

deque<coordenada> descobreCluster (matriz *m, char cor, coordenada inicio);

//deque<char> resolveFlood (matriz m);

deque<char> resolveFlood (matriz m, coordenada c);