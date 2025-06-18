#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include "Personagem.hpp"

class Disparo
{
private:
    double disparoX;
    double disparoY;
    bool disparou;
public:
    GLuint idTexturaBala;
    GLuint idTexturaCanhao;
    GLuint idTexturaMachado;
    string nomeDoArquivoBala;
    string nomeDoArquivoCanhao;
    string nomeDoArquivoMachado;
    int tamanhoDaBala;
    Disparo(bool disparou);
    ~Disparo();
    double getDisparoX();
    void setDisparoX(double x);
    double getDisparoY();
    void setDisparoY(double y);
    void desenhaTiro();
    void desenhaTiroCanhao();
    void desenhaTiroMachado();
    void carregaTextura(const char *arquivo);
    void carregaTexturas();
    GLuint DisplayListBala;
    GLuint DisplayListMachado;
    GLuint DisplayListCanhao;
    void criaDisplayList();
    void chamaDisplayList(int i);
    bool getDisparou();
    void setDisparou(bool t);
    void desenhaTiroParaDl();
    void desenhaCanhaoParaDl();
    void desenhaMachadoParaDl();
    static void limpaTiros(std::vector<Disparo> &projeteis, Personagem &p);
    static void projetil(std::vector<Disparo> &projeteis, GLfloat &aspectRatio, Personagem &p, double velocidade);


};


