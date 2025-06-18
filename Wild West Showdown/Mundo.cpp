#include "Mundo.hpp"
#include "TextLoader.hpp"
#include "Texturas.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


    //construtor
    Mundo::Mundo(char* script_mundo, TextLoader* tloader){
    
    this->fase_atual = 0;
    this->fases_desbloqueadas = 0;
    int n_parallax;

 
    // Variáveis auxiliares
    std::ifstream *file = new std::ifstream();

    //Aloca a memória dinamicamente
    char *input_str = (char *)malloc(sizeof(char) * 50);

    //abre o arquivo
    file->open(script_mundo, std::ios::in);

    // Verifica se o arquivo está aberto
    if (!file->is_open())
    {
        printf("Não consigo abrir o arquivo\n");
        delete input_str;
        delete file;

    }
    
    file->getline(input_str, 30);
    sscanf(input_str, "%d", &n_parallax);

    this->numbers_parallax = n_parallax;

    // Carrega o vetor de modelo da textura e o vetor de texturas
    for (int i = 0; i < n_parallax; i++)
    {
     
        // Obtem o nome do arquivo de textura do menu
        file->getline(input_str, 100);
        std::string key(input_str);

        //identifica cada Parte do parallax e qual o ID da textura designada para cada fase
        this->textures.vectext.push_back(tloader->getTexture(key));
        this->vec_menus_text.push_back(tloader->getTexture(key));
                                                printf("menu: %d, texture %d\n", i, this->textures.vectext[i]);



    }
    this->textures.texture_index = vec_menus_text[0];

    delete input_str;
    delete file;


    }

    void Mundo::render_fase(double posicaoX){


        //textura topo
        glPushMatrix();
        glColor3f(1,1,1);

        glBindTexture(GL_TEXTURE_2D, this->textures.vectext[0]);
        glBegin(GL_TRIANGLE_FAN);


        glTexCoord2f(1, 0);
        glVertex3f(155 - (posicaoX*0.05), 100,  -0.5);

        glTexCoord2f(0, 0);
        glVertex3f(-155 - (posicaoX*0.05), 100,  -0.5);

        glTexCoord2f(0, 1);
        glVertex3f(-155 - (posicaoX*0.05),  0,  -0.5);

        glTexCoord2f(1, 1);
        glVertex3f(155 - (posicaoX*0.05),  0,  -0.5);
        
        glEnd();
        glPopMatrix();

        //textura montanha 1
        glPushMatrix();
        glColor3f(1,1,1);

        glBindTexture(GL_TEXTURE_2D, this->textures.vectext[1]);
        glBegin(GL_TRIANGLE_FAN);


        glTexCoord2f(1, 0);
        glVertex3f(155 - (posicaoX*0.15), 80,  -0.5);

        glTexCoord2f(0, 0);
        glVertex3f( -155  - (posicaoX*0.15)  , 80,  -0.5);

        glTexCoord2f(0, 1);
        glVertex3f( -155  -(posicaoX*0.15)  , -20,  -0.5);

        glTexCoord2f(1, 1);
        glVertex3f(155 -(posicaoX*0.15), -20,  -0.5);
        
        glEnd();
        glPopMatrix();  

        //textura montanha 2
        glPushMatrix();
        glColor3f(1,1,1);

        glBindTexture(GL_TEXTURE_2D, this->textures.vectext[2]);
        glBegin(GL_TRIANGLE_FAN);

        glTexCoord2f(1, 0);
        glVertex3f(155- (posicaoX*0.25)   , 60,  -0.5);

        glTexCoord2f(0, 0);
        glVertex3f( -155- (posicaoX*0.25)   , 60,  -0.5);

        glTexCoord2f(0, 1);
        glVertex3f( -155- (posicaoX*0.25)   , -40,  -0.5);

        glTexCoord2f(1, 1);
        glVertex3f(155- (posicaoX*0.25)   , -40,  -0.5);
        
        glEnd();
        glPopMatrix();

        //textura chão
        glPushMatrix();
        glColor3f(1,1,1);

        glBindTexture(GL_TEXTURE_2D, this->textures.vectext[3]);
        glBegin(GL_TRIANGLE_FAN);

        glTexCoord2f(1, 0);
        glVertex3f(124, 50,  -0.5);

        glTexCoord2f(0, 0);
        glVertex3f( -124, 50,  -0.5);

        glTexCoord2f(0, 1);
        glVertex3f( -124,  -100,  -0.5);

        glTexCoord2f(1, 1);
        glVertex3f(124,  -100,  -0.5);

        
        glEnd();
        glPopMatrix();
    
        glDisable(GL_TEXTURE_2D);    
        
    }  

    //Carrega as transições das fases, início de fase, fase concluída e game over
    void Mundo::render_transicoes(int i){

                glPushMatrix();
        glColor3f(1,1,1);

        glBindTexture(GL_TEXTURE_2D, this->textures.vectext[i]);
        glBegin(GL_TRIANGLE_FAN);
       

        glTexCoord2f(1, 0);
        glVertex3f( 100,  100,  -0.5);

        glTexCoord2f(0, 0);
        glVertex3f(-100,  100,  -0.5);

        glTexCoord2f(0, 1);
        glVertex3f(-100, -100,  -0.5);

        glTexCoord2f(1, 1);
        glVertex3f( 100, -100,  -0.5);
    
        glEnd();
        glPopMatrix();
    }