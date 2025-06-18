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

class Menu {

    private:
       int fase_atual;
       int fases_desbloqueadas;
       std::vector<std::vector<std::pair<float,float>>> vec_buttons;

       int numbers_menus;
       
    public:
        std::vector<std::vector<GLuint>> vec_buttons_text;
        std::vector<GLuint> vec_menus_text;
        std::vector<std::vector<int>> vec_button_acction;
        Texturas textures;
        void render_menu();
        Menu(char* script_menu, TextLoader* tloader);
        int tratarMouse(int state, float ox, float oy);
        void atualizarfase(int statusjogo);


    

};

