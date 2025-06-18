#pragma once
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

class Vida{
    
    public: 
        bool vida_flag = false;
        double hp;
	    Vida();
        void inicializa();
	    GLuint carregaTextura(const char* arquivo);
        GLuint idTexturaVida;
        void recebeDano(double dano);
        void desenhaVida(double x1, double x2, double y1, double y2);

};