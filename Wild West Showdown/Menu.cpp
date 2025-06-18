#include "Menu.hpp"
#include "TextLoader.hpp"
#include "Texturas.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

    int aux = 0;

    //construtor
    Menu::Menu(char* script_menu, TextLoader* tloader){
    
    this->fase_atual = 0;
    this->fases_desbloqueadas = 0;

    float button_x, button_y;
    int n_menus, n_botoes;
    int button_acction;
    

    // Variáveis auxiliares
    std::ifstream *file = new std::ifstream();

    //aloca a memória dinamicamente
    char *input_str = (char *)malloc(sizeof(char) * 50);

    //abre o arquivo de texturas descritas
    file->open(script_menu, std::ios::in);

    // Verifica se o arquivo está aberto
    if (!file->is_open())
    {
        printf("Não consigo abrir o arquivo\n");
        delete input_str;
        delete file;

    }

    // Verifica quantos modelos de menus deve carregar
    file->getline(input_str, 30);
    sscanf(input_str, "%d", &n_menus);
    this->vec_buttons.resize(n_menus);
    this->vec_buttons_text.resize(n_menus);
    this->vec_button_acction.resize(n_menus);
                                                printf("num menus: %d\n", n_menus);
    this->numbers_menus = n_menus;

    // Carrega o vetor de modelo da textura e o vetor de texturas
    for (int i = 0; i < n_menus; i++)
    {

        // Obtem o nome do arquivo de textura do menu
        file->getline(input_str, 100);
        std::string key(input_str);
        this->textures.vectext.push_back(tloader->getTexture(key));
        this->vec_menus_text.push_back(tloader->getTexture(key));
                                                printf("menu: %d, texture %d\n", i, this->textures.vectext[i]);
        //monstra a quantidade de botões que o menu principal possui
        file->getline(input_str, 30);
        sscanf(input_str, "%d", &n_botoes);
                                                printf("n botoes %d\n", n_botoes);
        
        
        for(int j = 0; j < n_botoes; j++){
    
            //delimita as menores coordenadas desginadas para cada botão  
            file->getline(input_str, 30);
            sscanf(input_str, "%f %f", &button_x, &button_y);
            this->vec_buttons[i].push_back(std::make_pair(button_x, button_y));            
                                                printf("button x e y esquerda: %f, %f\n", button_x, button_y);
            //delimita as maiores coordenadas desginadas para cada botão
            file->getline(input_str, 30);
            sscanf(input_str, "%f %f", &button_x, &button_y);
            this->vec_buttons[i].push_back(std::make_pair(button_x, button_y));
                                                 printf("button x e y direita: %f, %f\n", button_x, button_y);           
            //delimita qual o ID da textura atual
            file->getline(input_str, 30);
            std::string key_button(input_str);
            this->vec_buttons_text[i].push_back(tloader->getTexture(key_button));
                                                 printf("button textura: %d\n", tloader->getTexture(key_button));   
            //muda a ação do botão para saber se o mouse está pressionado
            file->getline(input_str, 30);
            sscanf(input_str, "%d", &button_acction);
            this->vec_button_acction[i].push_back(button_acction);
                                                 printf("acao do botao: %d\n", button_acction);
    
        }
    }
    //caso não seja usada mais a textura deleta as informações para não pesar o programa
    this->textures.texture_index = vec_menus_text[0];

    delete input_str;
    delete file;
    }

    //tela de desenho do menu
    void Menu::render_menu(){

        glPushMatrix();
        glColor3f(1,1,1);

        glBindTexture(GL_TEXTURE_2D, this->textures.texture_index);
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

    void Menu::atualizarfase(int statusjogo){

        fase_atual = statusjogo;
    }

    /*
    Função responsável por tratar a tela do mouse
    A partir do arquivo lido, muda a FASE_ATUAL, carregando outro menu
    */

    int Menu::tratarMouse(int state, float ox, float oy){


        this->textures.texture_index = vec_menus_text[fase_atual];
        for(int i = 0, j = 0; i < vec_buttons[fase_atual].size();i+=2, j++){

            //verifica se a posição do mouse está dentro das coordenadas dos botoes designados na fase atual 
            if((vec_buttons[fase_atual][i].first <= ox && ox <= vec_buttons[fase_atual][i+1].first) && 
            (vec_buttons[fase_atual][i].second <= oy && oy <= vec_buttons[fase_atual][i+1].second)){
                
                if(state == 1){
                    fase_atual = vec_button_acction[fase_atual][j];  
                 }
                else{
                    this->textures.texture_index = vec_buttons_text[fase_atual][j];
                }
                break;
            }
        }
        //responsável por mudar as fases
        
        //fecha o programa
        if(fase_atual == -1)
            exit(0);
        //muda para a fase de menu 1
        else if(fase_atual == -2)
            return 1;
        //muda para a fase de menu 2
        else if(fase_atual == -3)
            return 2;
        //muda para a fase de menu 3
        else if(fase_atual == -4)
            return 3;
        
    return 0;
   }
