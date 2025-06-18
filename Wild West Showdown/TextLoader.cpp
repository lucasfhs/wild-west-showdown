#include "TextLoader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

TextLoader::TextLoader(char* texturas){

    // Variáveis auxiliares
    std::ifstream *file = new std::ifstream();

    //Aloca a memória dinamicamente
    char *input_str = (char *)malloc(sizeof(char) * 50);

    int n_coordenadas,
        n_texturas;

    file->open(texturas, std::ios::in);

    // Verifica se o arquivo está aberto
    if (!file->is_open())
    {
        printf("Não consigo abrir o arquivo\n");
        delete input_str;
        delete file;

    }


    // Verifica quantos modelos de textura deve carregar
    file->getline(input_str, 30);
    sscanf(input_str, "%d", &n_texturas);


    // Carrega o vetor de modelo da textura e o vetor de texturas
    for (int i = 0; i < n_texturas; i++)
    {

        
        // Obtem o nome do arquivo de textura
        file->getline(input_str, 100);
        std::string key(input_str);

        std::string input_caminho("texturas/");
        input_caminho.append(input_str);

        // Carrega a textura usando a soil
        GLuint idTextura = SOIL_load_OGL_texture(input_caminho.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_DDS_LOAD_DIRECT);

        // Verifica se ocorreu algum erro na SOIL
        if (idTextura == 0)
        {
            printf("Erro do SOIL: '%s'\n", SOIL_last_result());
        }
        else{
            this->text_map[key]=idTextura;
            printf("text loader: %s , %d\n", key.c_str(), this->text_map[key]);
        }
    }


    delete input_str;
    delete file;

}

GLuint TextLoader::getTexture(std::string text_key){


    return this->text_map[text_key];
}