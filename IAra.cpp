#include "IAra.h"

void showq(deque<coordenada> gq) {
    deque<coordenada> g = gq;
    while (!g.empty()) {
        printf("%d %d \n", g[0].first, g[0].second);
        g.pop_front();
    }
    cout << '\n';
}

deque<coordenada> descobreBorda (matriz *m, int posX, int posY, deque<coordenada> *ci)  {
    
    deque<coordenada> bordas;
    deque<coordenada> visitados = (*ci);
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

            if ( (*m)[aux.first][aux.second] == corAtual ) {
                (*ci).push_back(aux);
                visitar.push_back(make_pair(aux.first + 1, aux.second));
                visitar.push_back(make_pair(aux.first - 1, aux.second));
                visitar.push_back(make_pair(aux.first, aux.second + 1));
                visitar.push_back(make_pair(aux.first, aux.second - 1));
            } else {
                bordas.push_back(aux);
            }  
        }
    }

    (*ci) = visitados;

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

static int encontraElementoCor (deque<pair<char, coordenada>> f, char e) {

    for(int i = 0; i < f.size(); i++) {
        if ( e == f[i].first) {
            return 1;
        }
    }
    
    return 0;
}

static int encontraElementoChar (deque<char> f, char e) {

    for(int i = 0; i < f.size(); i++) {
        if ( e == f[i]) {
            return 1;
        }
    }
    
    return 0;
}

deque<pair<char, coordenada>> possiveisCores (matriz *m, coordenada c, deque<coordenada> fb) {

    deque<pair<char, coordenada>> cores;

    for (int i = 0; i < fb.size(); i++) {
        cores.push_back(make_pair( (*m)[fb[i].first][fb[i].second], fb[i] ));
    }

    return cores;
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

int checaCoresBorda(deque<pair<char, coordenada>> cores) {

    deque<char> aux;
    for (int i = 0; i < cores.size(); i++) {
            //printf("cor: %d, posicao: %d %d\n", cores[i].first, cores[i].second.first, cores[i].second.second);
            //printf("valor: %d \n", encontraElementoCor(cores, cores[i].first));

        if ( !encontraElementoChar(aux, cores[i].first) ) {
            aux.push_back(cores[i].first);
        }
    }
    /*
        for (int i = 0; i < aux.size(); i++) {
            printf("elemento: %d \n", aux[i]);
        }
    */
    if (aux.size() > 1) return 0;

    return 1;
}

static pair<char, int> descobreDistancia(matriz m, coordenada c, deque<coordenada> cluster) {

    deque<pair<int, int>> contaCores;

    contaCores.push_back(make_pair(BAIXO, 0));
    contaCores.push_back(make_pair(DIREITA, 0));
    contaCores.push_back(make_pair(ESQUERDA, 0));
    contaCores.push_back(make_pair(CIMA, 0));

    for (int i = 1; i < m.size() - c.first; i++) {
        if ( m[c.first + i][c.second] != m[c.first + i - 1][c.second] ) {
            contaCores[0].second += 1;
        }
    }

    for (int i = 1; i < m[0].size() - c.second; i++) {
        if ( m[c.first][c.second + i] != m[c.first][c.second + i - 1] ) {
            contaCores[1].second += 1;

        }
    }

    for (int i = 0; i < c.first; i++) {
        if ( m[c.first - i][c.second] != m[c.first - i + 1][c.second] ) {
            contaCores[2].second += 1;

        }
    }

    for (int i = 0; i < c.second; i++) {
        if ( m[c.first][c.second - i] != m[c.first][c.second - i + 1] ) {
            contaCores[3].second += 1;

        }
    }

    sort(contaCores.begin(), contaCores.end(), [](auto &left, auto &right) {
        return left.second > right.second;
    });

    /*    
    for (int j = 0; j < contaCores.size(); j++) {
        printf("%d %d\n", contaCores[j].first, contaCores[j].second);
    }
    printf("\n");
    */

    if ( contaCores.front().first == BAIXO ) {
        return make_pair(m[c.first + 1][c.second], contaCores.front().second);
    } else if (contaCores.front().first == DIREITA) {
        return make_pair(m[c.first][c.second + 1], contaCores.front().second);
    } else if (contaCores.front().first == CIMA) { 
        return make_pair(m[c.first - 1][c.second], contaCores.front().second);
    } else {
        return make_pair(m[c.first][c.second - 1], contaCores.front().second);
    }

}

static float h(matriz m, int cores) {

    int regioes = 0;
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++) {

            char cor = m[i][j];
            if (cor != 0) {
                deque<coordenada> lista;

                lista.push_back(make_pair(i,j));
                char corAnt = m[i][j];

                while (!lista.empty()) {
                    coordenada aux = lista.back();
                    lista.pop_back();

                    if ( flood(&m, aux.first, aux.second, corAnt, 0) ) {

                        lista.push_back(make_pair(aux.first+1, aux.second));
                        lista.push_back(make_pair(aux.first-1, aux.second));
                        lista.push_back(make_pair(aux.first, aux.second+1));
                        lista.push_back(make_pair(aux.first, aux.second-1));
                        
                    }
                }

                regioes++;
            }
        }
    }
    return (float) regioes / (float) cores;
}

static float preveJogada (matriz m, int cores, int escopos) {
    
    deque<float> controle;
    matriz temp_m = m;

    if ( resolveu(m) ) {
        return 0;
    }

    if (escopos < MAX_ESCOPOS) {
        temp_m = temp_m;

        for (int cor = 1; cor <= cores; cor++) {
            temp_m = m;

            if (cor != temp_m[0][0]) {
                floodFill(&temp_m, cor, make_pair(0,0));

                controle.push_back(h(temp_m, cores));
            }
        }

    }
    

    sort(controle.begin(), controle.end(), [](auto &left, auto &right) {
        return left < right;
    });

    return controle.front();
}   

static char buscaMelhorJogada (matriz m, int cores) {

    deque<pair<char, float>> controle;

    int corAtual = m[0][0];
    
    for (int cor = 1; cor <= cores; cor++) {
        if (cor != corAtual) {
            float heuristica;

            matriz temp_m = m;
            floodFill(&temp_m, cor, make_pair(0,0));

            heuristica = preveJogada(temp_m, cores, 0);
            
            //printf("cor: %d heuristica: %f\n", cor, heuristica);
            controle.push_back(make_pair(cor, heuristica));
        }
    }
    sort(controle.begin(), controle.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    return controle.front().first;        
}

static vector<char> resolve (matriz m, int cores) {

    vector<char> jogadas;

    int i = 0;
    while ( !resolveu(m) ) {
        //printf("jogada %d\n", i);
        char melhorJogada = buscaMelhorJogada(m, cores);
        /*
            printf("melhor jogada: %d\n", melhorJogada);
            EscreveMatriz(m);
            printf("\n");
        */
        floodFill(&m, melhorJogada, make_pair(0,0));
        jogadas.push_back(melhorJogada);
        
    }
    

    return jogadas;
}

vector<char> resolveFlood (matriz *m, int cores) {

    vector<char> resolucao;

    resolucao = resolve((*m), cores);

    printf("tamanho: %lu\n", resolucao.size());
    for (int i = 0; i < resolucao.size(); i++)
        printf("%d ", resolucao[i]);
    printf("\n");

    return resolucao;

}

