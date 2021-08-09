# Trabalho 1 para disciplina de Inteligência Artifical. 

## Descrição:
 - Este trabalho propõe-se a resolver tabuleiros do jogo Flood It (também conhecido como Flood Field ou Flood Fill) utilizando uma inteligência artifical programada em C++.

## O Problema
 - Como visto em aula, uma IA que resolve o Flood Field de maneira ótima -- isto é, sempre com a melhor sequência de jogadas -- pode ser obtida através de um algoritmo como o A*. Acontece que estamos limitados a 8GB de RAM e 2 minutos no máximo de execução de código, ou seja, conclui que seria inviável abrir todas as possibilidades e, portanto, resolvi implementar um algoritmo guloso (greedy) que utiliza-se de uma boa heurística , previsão de jogadas e detecção de possíveis jogadas para chegar a uma solução razoável em tempo hábil.

 ## Código
 ### O código fonte possui três bibliotecas locais: matriz.h, IAra.h e floodlib.h. 
 - Em IAra.h (uma pequena piada com o nome hehe) você encontrará as funções referentes à IA em si.
 - Em matriz.h você encontrará funções referentes ao alocamento e controle de dados de um tabuleiro (matriz de char).
 - Em floodlib.h você encontrará funções referentes à implementação do jogo flood field.

 - Para mais informações aqui recomendo rodar o comando doxygen, que gerará uma documentação automática do código.

## Fluxo
 - Em flood.cpp temos nossa main(), ela chamará a leitura das entradas, do tabuleiro e, por fim, chamará resolve() que resolverá o jogo.
 - A função resolve() executa um laço em que se busca a melhor jogada; joga-se, então, a melhor jogada e guarda esta jogada em uma lista de jogadas que será escrita na tela ao fim.
 - A função que busca a melhor jogada descobrirá, através de outra função, as possíveis jogadas. Em seguida é calculado se haverá previsão de jogadas e quantas deverão ser previstas para cada jogada (essa parte é crucial para o melhor desempenho do código e envolve uma expressão matemática obtida através de testes, mais detalhes no comentário no código em IAra.cpp), logo roda-se um laço para jogadas possíveis, testando-as e guardando a heurística relativa a cada jogada em uma lista que associa cor a uma heurística. Assim que temos todas nossas possíveis jogadas devidamente testadas, escolhemos a de menor score (detalhes da heurística) e a retornamos como sendo a melhor jogada.

 ## Heurística 
  - Há duas heurística aqui: número de regiões do tabuleiro dividido pelo número de cores e distância de cada ponto do tabuleiro referente ao cluster principal. 
  - A primeira heurística conta quantas regiões temos em um tabuleiro e divide esse valor pelo número de cores, dando-nos um valor real que estima quantas áreas faltam ser abertas para resolvermos o tabuleiro.
  - A segunda heurística, e essa sim é nosso "carro chefe", calcula a distância de cada ponto da matriz em relação ao nosso nodo principal, a melhor jogada é a que diminui a maior distância. 

  - Essas heurísticas são somadas, a jogada que tem a menor soma é a melhor. A parte boa da heurística ser um valor real é que não precisamos criar critério de desempate: se duas jogadas diminuem a mesma distância do nodo maais longe, será jogada a que abre mais regiões devido a primeira heurística descrita. Se ainda assim empatamos, então as duas jogadas são boas.

  ## Previsão
   - 
