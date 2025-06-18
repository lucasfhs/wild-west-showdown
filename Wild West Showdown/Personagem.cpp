#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include "Personagem.hpp"
using namespace std;

Personagem::Personagem(double posicaoX, double posicaoY, double larguraX, double alturaY, float velocidade, int numDeVidas, float hp, bool morreu)
{
    this->posicaoX = posicaoX;
    this->posicaoY = posicaoY;
    this->larguraX = larguraX;
    this->alturaY = alturaY;
    this->velocidade = velocidade;
    this->numDeVidas = numDeVidas;
    this->hp = hp;
    this->morreu = morreu;
    this->vida.hp = hp;

}

Personagem::Personagem()
{
}

void Personagem::verificaVivoMorto()
{
    /*Verifica se o personagem em questão está vivo ou morto
    Se o hp zerar e a vidas zerarem ele morrerá
    */
    if(this->hp == 0 && this->numDeVidas == 0){
        this->morreu = true;
    }
}
/*Getters e setters*/
double Personagem:: getPosicaoX()
{
    return this->posicaoX;
}
void Personagem::setPosicaoX(double x)
{
    this->posicaoX = x;
}
double Personagem::getPosicaoY()
{
    return this->posicaoY;
}
void Personagem::setPosicaoY(double y)
{
    this->posicaoY = y;
}
bool Personagem::getMorreu()
{
    return this->morreu;
}
void Personagem::setMorreu(bool m)
{
    this->morreu = m;
}
float Personagem::getVelocidade()
{
    return this->velocidade;
}
void Personagem::setVelocidade(float velocidade)
{
    this->velocidade = velocidade;
}
int Personagem::getContDisparos()
{
    return this->contDisparos;
}
void Personagem::setContDisparos(int ContDisparos)
{
    this->contDisparos = ContDisparos;
}
/*Getters e setters*/
void Personagem::suavizaMovimento()

{
    /*Deve ser adicionada a função atualiza da timer func
    Ela faz com que os movimentos que ocorrerem do personagem não sejam bruscos...
    */
    if(movimentoAtual != 0 && this->getMorreu() == false && movX == 0 & movY == 0){
        if(movimentoAtual - 1 >= 0){
            movimentoAtual -= 1;
        }
    }
    if(movX != 0 || movY != 0){
        if(movX > 0 && movX != 0){
            movX -= 0.5;
        }
        else if (movX != 0){
            movX += 0.5;
        }
        if(movY > 0  && movY != 0){
            movY -= 0.5;
        }
        else if (movY != 0){
            movY += 0.5;
        }
    }
}

void Personagem::desenhaPersonagem(double tX1, double tX2, double tY1, double tY2, double escala)
{
    /*Função básica de desenho do personagem... é utilizada pela função de desenho dentro da subclasse
    Ela também sinaliza que o inimigo tomou dano transformando seu sprite em um tom avermelhado.
    */
    float flag = 1;
    if (this->tomandoDano == true){
        flag = 0;
        this->segundosDano ++;
        if(this->segundosDano >= 15){
            this->tomandoDano = false;
            this->segundosDano = 0;
        }
    }

    glColor3f(1,flag,flag);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->idTexturaPersonagem);
    glScalef(escala, escala, escala);
    glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(tX1, tY1);
        glVertex3f(this->posicaoX , this->posicaoY , 1);

        glTexCoord2f(tX2, tY1);
        glVertex3f(this->posicaoX + this->larguraX, this->posicaoY  , 1);

        glTexCoord2f(tX2,tY2);
        glVertex3f(this->posicaoX + this->larguraX , this->posicaoY + this->alturaY , 1);

        glTexCoord2f(tX1, tY2);
        glVertex3f(this->posicaoX, this->posicaoY + this->alturaY, 1);
    glEnd();
    glDisable(GL_TEXTURE_2D);

}
void Personagem::movimentaPersonagem(double tX1, double tX2, double tY1, double tY2, double escala){
    /*Função básica de movimento de personagem que utiliza da função desenha personagem e translação de matrix*/
      if(movX != 0 || movY != 0){
        glPushMatrix();
        glTranslatef(movX, movY, 0);
        desenhaPersonagem(tX1,tX2,tY1,tY2,escala);
        // render_heroi(tX1, tX2, tY1, tY2, escala,this->getPosicaoX(), this->getPosicaoY(), this->getLarguraX(),this->getAlturaY(), this->tomandoDano);
        this->posicaoX += movX;
        this->posicaoY += movY;
        glPopMatrix();
    }else{
        desenhaPersonagem(tX1,tX2,tY1,tY2,escala);
        
    }
}
void Personagem::carregaTextura(const char *arquivo)
{
    /*Carrega a textura do personagem*/
    GLuint idTextura = SOIL_load_OGL_texture(
                           arquivo,
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y
                       );

    if (idTextura == 0) {
        std::cout << "Erro do SOIL: '" << SOIL_last_result() << "'" << std::endl;
    }

    else
        this->idTexturaPersonagem = idTextura;
}

double Personagem::getLarguraX()
{
    return this->larguraX;
}

double Personagem::getAlturaY()
{
    return  this->alturaY;
}
void Personagem::reapareceInimigo(float life)
{
    
   if(this->frequenciaDeInvocacao >= 80 && this->desapareceu == true){
    /*Move o inimigo para algum lugar antes de traze-lo denovo no jogo*/
    srand(time(0));
    double numeroAleatorioX = rand()%10;
    double numeroAleatorioY = rand()%10;
    if(rand() % 3 == 0){
        numeroAleatorioX *= -1;   
    }
    srand(time(0));
    if(rand() % 3 == 0){
        numeroAleatorioY *= -1;
    }
    
    this->setPosicaoX( 90 + numeroAleatorioX);
    this->setPosicaoY(-75 + numeroAleatorioY);
    this->setMorreu(false);
    this->desapareceu = false;
    this->segundosDeMorte = 0;
    this->tomandoDano = false;
    this->movimentoAtual = 0;
    this->atirando = false;
    this->vida.hp = life;
    this->frequenciaDeInvocacao = 0;
    
    
   }
}