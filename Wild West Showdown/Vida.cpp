#include "Vida.hpp"

Vida::Vida(){

    this->hp = hp; //diz respeito aos pontos de vida da entidade

}

GLuint Vida:: carregaTextura(const char* arquivo){ // esse método carrega a textura do sprite

    GLuint idTextura = SOIL_load_OGL_texture(
                           arquivo,
                           SOIL_LOAD_AUTO,
                           SOIL_CREATE_NEW_ID,
                           SOIL_FLAG_INVERT_Y
                       );

    if (idTextura == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    return idTextura;

}

void Vida::recebeDano(double dano){ //esse método pega o dano sofrido pela entidade e subtrai esse valor no hp

    this->hp -= dano;

}

void Vida::desenhaVida(double x1, double x2, double y1, double y2) //esse método desenha uma os corações de vida na tela 
{
    //y precisa ser obrigatoriamente o dobro de x pra manter uma proporção bonitinha do sprite
    if(!this->vida_flag){
        this->idTexturaVida = carregaTextura("texturas/vidas.png");
        vida_flag = true;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->idTexturaVida);

    glBegin(GL_TRIANGLE_FAN);

    if(this->hp<101 && this->hp>75){

        glTexCoord2f(0.17, -1.0);
        glVertex2f(x1, y1);

        glTexCoord2f(0.0, -1.0);
        glVertex2f(x2, y1);

        glTexCoord2f(0.0, 1.0); 
        glVertex2f(x2,  y2);

        glTexCoord2f(0.17, 1.0); 
        glVertex2f(x1,  y2);
    }

    if(this->hp<76 && this->hp>50){

        glTexCoord2f(0.33, -1.0);
        glVertex2f(x1, y1);

        glTexCoord2f(0.17, -1.0);
        glVertex2f(x2, y1);

        glTexCoord2f(0.17, 1.0); 
        glVertex2f(x2,  y2);

        glTexCoord2f(0.33, 1.0); 
        glVertex2f(x1,  y2);
    }

    if(this->hp<51 && this->hp>25){

        glTexCoord2f(0.49, -1.0);
        glVertex2f(x1, y1);

        glTexCoord2f(0.33, -1.0);
        glVertex2f(x2, y1);

        glTexCoord2f(0.33, 1.0); 
        glVertex2f(x2,  y2);

        glTexCoord2f(0.49, 1.0); 
        glVertex2f(x1,  y2);
    }

    if(this->hp<26 && this->hp>0){

        glTexCoord2f(0.65, -1.0);
        glVertex2f(x1, y1);

        glTexCoord2f(0.49, -1.0);
        glVertex2f(x2, y1);

        glTexCoord2f(0.49, 1.0); 
        glVertex2f(x2,  y2);

        glTexCoord2f(0.65, 1.0); 
        glVertex2f(x1,  y2);
    }

    if(this->hp<=0){

        glTexCoord2f(1.0, -1.0);
        glVertex2f(x1, y1);

        glTexCoord2f(0.82, -1.0);
        glVertex2f(x2, y1);

        glTexCoord2f(0.82, 1.0); 
        glVertex2f(x2,  y2);

        glTexCoord2f(1.0, 1.0); 
        glVertex2f(x1,  y2);
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);
}