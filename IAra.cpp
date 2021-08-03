#include "IAra.h"

void showq(deque<coordenada> gq) {
    deque<coordenada> g = gq;
    while (!g.empty()) {
        printf("%d %d \n", g[0].first, g[0].second);
        g.pop_front();
    }
    cout << '\n';
}

static float h(matriz m, int cores) {

    int regioes = 0;
    matriz distancias = m;
    floodFill(&distancias, 0, make_pair(0,0));
    int maiorDist = 0;

    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++) {

            if (distancias[i][j] != 0) {
                if (i-1 >= 0 && i-1 < distancias.size() && j-1 >= 0 && j-1 < distancias[0].size()) {
                    distancias[i][j] = min(distancias[i-1][j], distancias[i][j-1]) + 1; 

                } else if ( i-1 >= 0 && i-1 < distancias.size() ) {
                    distancias[i][j] = distancias[i-1][j] + 1; 

                } else if ( j-1 >= 0 && j-1 < distancias[0].size() ) {
                    distancias[i][j] = distancias[i][j-1] + 1; 
                } 
                if (distancias[i][j] > maiorDist)
                    maiorDist = distancias[i][j];
            }

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
    return (((float) regioes / (float) cores) + (float)maiorDist);
}

static char preveJogada (matriz m, int cores) {
    
    deque<pair<char, float>> controle;
    matriz temp_m;

    if ( resolveu(m) ) {
        return 0;
    }

    for (int escopos = 0; escopos < MAX_ESCOPOS; escopos++) {

        for (int cor = 1; cor <= cores; cor++) {
            temp_m = m;

            if (cor != temp_m[0][0]) {
                floodFill(&temp_m, cor, make_pair(0,0));

                controle.push_back(h(temp_m, cores));
            }
        }

    } 

    sort(controle.begin(), controle.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    return controle.front().first;
}   

char buscaMelhorJogada (matriz m, int cores) {

    deque<pair<char, float>> controle;

    int corAtual = m[0][0];
    
    for (int cor = 1; cor <= cores; cor++) {
        if (cor != corAtual) {
            float heuristica;

            matriz temp_m = m;
            floodFill(&temp_m, cor, make_pair(0,0));

            heuristica = h(temp_m, cores);
            
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
        char melhorJogada = preveJogada(m, cores);
        /*
            printf("melhor jogada: %d\n", melhorJogada);
            EscreveMatriz(m);
            printf("\n");
        */
        floodFill(&m, melhorJogada, make_pair(0,0));
        jogadas.push_back(melhorJogada);
        //if ( i == 1) exit(0);
        i++;
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

