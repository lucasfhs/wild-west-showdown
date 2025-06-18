#include <iostream>
#include "Inimigo2.hpp"
#include <vector>
#include <GL/freeglut.h>
#include <string.h>
using namespace std;


Inimigo2::Inimigo2(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu) : Personagem(posicaoX, posicaoY, larguraX, alturaY, velocidade, numDeVidas, hp, morreu)
{
    this->nomeDoArquivo = "texturas/inimigo2.png";
    /*Atribui valores para os sprites para uso interno*/
    this->larguraDoSprite = 240;
    this->alturaDoSprite = 300;
    /*Carrega a textura pelo construtor*/ 
    this->carregaTextura(nomeDoArquivo.c_str());
    /*Adiciona os movimentos*/
    movimentos.push_back(mov1);
    movimentos.push_back(mov2);
    movimentos.push_back(mov3);
    movimentos.push_back(mov4);
    movimentos.push_back(mov5);
    movimentos.push_back(mov7);
    movimentos.push_back(mov8);
    movimentos.push_back(mov9);
    movimentos.push_back(mov10);
    movimentos.push_back(mov11);
    movimentos.push_back(mov12);
    this->movimentaDL = glGenLists(1);
    criaDisplayList();
    this->dano = 20;

}
void Inimigo2::movimentaPersonagem(int movimento, double escala)

{
    /*Metodo sobrecarregado do movimenta personagem
    Faz com que o personagem em questão se movimente e troque os sprites para gerar animação
    */
    /*Condições que fazem com que o inimigo só ande nos limites da tela*/
    /*Metodo sobrecarregado do movimenta personagem
    Faz com que o personagem em questão se movimente e troque os sprites para gerar animação
    */
    /*Condições que fazem com que o inimigo só ande nos limites da tela*/
    bool condicaoLimiteVertical = !(this->getPosicaoY() + this->movY >= -55) && !(this->getPosicaoY() + this->movY <= -95);
    // bool condicaoLimiteHorizontal = !(this->getPosicaoX() + this->movX >= 70) && !(this->getPosicaoX() + this->movX <= -100);
    bool condicaoLimiteHorizontal = true;
    /*Faz o inimigo sinalizar que tomou dano e também desaparecer*/
    if(this->getMorreu()){
        movimentoAtual = 11;
        this->tomandoDano = true;
        this->segundosDeMorte += 1;
    }
    if(this->atirando == true){
        this->segundosAtirando += 1;
        this->movX = 0;
        this->movY = 0;
        animacaoAtirando();
        glutPostRedisplay();

    }
    /*Movimenta o personagem trocando seus sprites*/
    if((movX != 0 || movY != 0 ) && condicaoLimiteHorizontal && condicaoLimiteVertical && this->getMorreu() == false && this->atirando == false){
        glPushMatrix();
        glTranslatef(movX, movY, 0);
        desenhaPersonagem(this->movimentos[movimento][0],this->movimentos[movimento][1],this->movimentos[movimento][2],this->movimentos[movimento][3],escala);
        this->setPosicaoX(this->getPosicaoX() + movX);
        this->setPosicaoY(this->getPosicaoY() + movY);
        glPopMatrix();
    }
    else if (this->segundosDeMorte <= 120){
    /*Faz com que o personagem que esta morto continue no chão ate o tempo de desaparecer*/
        if(segundosDeMorte == 0){
            desenhaPersonagem(this->movimentos[movimento][0],this->movimentos[movimento][1],this->movimentos[movimento][2],this->movimentos[movimento][3],escala);
        }else{
            desenhaPersonagem(0.75 , 1, 0, 0.2,1);
        }
        
    }else{
    /*Sinaliza para que não desenhe mais o personagem visto que ele morreu*/
        this->desapareceu = true;
        this->frequenciaDeInvocacao += 1;
        reapareceInimigo(60);
    }
}
void Inimigo2::animacaoAndando()
{
    /*Troca os sprites para fornecer a animação de andar*/
    if(this->getMorreu() == false){
        if(movimentoAtual <= 6){
            if(movimentoAtual == 6){
                movimentoAtual = 0;
                
            }else{
                movimentoAtual += 1;
            }
        }
    }else{
        /*Se ele morreu faz com que mantenha o sprite de morte ativado*/
        movimentoAtual = 11;
    }
}
void Inimigo2::animacaoAtirando()
{
    /*Troca os sprites para fornecer animação de atirando*/
    if(frequenciaDeAtaque % 5 == 0){
        if(this->getMorreu() == false && atirando == true){

            if(this->movimentoAtual <= 10 && this->movimentoAtual >= 7){
                if(movimentoAtual == 10){
                    movimentoAtual = 7;
                    
                }else {
                    movimentoAtual++;
                }
            }else{
                movimentoAtual = 7;
            }
    }
    }
    /*Controla os segundos que ele atira*/
    if(this->segundosAtirando >= 35){
        this->atirando = false;
        this->segundosAtirando = 0;
        this->movimentoAtual = 0;
    }

}
void Inimigo2::atiraSozinho()
{
    /*Faz com que o inimigo atire sozinho a partir de um contador*/
    if(this->frequenciaDeAtaque >= 110){
        this->atirando = true;
        this->frequenciaDeAtaque = 0;
    }else{
        this->frequenciaDeAtaque += 1;
    }
}

void Inimigo2::seguePersonagem(double posicaoXP, double posicaoYP)
{
    /*Segue o personagem na tela*/
    /*A função segue personagem trabalha pegando a posição do jogador e movendo o inimigo ate ele através dos outros metodos que fornecem animação e movimento presentes nesse código*/
    atiraSozinho();
    if(atirando == false && !this->getMorreu()){
        if(this->frequenciaDePerseguicao >= 60){
            this->frequenciaDePerseguicao = 0;
            if(this->getPosicaoX() >= -100 && this->getPosicaoX() <= 100.0 && this->getPosicaoX() > posicaoXP){

                this->movX = -this->getVelocidade();
            }
            if(this->getPosicaoY() >= -100 && this->getPosicaoY() <= 100.0)
            {
                if(this->getPosicaoY() > (posicaoYP))
                {
                    this->movY = -this->getVelocidade();
                } 
                if (this->getPosicaoY() < (posicaoYP))
                {
                    this->movY = this->getVelocidade();
                }
            }

        }
        
    }

    this->frequenciaDePerseguicao++;
    animacaoAndando();
    if(this->atirando == false){
        suavizaMovimento();
    }
}
void Inimigo2::criaDisplayList()
{
    /*Cria a display list dependendo da animação*/
    /*Utilizamos display list para cumprir com o requirido no roteiro*/
    glNewList(movimentaDL, GL_COMPILE);
    movimentaPersonagem(this->movimentoAtual , 1);
    glEndList();
}
void Inimigo2::chamaDisplayList()
{
    criaDisplayList();
    glCallList(this->movimentaDL);
}
void Inimigo2::animacaoMorte(int movimento, double escala)
{

}
Inimigo2::Inimigo2()
{
}

Inimigo2::~Inimigo2()
{
}
