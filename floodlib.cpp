#include "floodlib.h"
using namespace std;
  

void floodFill (matriz *m, char novaCor, coordenada inicio)  {
    
    vector<coordenada> lista;

    lista.push_back(inicio);
    char corAnt = (*m)[0][0];

    while (!lista.empty()) {
        coordenada aux = lista.back();
        lista.pop_back();

        if ( flood(&(*m), aux, corAnt, novaCor) ) {

            lista.push_back(make_pair(aux.first+1, aux.second));
            lista.push_back(make_pair(aux.first-1, aux.second));
            lista.push_back(make_pair(aux.first, aux.second+1));
            lista.push_back(make_pair(aux.first, aux.second-1));
            
        }
    }
}   

int flood (matriz *m, coordenada c, char corAnt, char novaCor) {
    if (c.first < 0 || c.first >= (*m).size() || c.second < 0 || c.second >= (*m)[0].size()
        || (*m)[c.first][c.second] != corAnt || (*m)[c.first][c.second] == novaCor)
        return 0;

    (*m)[c.first][c.second] = novaCor;
    return 1;
}

int resolveu (matriz m) {    
    int cont = 0;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++)
            if (m[i][j] != m[0][0]) 
                return 0;
    }

    return 1;
}