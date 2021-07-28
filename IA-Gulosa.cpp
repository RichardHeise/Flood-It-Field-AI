#include "IA-Gulosa.h"

void showq(deque<coordenada> gq) {
    deque<coordenada> g = gq;
    while (!g.empty()) {
        printf("%d %d \n", g[0].first, g[0].second);
        g.pop_front();
    }
    cout << '\n';
}

deque<coordenada> descobreBorda (matriz *m, int posX, int posY)  {
    
    deque<coordenada> bordas;
    deque<coordenada> visitados;
    deque<coordenada> visitar;

    coordenada inicio = make_pair(posX,posY);
    visitar.push_front(inicio);

    char corAtual = (*m)[inicio.first][inicio.second];

    while ( !visitar.empty() ) {

        coordenada aux = visitar[0];
        visitar.pop_front();

        if ( !encontraPosicao(visitados, aux) && 
            aux.first >= 0 && aux.first < (*m).size() && aux.second >= 0 && aux.second < (*m)[0].size()) {

            visitados.push_back(aux);

            if ( (*m)[aux.first][aux.second] == corAtual  ) {
                visitar.push_back(make_pair(aux.first + 1, aux.second));
                visitar.push_back(make_pair(aux.first - 1, aux.second));
                visitar.push_back(make_pair(aux.first, aux.second + 1));
                visitar.push_back(make_pair(aux.first, aux.second - 1));
            } else {
                bordas.push_back(aux);
            }  
        }
    }


    return bordas;
}   

int encontraPosicao (deque<coordenada> f, coordenada c) {

    for(int i = 0; i < f.size(); i++) {
        if (c.first == f[i].first && c.second == f[i].second) {
            return 1;
        }
    }
    
    return 0;
}

static int encontraElemento (deque<pair<char, coordenada>> f, char e) {

    for(int i = 0; i < f.size(); i++) {
        if ( e == f[i].first) {
            return 1;
        }
    }
    
    return 0;
}

pair<char, int> escolheCor (matriz *m, coordenada c, deque<coordenada> fb) {

    deque<pair<char, coordenada>> cores;

    for (int i = 0; i < fb.size(); i++) {
        cores.push_back(make_pair( (*m)[fb[i].first][fb[i].second], fb[i] ));
    }

    pair<char, int> melhorCor;

    melhorCor.first = 0;
    melhorCor.second = 0;

    deque<coordenada> maiorCluster;

    for (int i = 0; i < cores.size(); i++) {
        maiorCluster = descobreCluster(m, cores[i].first, cores[i].second);
        if (melhorCor.second < maiorCluster.size() ) {
            melhorCor.first = cores[i].first;
            melhorCor.second = maiorCluster.size();
        }
    }

    return melhorCor;
}

deque<coordenada> descobreCluster (matriz *m, char cor, coordenada inicio) {

    deque<coordenada> cluster;
    deque<coordenada> visitados;
    deque<coordenada> visitar;

    visitar.push_front(inicio);

    while ( !visitar.empty() ) {

        coordenada aux = visitar[0];
        visitar.pop_front();

        if ( !encontraPosicao(visitados, aux) && 
            aux.first >= 0 && aux.first < (*m).size() && aux.second >= 0 && aux.second < (*m)[0].size()) {

            visitados.push_back(aux);

            if ( (*m)[aux.first][aux.second] == cor ) {
                cluster.push_back(aux);
                visitar.push_back(make_pair(aux.first + 1, aux.second));
                visitar.push_back(make_pair(aux.first - 1, aux.second));
                visitar.push_back(make_pair(aux.first, aux.second + 1));
                visitar.push_back(make_pair(aux.first, aux.second - 1));
            } 
        }
    }

    return cluster;

}

deque<char> resolveFlood (matriz m, coordenada c) {

    deque<char> resolucao;
    deque<coordenada> clusterOriginal;

    deque<coordenada> bordaAtual;
    bordaAtual = descobreBorda(&m, c.first, c.second);

    char melhorJogada = escolheCor(&m, c, bordaAtual).first;
    resolucao.push_back(melhorJogada);

    floodFill(&m, melhorJogada);
    if ( !resolveu(m) ) {
        resolveFlood(m, c);
    }


    return resolucao;
}

/*
deque<char> resolveFlood (matriz m, int maxCores) {

    resolveFloodRecursivo(&m, 0, maxCores);
}
*/
