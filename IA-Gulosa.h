#include "floodlib.h"

using namespace std;

void showq(deque<coordenada> gq);

deque<coordenada> descobreBorda (matriz m, int posX, int posY);

int encontraElemento (deque<coordenada> f, coordenada  c);