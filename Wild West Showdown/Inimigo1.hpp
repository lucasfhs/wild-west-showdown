#pragma once
#include "Personagem.hpp"
#include <vector>
#include <string.h>
using namespace std;
class Inimigo1:public Personagem
{
    /*Inimigo herda de personagem*/

private:
    /**/
    

public:
    /*Define os movimentos do inimigo1*/
    /*Andando*/
    vector<double> mov1 = {0.0 , 0.33, 0.75, 1};
    vector<double> mov2 = {0.33 , 0.66, 0.75, 1};
    vector<double> mov3 = {0.66 , 0.99, 0.75, 1};
    vector<double> mov4 = {0.0 , 0.33, 0.5, 0.75};
    vector<double> mov5 = {0.33 , 0.66, 0.5, 0.75};
    vector<double> mov6 = {0.66 , 0.99, 0.5, 0.75};
    vector<double> mov7 = {0 , 0.33, 0.25, 0.5};
    /*Atirando*/
    vector<double> mov8 = {0.33 , 0.66, 0.25, 0.5};
    vector<double> mov9 = {0.66 , 0.99, 0.25, 0.5};
    vector<double> mov10 = {0 , 0.33, 0, 0.25};
    /*Morto*/
    vector<double> mov11 = {0.33 , 0.66, 0, 0.25};    
    int frequenciaDePerseguicao = 0;
    int frequenciaDeAtaque = 0;
    void movimentaPersonagem(int movimento, double escala);
    void animacaoAndando();
    void animacaoMorte(int movimento, double escala);
    void animacaoAtirando();
    void atiraSozinho();
    void seguePersonagem(double posicaoXP , double posicaoYP);
    GLuint movimentaDL;
    void criaDisplayList();
    void chamaDisplayList();
    Inimigo1(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu);
    Inimigo1();
    ~Inimigo1();
    float dano;
    
};