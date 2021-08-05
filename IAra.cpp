#include "IAra.h"

static void showq(deque<coordenada> gq) {
    deque<coordenada> g = gq;
    while (!g.empty()) {
        printf("%d %d \n", g[0].first, g[0].second);
        g.pop_front();
    }
    cout << '\n';
}

vector<char> possiveisCores (matriz m) {
    
    vector<char> bordas;
    int controle = 0;
    floodFill(&m, 0, make_pair(0,0));

    /*
        EscreveMatriz(m);
        printf("\n");
    */
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[0].size(); j++) {
            if (m[i][j] != m[0][0]) {
                if (j-1 >= 0 && m[i][j-1] == 0) {
                    bordas.push_back(m[i][j]); 
                    controle = 0;
                } else if (i-1 >= 0 && m[i-1][j] == 0) {
                    bordas.push_back(m[i][j]);
                    controle = 0;
                }
                controle++;
            } 
        }
        if (controle == m[0].size() ) break;
    }

    sort(bordas.begin(), bordas.end(), [](auto &left, auto &right) {
        return left < right;
    });

    vector<char>::iterator it;
    it = unique(bordas.begin(), bordas.begin() + bordas.size());

    bordas.resize( distance(bordas.begin(), it) );

    return bordas;
}

float h(matriz m, int cores) {

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

float preveJogada (matriz m, int cores) {

    deque<pair<char, float>> controle;
    matriz temp_m = m;

    if ( resolveu(temp_m) ) return 0;

    for (int escopos = 0; escopos < MAX_ESCOPOS; escopos++) {

        if ( resolveu(temp_m) ) break;
        controle.clear();

        vector<char> coresBorda = possiveisCores(temp_m); 
        for (int i = 0; i < coresBorda.size(); i++) {
            if (coresBorda[i] != temp_m[0][0]) {

                matriz aux = temp_m;
                if ( resolveu(temp_m) ) break;
                floodFill(&aux, coresBorda[i], make_pair(0,0));

                controle.push_back(make_pair(coresBorda[i], (float)escopos + h(aux, cores)));
            }
        }

        sort(controle.begin(), controle.end(), [](auto &left, auto &right) {
            return left.second < right.second;
        });
        /*
        for (int i = 0; i < controle.size(); i++)
            printf("cor: %d, heuristca: %f\n", controle[i].first, controle[i].second);

        printf("menor: %d\n", controle.front().first);
        */
        floodFill(&temp_m, controle.front().first, make_pair(0,0));
    }

    sort(controle.begin(), controle.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    //printf("mano voltou isso: %d\n", controle.front().first);

    return controle.front().second;
}   

char buscaMelhorJogada (matriz m, int cores) {

    deque<pair<char, float>> controle;
    vector<char> coresBorda = possiveisCores(m);

    int corAtual = m[0][0];
    /*
    for (int i = 0; i < coresBorda.size(); i++)
        printf("cores: %d\n", coresBorda[i]);
    */
    for (int i = 0; i < coresBorda.size(); i++) {
        if (coresBorda[i] != corAtual) {
            
            float heuristica;

            matriz temp_m = m;
            floodFill(&temp_m, coresBorda[i], make_pair(0,0));

            heuristica = preveJogada(temp_m, cores);
            
            controle.push_back(make_pair(coresBorda[i], heuristica));
        }
    }

    
    sort(controle.begin(), controle.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    /*
    for (int i = 0; i < controle.size(); i++)
        printf("cor: %d, heuristca: %f\n", controle[i].first, controle[i].second);
    */
    return controle.front().first;        
}

vector<char> resolve (matriz m, int cores) {

    vector<char> jogadas;

    int i = 0;
    while ( !resolveu(m) ) {
        //printf("jogada %d\n", i+1);
        char melhorJogada = buscaMelhorJogada(m, cores);
        floodFill(&m, melhorJogada, make_pair(0,0));
        /*
            printf("melhor jogada: %d\n", melhorJogada);
            EscreveMatriz(m);
            printf("\n");
        */
        jogadas.push_back(melhorJogada);
        //if ( i == 5) exit(0);
        i++;
    }
    

    return jogadas;
}

vector<char> resolveFlood (matriz *m, int cores) {

    vector<char> resolucao;

    resolucao = resolve((*m), cores);

    printf("%lu\n", resolucao.size());
    for (int i = 0; i < resolucao.size(); i++)
        printf("%d ", resolucao[i]);
    printf("\n");

    return resolucao;

}
