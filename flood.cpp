#include "IA-Gulosa.h"

int main() {

    int col, lin, cores;

    scanf("%d %d %d", &col, &lin, &cores);
    //printf("%d %d %d \n", col, lin, cores);

    matriz mapa = alocaMatriz(lin, col);
    leMatriz(&mapa, lin, col);

    //mapa = geraMatriz(lin, col, cores);

    //EscreveMatriz(mapa, lin, col);
    int cor;
    descobreBorda(&mapa, 0, 0);

    /*
    do {
        cin >> cor;

        floodFill(&mapa, (char)cor);
        EscreveMatriz(mapa, lin, col);
    }
    while ( !resolveu(mapa) );
    */
    
    return 1;
}