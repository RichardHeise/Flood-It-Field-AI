for k in {4..20}; do
	echo "com "$k"cores: "
	echo " "
	for i in {1..5}; do
		echo "rodada"$i
    ./fabiano/geramapa 100 100 $k  > text.txt
    time ./flood < text.txt 
	done 
done

