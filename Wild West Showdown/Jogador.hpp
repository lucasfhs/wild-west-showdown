#pragma once
#include "Personagem.hpp"
#include "Vida.hpp"
#include <vector>
#include <string.h>
#include "Mundo.hpp"

using namespace std;
class Jogador:public Personagem
{
    /*Inimigo herda de personagem*/

private:
    /**/
    

public:
    /*Define os movimentos do inimigo1*/
    /*Andando*/
    vector<double> mov1 = {0.0 , 0.25, 0.66, 1};
    vector<double> mov2 = {0.25 , 0.5, 0.66, 1};
    vector<double> mov3 = {0.5 , 0.75, 0.66, 1};
    vector<double> mov4 = {0.75 , 1, 0.66, 1};
    /*Andando*/
    /*Atirando*/
    vector<double> mov5 = {0 , 0.25, 0.33, 0.66};
    vector<double> mov6 = {0.25 , 0.5, 0.33, 0.66};
    vector<double> mov7 = {0.5, 0.75, 0.33, 0.66};
    /*Atirando*/
    /*Andando sem arma*/
    //Pode ser adicionado em algum momento de transição de fase
    vector<double> mov8 = {0.75, 1, 0.33, 0.66};
    vector<double> mov9 = {0, 0.25, 0, 0.33};
    vector<double> mov10 = {0.25, 0.5, 0, 0.33};
    vector<double> mov11 = {0.5, 0.75, 0, 0.33};
    /*Andando sem arma*/
    /*Morto*/
    vector<double> mov12 = {0.75, 1, 0, 0.33};
    /*Armazena vidas do Player*/
    std::vector<Vida> vidas;
    /*Armazena a pontuação do Player*/
    int pontuacao;

    void movimentaPersonagem(int movimento, double escala);
    void animacaoAndando();
    void animacaoAtirando();
    void recebeDano(float dano);
    void desenhaVidas();
    void restauraVida();
    GLuint movimentaDL;
    void criaDisplayList();
    void chamaDisplayList();
    Jogador(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu);
    Jogador();
    ~Jogador();

   bool fimDeJogo;
};