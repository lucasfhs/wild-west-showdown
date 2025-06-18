#include "Disparo.hpp"

Disparo::Disparo(bool disparou) : disparou(disparou)
{
    /*Define o nome do arquivo da textura*/
    this->nomeDoArquivoBala = "texturas/bala.png";
    this->nomeDoArquivoCanhao = "texturas/balacanhao.png";
    this->nomeDoArquivoMachado = "texturas/machado.png";
    /*Carrega todas as texturas*/
    this->carregaTexturas();
    /*Cria a display list*/  
    this->criaDisplayList();
}

Disparo::~Disparo()
{
}

double Disparo::getDisparoX()
{
    return this->disparoX;
}
void Disparo::setDisparoX(double x)
{
    this->disparoX = x;
}
double Disparo::getDisparoY()
{
    return this->disparoY;
}
void Disparo::setDisparoY(double y)
{
    this->disparoY = y;
}

void Disparo::criaDisplayList()
{
    /*Cria as display list para as balas*/
    glNewList(DisplayListBala, GL_COMPILE);
    desenhaTiroParaDl();
    glEndList();

    glNewList(DisplayListCanhao, GL_COMPILE);
    desenhaCanhaoParaDl();
    glEndList();

    glNewList(DisplayListMachado, GL_COMPILE);
    desenhaMachadoParaDl();
    glEndList();
}

void Disparo::chamaDisplayList(int i)
{
    /*Chama a display display list das balas dependendo do valor enviado por parametro*/
    if(i == 0){
        glCallList(this->DisplayListBala);
    }
    if(i == 1){
        glCallList(this->DisplayListCanhao);
    }
    if(i == 2){
        glCallList(this->DisplayListMachado);
    }
}

bool Disparo::getDisparou()
{
    return this->disparou;
}
void Disparo::setDisparou(bool t)
{
    this->disparou = t;
}

void Disparo::desenhaTiro()
{
    /*Chama a bala padrão para ser desenhada*/
    chamaDisplayList(0);

}
void Disparo::desenhaTiroCanhao()
{
    /*Chama a bala de canhao padrão para ser desenhada*/
    chamaDisplayList(1);

}
void Disparo::desenhaTiroMachado()
{
    /*Chama o machado padrão para ser desenhado*/
    chamaDisplayList(2);
    
}
void Disparo::carregaTextura(const char *arquivo)
{
    /*Carrega a textura do personagem*/
    GLuint idTextura = SOIL_load_OGL_texture(
        arquivo,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y);

    if (idTextura == 0)
    {
        std::cout << "Erro do SOIL: '" << SOIL_last_result() << "'" << std::endl;
    }

    else
        this->idTexturaBala = idTextura;
}

void Disparo::projetil(std::vector<Disparo> &projeteis, GLfloat &aspectRatio, Personagem &p, double velocidade)
{
    //função que atualiza as posições do tiro de acordo com sua velocidade
    for (int i = projeteis.size() - 1; i >= 0; i--)
    {
        if (projeteis.at(i).getDisparoX() <= 110 && projeteis.at(i).getDisparoX() >= -110  && projeteis.at(i).getDisparou())
        {
            projeteis.at(i).setDisparoX(projeteis.at(i).getDisparoX() + velocidade);
        }
    //se o tiro sair da tela ele é apagado
        else if (projeteis.at(i).getDisparou())
        {
            projeteis.at(i).setDisparou(false);
            projeteis.erase(projeteis.begin() + i);
            p.setContDisparos(p.getContDisparos() - 1);
        }
    }
}

void Disparo::limpaTiros(std::vector<Disparo> &projeteis, Personagem &p)
{
    for (int i = projeteis.size() - 1; i >= 0; i--)
    {
        projeteis.at(i).setDisparou(false);
        projeteis.erase(projeteis.begin() + i);
        p.setContDisparos(p.getContDisparos() - 1);
    }
}

void Disparo::desenhaTiroParaDl()
{
    /*Função que desenha a bala através da textura carregada no construtor*/
    // glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->idTexturaBala);
    tamanhoDaBala = 4;
    // glScalef(escala, escala, escala);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 1);

    glTexCoord2f(1, 0);
    glVertex3f(2 * tamanhoDaBala, 0, 1);

    glTexCoord2f(1, 1);
    glVertex3f(2 * tamanhoDaBala, tamanhoDaBala, 1);

    glTexCoord2f(0, 1);
    glVertex3f(0, tamanhoDaBala, 1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Disparo::desenhaCanhaoParaDl()
{
    /*COD DE DESENHO DA BALA DE CANHAO PARA DISPLAYLIST*/
        // glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->idTexturaCanhao);
    tamanhoDaBala = 4;
    // glScalef(escala, escala, escala);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 1);

    glTexCoord2f(1, 0);
    glVertex3f(tamanhoDaBala, 0, 1);

    glTexCoord2f(1, 1);
    glVertex3f(tamanhoDaBala, tamanhoDaBala, 1);

    glTexCoord2f(0, 1);
    glVertex3f(0, tamanhoDaBala, 1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Disparo::desenhaMachadoParaDl()
{
    /*COD para desenho do machado para display list*/
    // glColor3f(1,1,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->idTexturaMachado);
    tamanhoDaBala = 4;
    // glScalef(escala, escala, escala);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 1);

    glTexCoord2f(1, 0);
    glVertex3f(2 * tamanhoDaBala, 0, 1);

    glTexCoord2f(1, 1);
    glVertex3f(2 * tamanhoDaBala, tamanhoDaBala, 1);

    glTexCoord2f(0, 1);
    glVertex3f(0, tamanhoDaBala, 1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
void Disparo::carregaTexturas()
{
    /*Carrega todas as texturas de tiro*/
    GLuint idTextura1 = SOIL_load_OGL_texture(
        this->nomeDoArquivoBala.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y);

    if (idTextura1 == 0)
    {
        std::cout << "Erro do SOIL: '" << SOIL_last_result() << "'" << std::endl;
    }
    GLuint idTextura2 = SOIL_load_OGL_texture(
        this->nomeDoArquivoCanhao.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y);

    if (idTextura2 == 0)
    {
        std::cout << "Erro do SOIL: '" << SOIL_last_result() << "'" << std::endl;
    }
    GLuint idTextura3 = SOIL_load_OGL_texture(
        this->nomeDoArquivoMachado.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y);

    if (idTextura3 == 0)
    {
        std::cout << "Erro do SOIL: '" << SOIL_last_result() << "'" << std::endl;
    }
    /*Atribui as variáveis da instancia*/
    this->idTexturaBala = idTextura1;
    this->idTexturaCanhao = idTextura2;
    this->idTexturaMachado = idTextura3;
}
