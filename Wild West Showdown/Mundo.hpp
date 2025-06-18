#pragma once

#include "TextLoader.hpp"
#include "Texturas.hpp"
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <vector>

#define MAX_LADOS 30

using namespace std;

class Mundo {

    private:
       int fase_atual;
       int fases_desbloqueadas;

       int numbers_parallax;
       
    public:
        std::vector<GLuint> vec_menus_text;
        Texturas textures;
        void render_fase(double posicaoX);
        void render_transicoes(int i);
        Mundo(char* script_menu, TextLoader *tloader);

};