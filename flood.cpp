#include "IAra.h"

int main() {

    int col, lin, cores;

    scanf("%d %d %d", &col, &lin, &cores);

    matriz mapa = alocaMatriz(lin, col);
    leMatriz(&mapa, lin, col);
    resolveFlood(&mapa, cores);

    //mapa = geraMatriz(lin, col, cores);

    //EscreveMatriz(mapa);

    //printf("tamanho: %lu \n", resolveu.size());

    /*
    while ( !resolveu.empty() ) {
        printf("%d ", resolveu.front());
        resolveu.pop_front();
    }
    printf("\n");
    */
    /*
    int cor;
    do {
        cin >> cor;

        floodFill(&mapa, (char)cor, make_pair(0,0));
        EscreveMatriz(mapa);
    }
    while ( !resolveu(mapa) );
    */
    
    return 1;
}