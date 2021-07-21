#include "matriz.h"
#include "floodlib.h"
#include <deque>
using namespace std;

static void showq(deque<coordenada> gq)
{
    deque<coordenada> g = gq;
    while (!g.empty()) {
        cout << '\t' << g.front().first;
        cout << '\t' << g.front().second;
        g.pop_back();
    }
    cout << '\n';
}
  

void floodFill (matriz *m, int posX, int posY, char corAnt, char novaCor)  {
    
    deque<coordenada> lista;

    lista.push_back(make_pair(posX, posY));

    while (!lista.empty()) {
        coordenada p_par = lista.back();
        lista.pop_back();

        if( flood(&(*m), p_par.first, p_par.second, corAnt, novaCor) ) {

            lista.push_back(make_pair(p_par.first+1, p_par.second));
            lista.push_back(make_pair(p_par.first-1, p_par.second));
            lista.push_back(make_pair(p_par.first, p_par.second+1));
            lista.push_back(make_pair(p_par.first, p_par.second-1));
            
        }
    }
}   

int flood (matriz *m, int posX, int posY, char corAnt, char novaCor) {
    if (posX < 0 || posX >= (*m).size() || posY < 0 || posY >= (*m)[0].size()
        || (*m)[posX][posY] != corAnt || (*m)[posX][posY] == novaCor)
        return 0;

    (*m)[posX][posY] = novaCor;
    return 1;
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