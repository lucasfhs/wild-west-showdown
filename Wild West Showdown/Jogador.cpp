#include <iostream>
#include "Jogador.hpp"
//#include "TexturasPersonagens.hpp"
#include "TextLoader.hpp"
#include <vector>
#include <GL/freeglut.h>
#include <string.h>
using namespace std;


Jogador::Jogador(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu) : Personagem(posicaoX, posicaoY, larguraX, alturaY, velocidade, numDeVidas, hp, morreu)
{
    this->nomeDoArquivo = "texturas/jogador.png";
    /*Atribui valores para os sprites para uso interno*/
    this->larguraDoSprite = 200;
    this->alturaDoSprite = 165;
    /*Inicializa a pontuação*/
    this->pontuacao = 0;
    /*Carrega a textura pelo construtor*/ 
    this->carregaTextura(nomeDoArquivo.c_str());
    /*Adiciona os movimentos*/
    movimentos.push_back(mov1);
    movimentos.push_back(mov2);
    movimentos.push_back(mov3);
    movimentos.push_back(mov4);
    movimentos.push_back(mov5);
    movimentos.push_back(mov6);
    movimentos.push_back(mov7);
    movimentos.push_back(mov8);
    movimentos.push_back(mov9);
    movimentos.push_back(mov10);
    movimentos.push_back(mov11);
    movimentos.push_back(mov12);

    Vida vida1;
    Vida vida2;
    Vida vida3;

    this->vidas.push_back(vida1);
    this->vidas.push_back(vida2);
    this->vidas.push_back(vida3);

    this->fimDeJogo = false;
    this->movimentaDL = glGenLists(1);
    criaDisplayList();
    

}
void Jogador::movimentaPersonagem(int movimento, double escala)

{
    /*Metodo sobrecarregado do movimenta personagem
    Faz com que o personagem em questão se movimente e troque os sprites para gerar animação
    */
    /*Condições que fazem com que o inimigo só ande nos limites da tela*/
    bool condicaoLimiteVertical = (this->getPosicaoY() + movY) < (glutGet(GLUT_WINDOW_HEIGHT) - this->alturaDoSprite) && (this->getPosicaoY() + movY) > 0;
    bool condicaoLimiteHorizontal = (this->getPosicaoX() + movX) < (glutGet(GLUT_WINDOW_WIDTH) - this->larguraDoSprite) && (this->getPosicaoX() + movX) > 0;
    /*Faz o inimigo sinalizar que tomou dano e também desaparecer*/
    if(this->getMorreu()){
        movimentoAtual = 11;
        this->tomandoDano = true;
        this->segundosDeMorte += 1;
    }
    if(this->atirando == true){
        this->segundosAtirando += 1;
        animacaoAtirando();
    }
    /*Movimenta o personagem trocando seus sprites*/
    if((movX != 0 || movY != 0 ) && this->getMorreu() == false && this->atirando == false){
        glPushMatrix();
        glTranslatef(movX, movY, 0);
        desenhaPersonagem(this->movimentos[movimento][0],this->movimentos[movimento][1],this->movimentos[movimento][2],this->movimentos[movimento][3],escala);
        this->setPosicaoX(this->getPosicaoX() + movX);
        this->setPosicaoY(this->getPosicaoY() + movY);
        glPopMatrix();
    }
    else if (this->segundosDeMorte <= 120){
    /*Faz com que o personagem que esta morto continue no chão ate o tempo de desaparecer*/
        desenhaPersonagem(this->movimentos[movimento][0],this->movimentos[movimento][1],this->movimentos[movimento][2],this->movimentos[movimento][3],escala);
    }else{
    /*Sinaliza para que não desenhe mais o personagem visto que ele morreu*/
        this->desapareceu = true;
        this->fimDeJogo = true;
    }

}
void Jogador::animacaoAndando()
{
    
    /*Troca os sprites para fornecer a animação de andar*/
    if(this->getMorreu() == false && atirando == false && (this->movX !=0 || this->movY != 0)){
        if(movimentoAtual <= 3){
            if(movimentoAtual == 3){
                movimentoAtual = 0;
                
            }else {
                movimentoAtual += 1;
            }
        }
    }else if (this->getMorreu() == true) {
        /*Se ele morreu faz com que mantenha o sprite de morte ativado*/
        movimentoAtual = 11;
    }
}
void Jogador::animacaoAtirando()
{
    /*Troca os sprites para fornecer animação de atirando*/
    if(this->getMorreu() == false && atirando == true){

        if(this->movimentoAtual <= 6 && this->movimentoAtual >= 4){
            if(movimentoAtual == 6){
                movimentoAtual = 4;
                
            }else {
                movimentoAtual++;
            }
        }else{
            movimentoAtual = 4;
        }
    }
    if(this->segundosAtirando >= 10){
        /*Controla o tempo que a unidade atira*/
        this->atirando = false;
        this->segundosAtirando = 0;
        this->movimentoAtual = 0;
    }

}

void Jogador::recebeDano(float dano){ //esse método recebe o dano causado por tiros inimigos e subtrai tal valor dos pontos de vida do personagem

    /*caso uma das vidas já tenha sido zerada, o dano é subtraido na vida seguinte e, se as três vidas já tiverem sido perdidas,
      o status do fim de jogo é ativado e a tela de game over é exibida
    */
    this->tomandoDano = true;

    if(this->vidas.at(0).hp>0){
        this->vidas.at(0).recebeDano(dano);
    }

    else if(this->vidas.at(1).hp>0){
        this->vidas.at(1).recebeDano(dano);
    }

    else if(this->vidas.at(2).hp>0){
        this->vidas.at(2).recebeDano(dano);
    }

    if(this->vidas.at(0).hp<=0 && this->vidas.at(1).hp<=0 && this->vidas.at(2).hp<=0)
    {
        this->setMorreu(true);
    }

}
void Jogador::restauraVida()
{
    //faz com que o personagem tenha sua vida completa novamente
    this->vidas.at(0).hp = 100;
    this->vidas.at(1).hp = 100;
    this->vidas.at(2).hp = 100;
}

void Jogador::desenhaVidas(){ //esse método desenha os 3 corações de vida do jogador na tela

    this->vidas.at(2).desenhaVida(0.0, 15.0, 40.0, 90.0);
    this->vidas.at(1).desenhaVida(17.0, 32.0,  40.0, 90.0);
    this->vidas.at(0).desenhaVida(35.0, 50.0, 40.0, 90.0);

}
void Jogador::criaDisplayList()
{
    /*Cria a display list dependendo da animação*/
    /*Utilizamos display list para cumprir com o requirido no roteiro*/
    glNewList(movimentaDL, GL_COMPILE);
    movimentaPersonagem(this->movimentoAtual , 1);
    glEndList();
}
void Jogador::chamaDisplayList()
{
    criaDisplayList();
    glCallList(this->movimentaDL);
}
Jogador::Jogador()
{
}

Jogador::~Jogador()
{
}


