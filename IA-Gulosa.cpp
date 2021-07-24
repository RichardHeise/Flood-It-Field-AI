#include "IA-Gulosa.h"

void showq(deque<coordenada> gq)
{
    deque<coordenada> g = gq;
    while (!g.empty()) {
        printf("%d %d \n", g[0].first, g[0].second);
        g.pop_front();
    }
    cout << '\n';
}

deque<coordenada> descobreBorda (matriz m, int posX, int posY)  {
    
    deque<coordenada> bordas;
    deque<coordenada> visitar;

    coordenada inicio = make_pair(posX,posY);
    visitar.push_back(inicio);

    int corAtual = m[inicio.first][inicio.second];

    while ( !visitar.empty() ) {
        
        
        if ( (visitar[0].first + 1 < m.size()) && (visitar[0].second + 1 < m[0].size()) &&
            !encontraElemento(bordas, make_pair(visitar[0].first + 1, visitar[0].second)) &&
            !encontraElemento(bordas, make_pair(visitar[0].first, visitar[0].second + 1)) &&
            !encontraElemento(visitar, make_pair(visitar[0].first + 1, visitar[0].second)) &&
            !encontraElemento(visitar, make_pair(visitar[0].first, visitar[0].second + 1)) ) {

            if ( !(m[visitar[0].first + 1][visitar[0].second] == corAtual) ) {
                bordas.push_back(make_pair(visitar[0].first + 1, visitar[0].second));
            } else { 
                visitar.push_back(make_pair(visitar[0].first + 1, visitar[0].second));
            }

            if ( !(m[visitar[0].first][visitar[0].second + 1] ==  corAtual) ) {                                                       
                    bordas.push_back(make_pair(visitar[0].first, visitar[0].second + 1));
            } else {
                    visitar.push_back(make_pair(visitar[0].first, visitar[0].second + 1));
            }
            
        }

        if ( (visitar[0].first - 1 >= 0) && (visitar[0].second - 1 >= 0) &&
            !encontraElemento(bordas, make_pair(visitar[0].first - 1, visitar[0].second)) &&
            !encontraElemento(bordas, make_pair(visitar[0].first, visitar[0].second - 1)) &&
            !encontraElemento(visitar, make_pair(visitar[0].first - 1, visitar[0].second)) &&
            !encontraElemento(visitar, make_pair(visitar[0].first, visitar[0].second - 1)) ) { 

            if ( !(m[visitar[0].first -1][visitar[0].second] == corAtual) ) {
                bordas.push_back(make_pair(visitar[0].first - 1, visitar[0].second));

            } else {
                visitar.push_back(make_pair(visitar[0].first - 1, visitar[0].second));
            }
                
            if ( !(m[visitar[0].first][visitar[0].second - 1] == corAtual) ) {
                bordas.push_back(make_pair(visitar[0].first, visitar[0].second - 1));

            } else {
                visitar.push_back(make_pair(visitar[0].first, visitar[0].second - 1));
            }
        }   
    
        printf("visitados: ");
        showq(visitar);
        printf("\n");

        visitar.pop_front();
    }

    printf("visitados: ");
    showq(visitar);
    printf("\n");
    printf("tamanho borda: %lu \n", bordas.size());
    //printf("tem elemento igual: %d \n", encontraElemento(bordas, make_pair(0,0)));
    printf("bordas: ");
    showq(bordas);
    printf("\n");

    return bordas;
}   

int encontraElemento (deque<coordenada> f, coordenada  c) {

    for(int i = 0; i < f.size(); i++) {
        if (c.first == f[i].first && c.second == f[i].second) {
            return 1;
        }
    }
    
    return 0;
}