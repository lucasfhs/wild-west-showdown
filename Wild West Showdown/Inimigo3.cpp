#include <iostream>
#include "Inimigo3.hpp"
#include <vector>
#include <GL/freeglut.h>
#include <string.h>
using namespace std;


Inimigo3::Inimigo3(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu) : Personagem(posicaoX, posicaoY, larguraX, alturaY, velocidade, numDeVidas, hp, morreu)
{
    this->nomeDoArquivo = "texturas/inimigo3.png";
    /*Atribui valores para os sprites para uso interno*/
    this->larguraDoSprite = 360;
    this->alturaDoSprite = 360;
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
    movimentos.push_back(mov13);
    movimentos.push_back(mov14);
    movimentos.push_back(mov15);
    this->movimentaDL = glGenLists(1);
    criaDisplayList();

    this->dano = 35;


}
void Inimigo3::movimentaPersonagem(int movimento, double escala)

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
        movimentoAtual = 14;
        this->tomandoDano = true;
        this->segundosDeMorte += 1;
    }
    if(this->atirando == true){
        this->segundosAtirando += 1;
        this->movX = 0;
        this->movY = 0;
        animacaoAtirando();
       //// glutPostRedisplay();

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
            desenhaPersonagem(0.5 , 0.75, 0, 0.25, 1);
        }
        
    }else{
    /*Sinaliza para que não desenhe mais o personagem visto que ele morreu*/
        this->desapareceu = true;
        this->frequenciaDeInvocacao += 1;
        reapareceInimigo(40);
    }
}
void Inimigo3::animacaoAndando()
{
    /*Troca os sprites para fornecer a animação de andar*/
    if(this->getMorreu() == false){
        if(movimentoAtual <= 8){
            if(movimentoAtual == 8){
                movimentoAtual = 0;
                
            }else{
                movimentoAtual += 1;
            }
        }
    }else{
        /*Se ele morreu faz com que mantenha o sprite de morte ativado*/
        movimentoAtual = 14;
    }
}
void Inimigo3::animacaoAtirando()
{
    /*Troca os sprites para fornecer uma animação de tiro*/
    if(frequenciaDeAtaque % 5 == 0){
        if(this->getMorreu() == false && atirando == true){

            if(this->movimentoAtual <= 13 && this->movimentoAtual >= 9){
                if(movimentoAtual == 13){
                    movimentoAtual = 9;
                    
                }else {
                    movimentoAtual++;
                }
            }else{
                movimentoAtual = 9;
            }
    }
    }

    if(this->segundosAtirando >= 35){
        /*Controla o tempo que a unidade atira*/
        this->atirando = false;
        this->segundosAtirando = 0;
        this->movimentoAtual = 0;
    }

}
void Inimigo3::atiraSozinho()
{
    /*Diz a unidade quando atirar através de um contador*/
    if(this->frequenciaDeAtaque >= 160){
        this->atirando = true;
        this->frequenciaDeAtaque = 0;
    }else{
        this->frequenciaDeAtaque += 1;
    }
}
void Inimigo3::seguePersonagem(double posicaoXP, double posicaoYP)
{
    /*Segue o personagem na tela*/
       /*A função segue personagem trabalha pegando a posição do jogador e movendo o inimigo ate ele através dos outros metodos que fornecem animação e movimento presentes nesse código*/
    atiraSozinho();
    if(atirando == false && !this->getMorreu()){
        if(this->frequenciaDePerseguicao >= 35){
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
void Inimigo3::criaDisplayList()
{
    /*Cria a display list dependendo da animação*/
    /*Utilizamos display list para cumprir com o requirido no roteiro*/
    glNewList(movimentaDL, GL_COMPILE);
    movimentaPersonagem(this->movimentoAtual , 1);
    glEndList();
}
void Inimigo3::chamaDisplayList()
{
    criaDisplayList();
    glCallList(this->movimentaDL);
}
Inimigo3::Inimigo3()
{
}

Inimigo3::~Inimigo3()
{
}
