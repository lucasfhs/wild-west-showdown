#include <iostream>
#include "Inimigo1.hpp"
#include "Personagem.hpp"
#include <vector>
#include <GL/freeglut.h>
#include <string.h>
using namespace std;


Inimigo1::Inimigo1(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu) : Personagem(posicaoX, posicaoY, larguraX, alturaY, velocidade, numDeVidas, hp, morreu)
{
    this->nomeDoArquivo = "texturas/inimigo1.png";
    /*Atribui valores para os sprites para uso interno*/
    this->larguraDoSprite = 300;
    this->alturaDoSprite = 400;
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
    /*Cria id da displaylist para um atributo interno*/
    this->movimentaDL = glGenLists(1);
    criaDisplayList();
    /*Define o dano padrão*/
    this->dano = 20;
}
void Inimigo1::movimentaPersonagem(int movimento, double escala)

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
        movimentoAtual = 10;
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
            desenhaPersonagem(0.33 , 0.66, 0, 0.25,1);
        }
        
    }else{
    /*Sinaliza para que não desenhe mais o personagem visto que ele morreu*/
        this->desapareceu = true;
        this->frequenciaDeInvocacao += 1;
        reapareceInimigo(100);
    }
}
void Inimigo1::animacaoAndando()
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
        movimentoAtual = 10;
    }
}
void Inimigo1::animacaoAtirando()
{
    /*Troca os sprites para fornecer animação de atirando*/
    if(frequenciaDeAtaque % 5 == 0){
    if(this->getMorreu() == false && atirando == true){

        if(this->movimentoAtual <= 9 && this->movimentoAtual >= 7){
            if(movimentoAtual == 9){
                movimentoAtual = 7;
                
            }else {
                movimentoAtual++;
            }
        }else{
            movimentoAtual = 7;
        }
    }
    /*Define o tempo que o personagem continua atirando*/  
    if(this->segundosAtirando >= 40){
        this->atirando = false;
        this->segundosAtirando = 0;
        this->movimentoAtual = 0;
    }
    }


}

void Inimigo1::atiraSozinho()
{
    /*Configura o inimigo para atirar sozinho a partir de um contador*/
    if(this->frequenciaDeAtaque >= 60){
        this->atirando = true;
        this->frequenciaDeAtaque = 0;
    }else{
        this->frequenciaDeAtaque += 1;
    }
}

void Inimigo1::seguePersonagem(double posicaoXP, double posicaoYP)
{
    /*Segue o personagem na tela*/
       /*A função segue personagem trabalha pegando a posição do jogador e movendo o inimigo ate ele através dos outros metodos que fornecem animação e movimento presentes nesse código*/
    atiraSozinho();
    if(atirando == false && !this->getMorreu()){
        if(this->frequenciaDePerseguicao >= 45){
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
void Inimigo1::criaDisplayList()
{
    /*Cria a display list dependendo da animação*/
    /*Utilizamos display list para cumprir com o requirido no roteiro*/
    glNewList(movimentaDL, GL_COMPILE);
    movimentaPersonagem(this->movimentoAtual , 1);
    glEndList();
}
void Inimigo1::chamaDisplayList()
{
    criaDisplayList();
    glCallList(this->movimentaDL);
}
void Inimigo1::animacaoMorte(int movimento, double escala)
{
}
Inimigo1::Inimigo1()
{
}
Inimigo1::~Inimigo1()
{
}
