#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> matriz;

void leMatrix (matriz *m, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++)
            scanf(" %d", &(*m)[i][j]);
    }
}

void EscreveMatrix (matriz m, int l, int c) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++)
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

void floodRecursivo (matriz *m, int posX, int posY, char corAnt, char novaCor)  {
    
    if (posX < 0 || posX >= (*m).size() || posY < 0 || posY >= (*m)[0].size())
        return;
    if ((*m)[posX][posY] != corAnt)
        return;
    if ((*m)[posX][posY] == novaCor)
        return;
 
    
    (*m)[posX][posY] = novaCor;
 
    
    floodRecursivo(&(*m), posX+1, posY, corAnt, novaCor);
    floodRecursivo(&(*m), posX-1, posY, corAnt, novaCor);
    floodRecursivo(&(*m), posX, posY+1, corAnt, novaCor);
    floodRecursivo(&(*m), posX, posY-1, corAnt, novaCor);
}   

void flood (matriz *m, int posX, int posY, char novaCor) {
    char corAnt = (*m)[posX][posY];
    floodRecursivo(&(*m), posX, posY, corAnt, novaCor);
}

int resolveu (matriz m, char novaCor) {    
    int cont = 0;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++)
            if (m[i][j] == novaCor) 
                cont++;
    }

    if (cont == (m.size() * m[0].size()) ) {
        printf("Terminou\n");
        return 1;    
    }

    return 0;
}

int main() {


    int col, lin, cores;

    scanf("%d %d %d", &col, &lin, &cores);
    //printf("%d %d %d \n", col, lin, cores);

    matriz mapa = alocaMatriz(lin, col);
    leMatrix(&mapa, lin, col);

    EscreveMatrix(mapa, lin, col);
    int cor;
    do {
        cin >> cor;

        flood(&mapa, 0, 0, (char)cor);
        EscreveMatrix(mapa, lin, col);
    }
    while ( !resolveu(mapa, mapa[0][0]) );
    
    
    return 1;
}