#pragma once
#include "Personagem.hpp"
#include <vector>
#include <string.h>
using namespace std;
class Chefe:public Personagem
{
    /*Inimigo herda de personagem*/

private:
    /**/
    

public:
    /*Define os movimentos do inimigo1*/
    /*Andando*/
    vector<double> mov1 = {0.0 , 0.25, 0.75, 1};
    vector<double> mov2 = {0.25 , 0.5, 0.75, 1};
    vector<double> mov3 = {0.5 , 0.75, 0.75, 1};
    vector<double> mov4 = {0.75 , 1, 0.75, 1};
    vector<double> mov5 = {0 , 0.25, 0.5, 0.75};
    /*Atirando*/ 
    vector<double> mov6 = {0.25 , 0.5, 0.5, 0.75};
    vector<double> mov7 = {0.5 , 0.75, 0.5, 0.75};
    vector<double> mov8 = {0.75 , 1, 0.5, 0.75};
    vector<double> mov9 = {0 , 0.25, 0.25, 0.5};
    /*Defesa*/
    vector<double> mov10 = {0.25 , 0.5, 0.25, 0.5};
    vector<double> mov11 = {0.5 , 0.75, 0.25, 0.5};
    vector<double> mov12 = {0.75 , 1, 0.25, 0.5};
    vector<double> mov13 = {0 , 0.25, 0, 0.25};  
    /*Morto*/
    vector<double> mov14 = {0.25 , 0.5, 0, 0.25};    

    int frequenciaDePerseguicao = 0;
    int frequenciaDeAtaque = 0;
    void movimentaPersonagem(int movimento, double escala);
    void animacaoAndando();
    void animacaoAtirando();
    void atiraSozinho();
    void seguePersonagem(double posicaoXP , double posicaoYP);
    GLuint movimentaDL;
    void criaDisplayList();
    void chamaDisplayList();
    Chefe(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu);
    Chefe();
    ~Chefe();
    /*Variável para definir o dano padrao da unidade*/
    float dano;
};