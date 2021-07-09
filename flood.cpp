#include "matriz.h"
#include "floodlib.h"

int main() {


    int col, lin, cores;

    scanf("%d %d %d", &col, &lin, &cores);
    //printf("%d %d %d \n", col, lin, cores);

    matriz mapa = alocaMatriz(lin, col);
    //leMatrix(&mapa, lin, col);
    mapa = geraMatriz(lin, col, cores);

    EscreveMatriz(mapa, lin, col);
    int cor;
    do {
        cin >> cor;

        flood(&mapa, 0, 0, (char)cor);
        EscreveMatriz(mapa, lin, col);
    }
    while ( !resolveu(mapa) );
    
    
    return 1;
}