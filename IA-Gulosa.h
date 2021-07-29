#include "floodlib.h"

#define MAX_ESCOPOS 3

using namespace std;

void showq(deque<coordenada> gq);

deque<coordenada> descobreBorda (matriz *m, int posX, int posY, deque<coordenada> ci);

int borda (matriz *m, deque<coordenada> *fb, deque<coordenada> *fv, coordenada c, char corAtual);

int encontraPosicao (deque<coordenada> f, coordenada  c);

deque<pair<char, coordenada>> possiveisCores (matriz *m, coordenada c, deque<coordenada> fb);

int checaCoresBorda(deque<pair<char, coordenada>> cores);

deque<coordenada> descobreCluster (matriz *m, char cor, coordenada inicio);

deque<char> resolveFlood (matriz m);

char buscaMelhorJogada (matriz m, int escopos, coordenada coordAtual, deque<coordenada> *clusterInicial, int *maiorCluster);