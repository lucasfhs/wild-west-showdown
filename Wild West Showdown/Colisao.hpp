#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <vector>
#include <iostream>
#include "Personagem.hpp"
#include "Cavalo.hpp"
#include "Jogador.hpp"
#include "Disparo.hpp"
#include "math.h"

bool colidiu(std::vector<Disparo> &d, Personagem &p);
bool colisaoComCavalo(Cavalo &d, Jogador &p);