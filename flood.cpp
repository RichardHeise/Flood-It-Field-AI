#include "IAra.h"

int main() {

    int col, lin, cores;

    scanf("%d %d %d", &col, &lin, &cores);

    matriz mapa = alocaMatriz(lin, col);
    leMatriz(&mapa, lin, col);
    resolve(mapa, cores);
    
    return 1;
}