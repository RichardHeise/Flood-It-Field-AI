#include "floodlib.h"
#include <algorithm>
using namespace std;

#define MAX_ESCOPOS 3
#define BAIXO 0
#define DIREITA 1
#define ESQUERDA 2
#define CIMA 3

typedef struct s_nodo {
    matriz jogo;
    vector<char> jogadas;
    float heuristica;
} t_nodo;

void showq(deque<coordenada> gq);

deque<coordenada> descobreBorda (matriz *m, int posX, int posY, deque<coordenada> ci);

int borda (matriz *m, deque<coordenada> *fb, deque<coordenada> *fv, coordenada c, char corAtual);

int encontraPosicao (deque<coordenada> f, coordenada  c);

deque<pair<char, coordenada>> possiveisCores (matriz *m, coordenada c, deque<coordenada> fb);

int checaCoresBorda(deque<pair<char, coordenada>> cores);

deque<coordenada> descobreCluster (matriz *m, char cor, coordenada inicio);

vector<char> resolveFlood (matriz *m, int cores);

char buscaMelhorJogada (matriz m, int cores);
