#include "IA-Gulosa.h"

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

char buscaMelhorJogada (matriz m, int cores) {

    deque<pair<char, int>> controle;

    int possivelMaior;
    char melhorCor;
    
    /*
        printf("Profundidade: %d\n", escopos);
        printf("tamanho cores: %lu \n", cores.size());
        for (int w = 0; w < cores.size(); w++)
            printf("cor: %d, posicao: %d %d\n", cores[w].first, cores[w].second.first, cores[w].second.second);
        
        printf("checaBorda vale: %d\n", checaCoresBorda(cores));
        printf("coordenada atual: %d %d\n", coordAtual.first, coordAtual.second);
        printf("Maior Cluster: %d \n", (*maiorCluster));
        printf("Cluster inicial: { \n");
        showq((*clusterInicial));
        printf("}\n");
        printf("bordas: {\n");
        showq(borda);
        printf("}");
        
        borda = descobreBorda(&m, coordAtual.first, coordAtual.second, clusterInicial);
        cores = possiveisCores(&m, coordAtual, borda);
    */

    matriz temp;
    for (int cor = 1; cor <= cores; cor++) {
        temp = m;

        /*
            printf("Cor Atual: %d \n", cores[i].first);
            printf("=============================== \n");
        */

        floodFill(&temp, cor);

        //EscreveMatriz(temp, temp.size(), temp[0].size());

        if ( resolveu(temp) ) {
            return cor;
        }

        //coordAtual = cor;
        possivelMaior = descobreCluster(&temp, (char)cor, make_pair(0,0)).size();

        controle.push_back(make_pair((char)cor, possivelMaior));
    }

    /*
        for (int i =0; i < controle.size(); i++)
            printf("melhor cor: %d\narea: %d\n", controle[i].first, controle[i].second);
        printf("\n");
            showq(clusterInicial);
            for (int i = 0; i < m.size(); i ++) {
            for (int j = 0; j < m[0].size(); j++) {
                if ( encontraPosicao(clusterInicial, make_pair(i,j)) ) {
                    printf("x");
                } else {
                    printf("0");
                }
            }
            printf("\n");
        }
    
    */

    sort(controle.begin(), controle.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    melhorCor = controle.back().first;

    return melhorCor;
}

static void teste (matriz m, int cores) {

    matriz temp_m = m;
    for (int escopos = 0; escopos < MAX_ESCOPOS; escopos++) {

        for (int cor = 1; cor <= cores; cor++) {
            floodFill(&temp_m, cor);

            char jogada = buscaMelhorJogada(temp_m, cores);


        }
    }

}

deque<char> resolveFlood (matriz m, int cores) {

    deque<char> resolucao;
    /*
        deque<coordenada> clusterInicial;
        int maiorCluster = 0;
    */

    printf("melhor jogada: %d\n", buscaMelhorJogada(m, cores));

    return resolucao;

}
