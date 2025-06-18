compilar:
	g++ *.cpp -c -g
	g++ *.o -o main.out -lglut -lGL -lGLU -lSOIL -lm -lglfw -lGLEW -std=c++11
limpar:
	rm *.o -rf
executar: compilar limpar
	-./main.out
	rm main.out
	
