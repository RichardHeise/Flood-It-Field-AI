#include <iostream>
#include <time.h>
#include <vector>
using namespace std;

typedef vector<vector<char>> matriz;

void leMatriz (matriz *m, int l, int c);

void EscreveMatriz (matriz m);

matriz alocaMatriz (int l, int c);

matriz geraMatriz (int l, int c, int cors);