#include "matriz.h"
using namespace std;

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

int resolveu (matriz m) {    
    int cont = 0;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++)
            if (m[i][j] == m[0][0]) 
                cont++;
    }

    if (cont == (m.size() * m[0].size()) ) {
        printf("Terminou\n");
        return 1;    
    }

    return 0;
}