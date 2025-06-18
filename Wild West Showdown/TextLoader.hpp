#pragma once

//#include "Texturas.hpp"
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <vector>
#include <map>



class TextLoader{

    private:
        std::map<std::string,int> text_map;

    public:
        TextLoader(char* texturas);
        GLuint getTexture(std::string text_key);


};