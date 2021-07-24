#include <deque>
#include "matriz.h"
using namespace std;

typedef struct s_nodo {
    s_nodo* pai;
    s_nodo* posicao;
    int g;
    int h;
    int f;

} t_nodo;

void A_Star(matriz m, auto start, auto end);