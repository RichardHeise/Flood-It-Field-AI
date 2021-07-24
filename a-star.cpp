#include "a-star.h"

t_nodo inicializaNodo(auto valor) {
    t_nodo novoNodo;
    novoNodo.pai = NULL;
    novoNodo.posicao = NULL;
    novoNodo.g = novoNodo.f = novoNodo.h = 0;

    return novoNodo;
}

void A_Star(matriz m, auto inicio, auto fim) {

    t_nodo nodoInicial = inicializaNodo(inicio);
    t_nodo nodoFinal = inicializaNodo(fim);

    deque<t_nodo> listaAberta;
    deque<t_nodo> listaFechada;

    listaAberta.push_back(nodoInicial);

    while ( listaAberta.size() ) {

        t_nodo nodoAtual = listaAberta[0];
        int indexAtual = 0;

        for (int i = 1; i < listaAberta.size() ; i++ ) {
            if (listaAberta[i].f < nodoAtual.f) {
                nodoAtual = listaAberta[indexAtual];
                indexAtual = i;
            }
        }

        

    }

}


