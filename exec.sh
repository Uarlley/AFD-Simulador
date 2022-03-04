#comando de execucao no linux: nohup ./exec.sh >> saida.txt &

FLAGS=""
rm Teste.txt
g++ -o generator.exe -fconcepts testeGen.cpp
./generator.exe
g++ trabalho1.c
./a.out <Teste.txt
rm generator.exe
rm a.out