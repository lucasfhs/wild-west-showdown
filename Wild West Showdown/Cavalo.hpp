#pragma once
#include "Personagem.hpp"
#include <vector>
#include <string.h>
using namespace std;
class Cavalo:public Personagem
{
    /*Inimigo herda de personagem*/

private:
    /**/
    

public:
    /*Define os movimentos do inimigo1*/
    /*Andando*/
    vector<double> mov1 = {0.0 , 0.5, 0.66, 1};
    vector<double> mov2 = {0.5 , 1, 0.66, 1};
    vector<double> mov3 = {0.0 , 0.5, 0.33, 0.66};
    vector<double> mov4 = {0.5 , 1, 0.33, 0.66};
    vector<double> mov5 = {0.0 , 0.5, 0.0, 0.33};
    vector<double> mov6 = {0.5 , 1, 0.0, 0.33};
    int frequenciaDePerseguicao = 0;
    int frequenciaDeAtaque = 0;
    bool atingiu = false;
    bool morreu_sozinho = false;
    void movimentaPersonagem(int movimento, double escala);
    void animacaoAndando();
    void seguePersonagem(double posicaoXP , double posicaoYP);
    Cavalo(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu);
    GLuint movimentaDL;
    void criaDisplayList();
    void chamaDisplayList();
    Cavalo();
    ~Cavalo();

    float dano;
};