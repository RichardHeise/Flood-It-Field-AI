#include "matriz.h"
using namespace std;

void leMatriz (matriz *m, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++)
            scanf(" %d", &(*m)[i][j]);
    }
}

void EscreveMatriz (matriz m) {
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

matriz alocaMatriz (int l, int c) {
    matriz m(l);
    for (int i = 0; i < l; i++) {
        m[i].resize(c);
    }

    return m;
}

matriz geraMatriz (int l, int c, int cors) { 

    matriz m = alocaMatriz(l, c);

    srand(time(NULL));

    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++)
            m[i][j] = (rand() % cors + 1);
    }

    return m;
} 