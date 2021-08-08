#include "IAra.h"

vector<char> possiveisCores (matriz m) {
    
    vector<char> bordas;
    int controle = 0;
    floodFill(&m, 0, make_pair(0,0));

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

            if (m[i][j] != 0) {
                vector<coordenada> lista;

                lista.push_back(make_pair(i,j));
                char corAnt = m[i][j];

                while (!lista.empty()) {
                    coordenada aux = lista.back();
                    lista.pop_back();

                    if ( flood(&m, aux, corAnt, 0) ) {

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

float preveJogada (matriz m, int cores, int max_escopos) {

    vector<pair<char, float>> controle;
    matriz temp_m = m;

    if ( resolveu(temp_m) ) return 0;

    for (int escopos = 0; escopos < max_escopos; escopos++) {

        if ( resolveu(temp_m) ) break;
        controle.clear();

        vector<char> coresBorda = possiveisCores(temp_m); 

        for (char cor : coresBorda) {
            if (cor != temp_m[0][0]) {

                matriz aux = temp_m;
                
                floodFill(&aux, cor, make_pair(0,0));

                if ( resolveu(temp_m) ) break;

                controle.push_back(make_pair(cor, (float)escopos + h(aux, cores)));
            }
        }

        sort(controle.begin(), controle.end(), [](auto &left, auto &right) {
            return left.second < right.second;
        });

        floodFill(&temp_m, controle.front().first, make_pair(0,0));
    }
    

    return controle.front().second;
}   

char buscaMelhorJogada (matriz m, int cores) {

    vector<pair<char, float>> controle;
    vector<char> coresBorda = possiveisCores(m);

    int previsoes = (-4.796l*log(coresBorda.size()) + 14.715);

    if (previsoes) {
        for (char cor : coresBorda) {
            if (cor != m[0][0]) {
                
                float heuristica;

                matriz temp_m = m;
                floodFill(&temp_m, cor, make_pair(0,0));

                heuristica = preveJogada(temp_m, cores, previsoes);
                
                controle.push_back(make_pair(cor, heuristica));
            }
        }        
    } else {
        for (char cor : coresBorda) {
            if (cor != m[0][0]) {
                
                float heuristica;

                matriz temp_m = m;
                floodFill(&temp_m, cor, make_pair(0,0));

                heuristica = h(temp_m, cores);
                
                controle.push_back(make_pair(cor, heuristica));
            }
        }
    }

    sort(controle.begin(), controle.end(), [](auto &left, auto &right) {
        return left.second < right.second;
    });

    return controle.front().first;        
}


void resolve (matriz m, int cores) {

    vector<char> jogadas;


    while ( !resolveu(m) ) {
        
        char melhorJogada = buscaMelhorJogada(m, cores);
        floodFill(&m, melhorJogada, make_pair(0,0));
        jogadas.push_back(melhorJogada);
       
    }

    printf("%lu\n", jogadas.size());
    for (int i = 0; i < jogadas.size(); i++)
        printf("%d ", jogadas[i]);
    printf("\n");

}
