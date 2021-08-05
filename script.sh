for i in {1..5}; do
    ./fabiano/geramapa 100 100 20  > text.txt
    time ./flood < text.txt > solucao_$i.sh 2> tempo_$i.txt
    echo " " > tempo_$i.txt 
    echo " " > solucao_$i.txt 
done

