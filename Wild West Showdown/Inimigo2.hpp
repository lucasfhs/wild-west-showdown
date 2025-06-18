#pragma once
#include "Personagem.hpp"
#include <vector>
#include <string.h>
using namespace std;
class Inimigo2:public Personagem
{
    /*Inimigo herda de personagem*/

private:
    /**/
    

public:
    /*Define os movimentos do inimigo1*/
    /*Andando*/
    vector<double> mov1 = {0.0 , 0.25, 0.8, 1};
    vector<double> mov2 = {0.25 , 0.5, 0.8, 1};
    vector<double> mov3 = {0.5 , 0.75, 0.8, 1};
    vector<double> mov4 = {0.75 , 1, 0.8, 1};
    vector<double> mov5 = {0.0 , 0.25, 0.6, 0.8};
    vector<double> mov6 = {0.25 , 0.5, 0.6, 0.8};
    vector<double> mov7 = {0.5 , 0.75, 0.6, 0.8};
    /*Atirando*/
    vector<double> mov8 = {0.0 , 0.25, 0.4, 0.6};
    vector<double> mov9 = {0.25 , 0.5, 0.4, 0.6};
    vector<double> mov10 = {0.5 , 0.75, 0.4, 0.6};
    vector<double> mov11 = {0.75 , 1, 0.4, 0.6};
    /*Morto*/
    vector<double> mov12 = {0.75 , 1, 0, 0.2};
    int frequenciaDePerseguicao = 0;
    int frequenciaDeAtaque = 0;
    void movimentaPersonagem(int movimento, double escala);
    void animacaoAndando();
    void animacaoMorte(int movimento, double escala);
    void animacaoAtirando();
    void atiraSozinho();
    GLuint movimentaDL;
    void criaDisplayList();
    void chamaDisplayList();
    void seguePersonagem(double posicaoXP , double posicaoYP);
    Inimigo2(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu);
    Inimigo2();
    ~Inimigo2();
    float dano;
};