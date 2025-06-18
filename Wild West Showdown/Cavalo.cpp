#include <iostream>
#include "Cavalo.hpp"
#include <vector>
#include <GL/freeglut.h>
#include <string.h>
using namespace std;

Cavalo::Cavalo(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu) : Personagem(posicaoX, posicaoY, larguraX, alturaY, velocidade, numDeVidas, hp, morreu)
{
    this->nomeDoArquivo = "texturas/inimigoCavalo.png";
    /*Atribui valores para os sprites para uso interno*/
    this->larguraDoSprite = 120;
    this->alturaDoSprite = 99;
    /*Carrega a textura pelo construtor*/
    this->carregaTextura(nomeDoArquivo.c_str());
    /*Adiciona os movimentos*/
    movimentos.push_back(mov1);
    movimentos.push_back(mov2);
    movimentos.push_back(mov3);
    movimentos.push_back(mov4);
    movimentos.push_back(mov5);
    movimentos.push_back(mov6);
    this->dano = 50;
    this->movimentaDL = glGenLists(1);
    criaDisplayList();

}
Cavalo::~Cavalo()
{
}
Cavalo::Cavalo()
{
}
void Cavalo::movimentaPersonagem(int movimento, double escala)

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
    bool condicaoLimiteHorizontal = true;
    /*Faz o inimigo sinalizar que tomou dano e também desaparecer*/
    if (this->getMorreu())
    {
        movimentoAtual = 4;
        this->tomandoDano = true;
        this->segundosDeMorte += 1;
    }
    /*Movimenta o personagem trocando seus sprites*/
    if ((movX != 0 || movY != 0) && condicaoLimiteHorizontal && condicaoLimiteVertical && this->getMorreu() == false && this->atirando == false)
    {
        glPushMatrix();
        glTranslatef(movX, movY, 0);
        desenhaPersonagem(this->movimentos[movimento][0], this->movimentos[movimento][1], this->movimentos[movimento][2], this->movimentos[movimento][3], escala);
        this->setPosicaoX(this->getPosicaoX() + movX);
        this->setPosicaoY(this->getPosicaoY() + movY);
        glPopMatrix();
    }
    else if (this->segundosDeMorte <= 120)
    {
        /*Faz com que o personagem que esta morto continue no chão ate o tempo de desaparecer*/
        desenhaPersonagem(this->movimentos[movimento][0], this->movimentos[movimento][1], this->movimentos[movimento][2], this->movimentos[movimento][3], escala);
    }
    else
    {
        /*Sinaliza para que não desenhe mais o personagem visto que ele morreu*/
        this->desapareceu = true;
        this->frequenciaDeInvocacao += 1;
        reapareceInimigo(20);
        this->morreu_sozinho = false;
    }
}
void Cavalo::animacaoAndando()
{
    /*Troca os sprites para fornecer a animação de andar*/
    if (this->getMorreu() == false)
    {
        if (movimentoAtual <= 5)
        {
            if (movimentoAtual == 5)
            {
                movimentoAtual = 0;
            }
            else
            {
                movimentoAtual += 1;
            }
        }
    }
    else
    {
        /*Se ele morreu faz com que mantenha o sprite de morte ativado*/
        movimentoAtual = 4;
    }
}

void Cavalo::seguePersonagem(double posicaoXP, double posicaoYP)
{
    /*Segue o personagem na tela*/
    if (!this->getMorreu())
    {

            this->frequenciaDePerseguicao = 0;
            this->movX = -this->getVelocidade()*1.5;

            if(this->getPosicaoX() <= -105)
            {
                this->setMorreu(true);
                this->morreu_sozinho = true;
                this->atingiu = false;
            }

    }

    this->frequenciaDePerseguicao++;
    animacaoAndando();
}
void Cavalo::criaDisplayList()
{
    /*Cria a display list dependendo da animação*/
    /*Utilizamos display list para cumprir com o requirido no roteiro*/
    glNewList(movimentaDL, GL_COMPILE);
    movimentaPersonagem(this->movimentoAtual , 1);
    glEndList();
}
void Cavalo::chamaDisplayList()
{
    criaDisplayList();
    glCallList(this->movimentaDL);
}