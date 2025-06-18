#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <vector>
#include <string.h>
#include "Vida.hpp"
using namespace std;
class Personagem
{
private:
    double posicaoX;
    double posicaoY;
    double larguraX;
    double alturaY;
    float velocidade;
    int numDeVidas;
    float hp;
    bool morreu;
    int contDisparos = 0;

public:
    //
    double movX = 0;
    double movY = 0;
    Personagem(double posicaoX,
               double posicaoY,
               double larguraX,
               double alturaY,
               float velocidade,
               int numDeVidas,
               float hp,
               bool morreu
               );
    GLuint idTexturaPersonagem;
    string nomeDoArquivo;
    vector <vector<double>> movimentos;
    //Variaveis de controle de animação//
    int larguraDoSprite;
    int alturaDoSprite;
    bool tomandoDano = false;
    bool desapareceu = false;
    bool atirando = false;
    int segundosDeMorte = 0;
    int segundosDano = 0;
    int segundosAtirando = 0;
    int movimentoAtual = 0;
    int frequenciaDeInvocacao = 0;
    //Variaveis de controle de animação//
    Personagem(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu, int larguraDoSprite, int alturaDoSprite);
    Personagem();
    void verificaVivoMorto();
    double getPosicaoX();
    void setPosicaoX(double x);
    double getPosicaoY();
    void setPosicaoY(double y);
    void desenhaPersonagem(double tX1, double tX2, double tY1, double tY2, double escala);
    void movimentaPersonagem(double tX1, double tX2, double tY1, double tY2, double escala);
    void carregaTextura(const char* arquivo);
    double getLarguraX();
    void setLargurax(double lx);
    double getAlturaY();
    void setAlturay(double ay);
    bool getMorreu();
    void setMorreu(bool m);
    float getVelocidade();
    void setVelocidade(float velocidade);
    int getContDisparos();
    void setContDisparos(int ContDisparos);
    void suavizaMovimento();
    void reapareceInimigo(float life);

    Vida vida;
};
