#pragma once

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <vector>

typedef struct tripla{  

float x, y, z;

} tripla_ordenada;

class Texturas {        



    public:

        std::vector<int> vectext;
        std::vector<tripla_ordenada> coordenadastexturas;
        GLuint texture_index;

        Texturas();
      
};