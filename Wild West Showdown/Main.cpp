#include "Menu.hpp"
#include "Mundo.hpp"
#include "Texturas.hpp"
#include "TextLoader.hpp"
#include "Personagem.hpp"
#include "Inimigo1.hpp"
#include "Inimigo2.hpp"
#include "Inimigo3.hpp"
#include "Chefe.hpp"
#include "Jogador.hpp"
#include "Cavalo.hpp"
#include "Disparo.hpp"
#include "Colisao.hpp"
#include <map>
#include "Vida.hpp"

TextLoader *tloader;
Menu *menu;
Mundo *carregar_fase1;
Mundo *carregar_fase2;
Mundo *carregar_fase3;
Mundo *carregar_transicoes;

Jogador personagemJogavel;
Inimigo1 inimigo1;
Inimigo2 inimigo2;
Inimigo3 inimigo3;
Cavalo cavalo1;
Chefe boss;

bool libera_tiro[5] = {false, false, false, false, false};

GLfloat razaoAspecto;
GLdouble ox = 0, oy = 0, oz = 0;

std::vector<int> displaytexturas;
std::vector<Disparo> tiros_heroi;
std::vector<Disparo> tiros_inimigos;
std::vector<Disparo> tiros_inimigos2;
std::vector<Disparo> tiros_inimigos3;
std::vector<Disparo> tiros_boss;

int cavalo_anda = 0;
int cronometro = 0;
int cronometro_congrats = 0;
int statusjogo = 0;
int cronometro_gameover = 0;
int aux_morte = 0;

char *texto;

int fase_iniciada;
int mouse_flag = 0;
GLdouble angle = 0;
GLuint idTexturaPoint;
bool pontuacao_flag = false;
int cont_disparo_inimigo = 1;

int delay_tiro = 0;
bool atirou = false;

GLuint carregaTextura(const char *arquivo)
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
        return idTextura;
}

void desenhaPoint()
{
    if(!pontuacao_flag){
        idTexturaPoint = carregaTextura("texturas/pontuacao.png");
        pontuacao_flag = true;
    }
    
    // habilita a textura
    glColor3f(1.0, 1.0, 0.0);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, idTexturaPoint);
    glBegin(GL_TRIANGLE_FAN);

    glTexCoord2f(1.0, -1.0);
    glVertex2f(57, 51);

    glTexCoord2f(-1.0, -1.0);
    glVertex2f(117, 51);

    glTexCoord2f(-1.0, 1.0);
    glVertex2f(117, 85);

    glTexCoord2f(1.0, 1.0);
    glVertex2f(57, 85);

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void inicializa()
{

    glClearColor(0, 0, 0, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    personagemJogavel = Jogador(-30, -70, 30, 30, 3, 3, 100, false);

    inimigo1 = Inimigo1(30, -75, 30, 30, 3, 1, 100, false);
    cavalo1 = Cavalo(30, -75, 30, 15, 6, 1, 20, false);
    inimigo2 = Inimigo2(30, -75, 30, 30, 3, 1, 60, false);
    inimigo3 = Inimigo3(30, -75, 30, 30, 3, 1, 40, false);
    boss = Chefe(30, -75, 60, 60, 3, 1, 600, false);
}

void restauraPersonagens()
{

    //Função usada para recriar os personagens ao iniciar um novo jogo

    personagemJogavel = Jogador(-30, -70, 30, 30, 3, 3, 100, false);
    personagemJogavel.desapareceu = false;
    personagemJogavel.segundosDeMorte = 0;
    personagemJogavel.restauraVida();

    inimigo1 = Inimigo1(30, -75, 30, 30, 3, 1, 40, false);
    inimigo1.desapareceu = false;
    inimigo1.segundosDeMorte = 0;
    cavalo1 = Cavalo(30, -75, 30, 15, 2, 1, 20, false);
    cavalo1.desapareceu = false;
    cavalo1.segundosDeMorte = 0;
    cavalo_anda = 0;
    inimigo2 = Inimigo2(30, -75, 30, 30, 3, 1, 60, false);
    inimigo2.desapareceu = false;
    inimigo2.segundosDeMorte = 0;
    inimigo3 = Inimigo3(30, -75, 30, 30, 3, 1, 80, false);
    inimigo3.desapareceu = false;
    inimigo3.segundosDeMorte = 0;
    boss = Chefe(30, -75, 60, 60, 3, 1, 2000, false);
    boss.desapareceu = false;
    boss.segundosDeMorte = 0;
}

void inimigoAtira()
{

    //função criada para fazer com que os inimigos atirem periodicamente

    if (cont_disparo_inimigo > 299 && cont_disparo_inimigo % 10 == 0 && libera_tiro[3])
    {
        if (!boss.getMorreu())
        {
            Disparo tiro_inimigo(true);
            tiros_boss.push_back(tiro_inimigo);
            tiros_boss.at(boss.getContDisparos()).setDisparoY(boss.getPosicaoY() + 14);
            tiros_boss.at(boss.getContDisparos()).setDisparoX(boss.getPosicaoX());
            boss.setContDisparos(boss.getContDisparos() + 1);
        }
    }

    if (cont_disparo_inimigo % 100 == 0 && libera_tiro[0])
    {
        if (!inimigo1.getMorreu())
        {
            Disparo tiro_inimigo(true);
            tiros_inimigos.push_back(tiro_inimigo);
            tiros_inimigos.at(inimigo1.getContDisparos()).setDisparoY(inimigo1.getPosicaoY() + 7);
            tiros_inimigos.at(inimigo1.getContDisparos()).setDisparoX(inimigo1.getPosicaoX());
            inimigo1.setContDisparos(inimigo1.getContDisparos() + 1);
        }
    }

    if (cont_disparo_inimigo % 120 == 0 && libera_tiro[1])
    {
        if (!inimigo2.getMorreu())
        {
            Disparo tiro_inimigo(true);
            tiros_inimigos2.push_back(tiro_inimigo);
            tiros_inimigos2.at(inimigo2.getContDisparos()).setDisparoY(inimigo2.getPosicaoY() + 7);
            tiros_inimigos2.at(inimigo2.getContDisparos()).setDisparoX(inimigo2.getPosicaoX());
            inimigo2.setContDisparos(inimigo2.getContDisparos() + 1);
        }
    }

    if (cont_disparo_inimigo % 140 == 0 && libera_tiro[2])
    {
        if (!inimigo3.getMorreu())
        {
            Disparo tiro_inimigo(true);
            tiros_inimigos3.push_back(tiro_inimigo);
            tiros_inimigos3.at(inimigo3.getContDisparos()).setDisparoY(inimigo3.getPosicaoY() + 7);
            tiros_inimigos3.at(inimigo3.getContDisparos()).setDisparoX(inimigo3.getPosicaoX());
            inimigo3.setContDisparos(inimigo3.getContDisparos() + 1);
        }
    }

    if (cont_disparo_inimigo > 400)
    {
        cont_disparo_inimigo = 1;
    }
}

void desenhaTiro()
{
    //função criada para desenhar os tiros na tela

    for (int i = 0; i < tiros_heroi.size(); i++)
    {
        if (tiros_heroi.at(i).getDisparou())
        {
            glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            glScaled(1.0, 1.0, 1.0);
            glTranslatef(tiros_heroi.at(i).getDisparoX(), tiros_heroi.at(i).getDisparoY(), 0.0);
            tiros_heroi.at(i).desenhaTiro();
            glPopMatrix();
        }
    }

    for (int i = 0; i < tiros_inimigos.size() && libera_tiro[0]; i++)
    {
        if (tiros_inimigos.at(i).getDisparou())
        {
            glColor3f(1.0, 0.0, 0.0);
            glPushMatrix();
            glScaled(1.0, 1.0, 1.0);
            glTranslatef(tiros_inimigos.at(i).getDisparoX(), tiros_inimigos.at(i).getDisparoY(), 0.0);
            tiros_inimigos.at(i).desenhaTiroCanhao();
            glPopMatrix();
        }
    }
    for (int i = 0; i < tiros_inimigos2.size() && libera_tiro[1]; i++)
    {
        if (tiros_inimigos2.at(i).getDisparou())
        {
            glColor3f(1.0, 0.0, 0.0);
            glPushMatrix();
            glScaled(1.0, 1.0, 1.0);
            glTranslatef(tiros_inimigos2.at(i).getDisparoX(), tiros_inimigos2.at(i).getDisparoY(), 0.0);
            tiros_inimigos2.at(i).desenhaTiroCanhao();
            glPopMatrix();
        }
    }
    for (int i = 0; i < tiros_inimigos3.size() && libera_tiro[2]; i++)
    {
        if (tiros_inimigos3.at(i).getDisparou())
        {
            glColor3f(1.0, 1.0, 1.0);
            glPushMatrix();
            glScaled(1.0, 1.0, 1.0);
            glTranslatef(tiros_inimigos3.at(i).getDisparoX(), tiros_inimigos3.at(i).getDisparoY(), 0.0);
            glRotated(angle, 0.0, 0.0, 1.0);
            tiros_inimigos3.at(i).desenhaTiroMachado();
            glPopMatrix();
        }

        angle += 2;
    }

    for (int i = 0; i < tiros_boss.size() && libera_tiro[3]; i++)
    {
        if (tiros_boss.at(i).getDisparou())
        {
            glColor3f(1.0, 0.0, 0.0);
            glPushMatrix();
            glScaled(1.0, 1.0, 1.0);
            glTranslatef(tiros_boss.at(i).getDisparoX(), tiros_boss.at(i).getDisparoY(), 0.0);
            tiros_boss.at(i).desenhaTiroCanhao();
            glPopMatrix();
        }
    }

    //testes de colisão dos tiros dos inimigos com o jogador

    if (colidiu(tiros_inimigos, personagemJogavel) && libera_tiro[0])
    {
        personagemJogavel.recebeDano(inimigo1.dano);
        inimigo1.setContDisparos(inimigo1.getContDisparos() - 1);
    }

    if (colidiu(tiros_inimigos2, personagemJogavel) && libera_tiro[1])
    {
        personagemJogavel.recebeDano(inimigo2.dano);
        inimigo2.setContDisparos(inimigo2.getContDisparos() - 1);
    }

    if (colidiu(tiros_inimigos3, personagemJogavel) && libera_tiro[2])
    {
        personagemJogavel.recebeDano(inimigo3.dano);
        inimigo3.setContDisparos(inimigo3.getContDisparos() - 1);
    }

    if (colisaoComCavalo(cavalo1, personagemJogavel) && libera_tiro[4])
    {
        personagemJogavel.recebeDano(cavalo1.dano);
        cavalo1.atingiu = true;
    }

    if (colidiu(tiros_boss, personagemJogavel) && libera_tiro[3])
    {
        personagemJogavel.recebeDano(boss.dano);
        boss.setContDisparos(boss.getContDisparos() - 1);
    }

    //testes de colisão dos tiros do jogador com os inimigos

    if (!inimigo1.getMorreu() && libera_tiro[0] && inimigo1.segundosDeMorte == 0)
    {
        if (colidiu(tiros_heroi, inimigo1))
        {
            inimigo1.vida.hp -= 20;
            inimigo1.tomandoDano = true;

            if (inimigo1.vida.hp <= 0)
            {
                inimigo1.setMorreu(true);
                personagemJogavel.pontuacao++;
            }

            personagemJogavel.setContDisparos(personagemJogavel.getContDisparos() - 1);
        }
    }

    if (!inimigo2.getMorreu() && libera_tiro[1] && inimigo2.segundosDeMorte == 0)
    {
        if (colidiu(tiros_heroi, inimigo2))
        {
            inimigo2.vida.hp -= 20;
            inimigo2.tomandoDano = true;

            if (inimigo2.vida.hp <= 0)
            {
                inimigo2.setMorreu(true);
                personagemJogavel.pontuacao++;
            }

            personagemJogavel.setContDisparos(personagemJogavel.getContDisparos() - 1);
        }
    }
    if (!inimigo3.getMorreu() && libera_tiro[2] && inimigo3.segundosDeMorte == 0)
    {
        if (colidiu(tiros_heroi, inimigo3))
        {
            inimigo3.vida.hp -= 20;
            inimigo3.tomandoDano = true;

            if (inimigo3.vida.hp <= 0)
            {
                inimigo3.setMorreu(true);
                personagemJogavel.pontuacao++;
            }

            personagemJogavel.setContDisparos(personagemJogavel.getContDisparos() - 1);
        }
    }
    if (!cavalo1.getMorreu() && libera_tiro[4] && cavalo1.segundosDeMorte == 0)
    {
        if (colidiu(tiros_heroi, cavalo1))
        {
            cavalo1.vida.hp -= 20;
            cavalo1.tomandoDano = true;

            if (cavalo1.vida.hp <= 0 && !cavalo1.morreu_sozinho)
            {
                cavalo1.setMorreu(true);
                personagemJogavel.pontuacao++;
            }

            personagemJogavel.setContDisparos(personagemJogavel.getContDisparos() - 1);
        }
    }
    if (!boss.getMorreu() && libera_tiro[3] && boss.segundosDeMorte == 0)
    {
        if (colidiu(tiros_heroi, boss))
        {
            boss.vida.hp -= 20;
            boss.tomandoDano = true;

            if (boss.vida.hp <= 0)
            {
                boss.setMorreu(true);
                personagemJogavel.pontuacao++;
            }

            personagemJogavel.setContDisparos(personagemJogavel.getContDisparos() - 1);
        }
    }
}

void desenhaPontuacao(const char *text,
                      void *font,
                      float x,
                      float y,
                      GLuint red,
                      GLuint green,
                      GLuint blue,
                      GLuint alpha)
{

    // Seleciona a cor e a posicao da pontuação
    glColor4ub(red, green, blue, alpha);
    glRasterPos2f(x, y);

    while (*text != '\0')
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
}

void redimensiona(int width, int height)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100, 100, -100, 100, -1, 1);

    razaoAspecto = ((float)width) / height;
    float worldAspectRatio = 1;
    ;

    if (razaoAspecto < worldAspectRatio)
    {
        float h = width / worldAspectRatio;
        float y = (height - h) / 2;
        glViewport(0, y, width, h);
    }

    else if (razaoAspecto > worldAspectRatio)
    {
        float w = ((float)height) * worldAspectRatio;
        float x = (width - w) / 2;
        glViewport(x, 0, w, height);
    }

    else
    {
        glViewport(0, 0, width, height);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{

    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLfloat wx = x, wy, wz;

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouse_flag = 1;

        // funcao responsável por pegar as coordenadas em pixels e transformar na coordenada do mundo.

        glGetIntegerv(GL_VIEWPORT, viewport);
        y = viewport[3] - y;
        wy = y;
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &wz);
        gluUnProject(wx, wy, wz, modelview, projection, viewport, &ox, &oy, &oz);
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        mouse_flag = 3;
    }
}

void posicaomouse(int x, int y)
{

    GLint viewport[4];
    GLdouble modelview[16], projection[16];
    GLfloat wx = x, wy, wz;

    glGetIntegerv(GL_VIEWPORT, viewport);
    y = viewport[3] - y;
    wy = y;
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &wz);
    gluUnProject(wx, wy, wz, modelview, projection, viewport, &ox, &oy, &oz);

    mouse_flag = 3;
}

void desenha_na_tela()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);

    if (fase_iniciada == 0)
    {
        menu->render_menu();
    }
    // Tela de carregamento fase 1
    if (fase_iniciada == 1)
    {
        if (cronometro <= 200)
        {
            for (int i = 0; i < 5; i++)
            {
                libera_tiro[i] = false;
            }

                Disparo::limpaTiros(tiros_inimigos, inimigo1);
                Disparo::limpaTiros(tiros_inimigos2, inimigo2);
                Disparo::limpaTiros(tiros_inimigos3, inimigo3);
                Disparo::limpaTiros(tiros_boss, boss);
                Disparo::limpaTiros(tiros_heroi, personagemJogavel);

            carregar_transicoes->render_transicoes(0);
            cronometro++;
            personagemJogavel.pontuacao = 0;
            restauraPersonagens();
            cont_disparo_inimigo = 1;
        }
        
        // A FASE 1 COMEÇA AQUI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (cronometro > 200 && personagemJogavel.pontuacao < 65)
        {
            libera_tiro[0] = true;
            libera_tiro[2] = true;
            carregar_fase1->render_fase(personagemJogavel.getPosicaoX());
            desenhaTiro();
            inimigo1.chamaDisplayList();
            inimigo3.chamaDisplayList();
            personagemJogavel.chamaDisplayList();
            personagemJogavel.desenhaVidas();
            desenhaPoint();
            desenhaPontuacao(texto, GLUT_BITMAP_9_BY_15, 64.5, 75, 0, 0, 0, 255);


        }
        // E TERMINA AQUI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        
        // Função Game Over 
        if (personagemJogavel.fimDeJogo  && cronometro_gameover <= 200)
        {
            glEnable(GL_TEXTURE_2D);
            carregar_transicoes->render_transicoes(7);
            cronometro_gameover++;
            //chama o menu principal do jogo
            if (cronometro_gameover > 200)
            {
            personagemJogavel.restauraVida();
            menu->atualizarfase(0);
            fase_iniciada = 0;
            cronometro = 0;
            cronometro_gameover = 0;
            }
        }
        
        //Transição fase 1 concluida
        if (personagemJogavel.pontuacao >= 65 && cronometro >= 200)
        {
            glEnable(GL_TEXTURE_2D);
            carregar_transicoes->render_transicoes(1);
            cronometro++;
        }
        
        //Menu de fases
        if (cronometro > 400)
        {
            personagemJogavel.restauraVida();
            menu->atualizarfase(3);
            fase_iniciada = 0;
            cronometro = 0;
            cronometro_gameover = 0;
        }
    }
    
    // Tela de carregamento fase 2
    if (fase_iniciada == 2)
    {
        if (cronometro <= 200)
        {
            for (int i = 0; i < 5; i++)
            {
                libera_tiro[i] = false;
            }
            for (int i = 0; i < tiros_heroi.size(); i++)
            {
                tiros_heroi.at(i).setDisparou(false);
            }
            carregar_transicoes->render_transicoes(2);
            cronometro++;
            cont_disparo_inimigo = 1;
        }
        
        // A FASE 2 COMEÇA AQUI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (cronometro > 200 && personagemJogavel.pontuacao < 130)
        {
            libera_tiro[1] = true;
            libera_tiro[4] = true;
            carregar_fase2->render_fase(personagemJogavel.getPosicaoX());
            desenhaTiro();
            inimigo2.chamaDisplayList();
            personagemJogavel.chamaDisplayList();
            cavalo1.chamaDisplayList();
            personagemJogavel.desenhaVidas();
            desenhaPoint();
            desenhaPontuacao(texto, GLUT_BITMAP_9_BY_15, 64.5, 75, 0, 0, 0, 255);
        }
        // E TERMINA AQUI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        
        // Função Game Over
        if (personagemJogavel.fimDeJogo  && cronometro_gameover <= 200)
        {
            glEnable(GL_TEXTURE_2D);
            carregar_transicoes->render_transicoes(7);
            cronometro_gameover++;
            //chama o menu principal do jogo
            if (cronometro_gameover > 200)
            {
            personagemJogavel.restauraVida();
            menu->atualizarfase(0);
            fase_iniciada = 0;
            cronometro = 0;
            cronometro_gameover = 0;
            }
        }

        //Transição fase 2 concluida
        if (personagemJogavel.pontuacao >= 130 && cronometro >= 200)
        {
            glEnable(GL_TEXTURE_2D);
            carregar_transicoes->render_transicoes(3);
            cronometro++;
        }

        //Menu de fases
        if (cronometro > 400)
        {
            personagemJogavel.restauraVida();
            menu->atualizarfase(4);
            fase_iniciada = 0;
            cronometro = 0;
            cronometro_gameover = 0;
        }
    }

    // Tela de carregamento fase 3
    if (fase_iniciada == 3)
    {
        if (cronometro <= 200)
        {
            for (int i = 0; i < 5; i++)
            {
                libera_tiro[i] = false;
            }
            for (int i = 0; i < tiros_heroi.size(); i++)
            {
                tiros_heroi.at(i).setDisparou(false);
            }
            carregar_transicoes->render_transicoes(4);
            cronometro++;
            boss.desapareceu = false;
            cont_disparo_inimigo = 1;
        }
        
        // A FASE 3 COMEÇA AQUI!!1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if (cronometro > 200 && !boss.desapareceu)
        {
            libera_tiro[3] = true;
            carregar_fase3->render_fase(personagemJogavel.getPosicaoX());
            desenhaTiro();
            personagemJogavel.chamaDisplayList();
            boss.chamaDisplayList();
            personagemJogavel.desenhaVidas();
            desenhaPoint();
            desenhaPontuacao(texto, GLUT_BITMAP_9_BY_15, 64.5, 75, 0, 0, 0, 255);
        }
        // E TERMINA AQUI !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        
        // Função Game Over
        if (personagemJogavel.fimDeJogo  && cronometro_gameover <= 200)
        {
            glEnable(GL_TEXTURE_2D);
            carregar_transicoes->render_transicoes(7);
            cronometro_gameover++;
            //chama o menu principal do jogo
            if (cronometro_gameover > 200)
            {
            personagemJogavel.restauraVida();
            menu->atualizarfase(0);
            fase_iniciada = 0;
            cronometro = 0;
            cronometro_gameover = 0;
            }
        }
        
        //Transição fase 3 concluida
        if (boss.desapareceu && cronometro >= 200)
        {
            glEnable(GL_TEXTURE_2D);
            carregar_transicoes->render_transicoes(5);
            cronometro++;
        }
        
        //Transição fase CONGRATULATION para menu
        if (cronometro > 400 && cronometro <= 600)
        {
            carregar_transicoes->render_transicoes(6);
            cronometro++;
        }
        //Menu principal do jogo.
        if (cronometro > 600)
        {
            menu->atualizarfase(0);
            fase_iniciada = 0;
            cronometro = 0;
            personagemJogavel.pontuacao = 0;
            cronometro_gameover = 0;
        }
    }

    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

void teclado(unsigned char tecla, int x, int y)
{
    switch (tolower(tecla))
    {
    // Tecla ESC
    case 27:
        exit(0);
        break;
    case 'w':
        // vai pra cima
        if (!(personagemJogavel.getPosicaoY() >= -55))
        {
            personagemJogavel.movY = personagemJogavel.getVelocidade();
        }

        break;
    case 'a':
        // vai pra esquerda
        if (!(personagemJogavel.getPosicaoX() <= -90))
        {
            personagemJogavel.movX = -personagemJogavel.getVelocidade();
        }

        break;
    case 's':
        // vai pra trás
        if (!(personagemJogavel.getPosicaoY() <= -90))
        {
            personagemJogavel.movY = -personagemJogavel.getVelocidade();
        }

        break;
    case 'd':
        // vai pra direita
        if (!(personagemJogavel.getPosicaoX() >= 70))
        {
            personagemJogavel.movX = personagemJogavel.getVelocidade();
        }
        break;
    case '\r':
        // personagem atira
        personagemJogavel.atirando = true;
        if (!personagemJogavel.getMorreu() && delay_tiro == 0)
        {
            Disparo tiro(true);
            tiros_heroi.push_back(tiro);
            tiros_heroi.at(personagemJogavel.getContDisparos()).setDisparoY(personagemJogavel.getPosicaoY() + 6.85);
            tiros_heroi.at(personagemJogavel.getContDisparos()).setDisparoX(personagemJogavel.getPosicaoX());
            personagemJogavel.setContDisparos(personagemJogavel.getContDisparos() + 1);
            atirou = true;
        }
        break;
    }
    personagemJogavel.animacaoAndando();
    glutPostRedisplay();
}

void timer(int t)
{

    if (!fase_iniciada)
    {
        fase_iniciada = menu->tratarMouse(mouse_flag, ox, oy);
    }
    //chama as funções apenas dos personagens presentes na fase 1
    if (fase_iniciada == 1 && cronometro > 200 && personagemJogavel.pontuacao < 65)
    {
        inimigoAtira();
        inimigo1.suavizaMovimento();
        inimigo1.seguePersonagem(personagemJogavel.getPosicaoX(), personagemJogavel.getPosicaoY());
        inimigo1.animacaoAtirando();
        inimigo3.suavizaMovimento();
        inimigo3.seguePersonagem(personagemJogavel.getPosicaoX(), personagemJogavel.getPosicaoY());
        inimigo3.animacaoAtirando();
        personagemJogavel.suavizaMovimento();
        personagemJogavel.animacaoAtirando();
        Disparo::projetil(tiros_heroi, razaoAspecto, personagemJogavel, 2);
        Disparo::projetil(tiros_inimigos, razaoAspecto, inimigo1, -2);
        Disparo::projetil(tiros_inimigos3, razaoAspecto, inimigo3, -1);
        cont_disparo_inimigo++;
    }
    //chama as funções apenas dos personagens presentes na fase 2
    if (fase_iniciada == 2 && cronometro > 200 && personagemJogavel.pontuacao < 130)
    {
        inimigoAtira();
        inimigo2.suavizaMovimento();
        inimigo2.seguePersonagem(personagemJogavel.getPosicaoX(), personagemJogavel.getPosicaoY());
        inimigo2.animacaoAtirando();
        if (cavalo_anda == 30)
        {
            cavalo1.seguePersonagem(personagemJogavel.getPosicaoX(), personagemJogavel.getPosicaoY());
            cavalo1.suavizaMovimento();
        }
        else
        {
            cavalo_anda += 1;
        }
        personagemJogavel.suavizaMovimento();
        personagemJogavel.animacaoAtirando();
        Disparo::projetil(tiros_heroi, razaoAspecto, personagemJogavel, 2);
        Disparo::projetil(tiros_inimigos2, razaoAspecto, inimigo2, -2);
        cont_disparo_inimigo++;
    }
    //chama as funções apenas do jogador e do boss (fase final)
    if (fase_iniciada == 3 && cronometro > 200 && !boss.desapareceu)
    {
        inimigoAtira();
        boss.suavizaMovimento();
        boss.seguePersonagem(personagemJogavel.getPosicaoX(), personagemJogavel.getPosicaoY());
        boss.animacaoAtirando();
        personagemJogavel.suavizaMovimento();
        personagemJogavel.animacaoAtirando();
        Disparo::projetil(tiros_heroi, razaoAspecto, personagemJogavel, 2);
        Disparo::projetil(tiros_boss, razaoAspecto, boss, -2);
        cont_disparo_inimigo++;
    }
    if(delay_tiro < 10 && atirou)
    {
        delay_tiro++;
    }else{
        delay_tiro = 0;
        atirou = false;
    }
    sprintf(texto, "  %d", personagemJogavel.pontuacao);
    glutPostRedisplay();

    glutTimerFunc(1000 / 60, timer, 0);
}

int main(int argc, char **argv)
{

    texto = (char *)malloc(sizeof(char *) * 100);

    glutInit(&argc, argv);
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(1500, 100);
    glutCreateWindow("Wild West Showdown");
    tloader = new TextLoader("carregar_texturas");
    menu = new Menu("fases_menu", tloader);
    carregar_fase1 = new Mundo("carregar_fase1", tloader);
    carregar_fase2 = new Mundo("carregar_fase2", tloader);
    carregar_fase3 = new Mundo("carregar_fase3", tloader);
    carregar_transicoes = new Mundo("carregar_transicoes", tloader);
    inicializa();
    glutDisplayFunc(desenha_na_tela);
    glutPassiveMotionFunc(posicaomouse);
    glutMouseFunc(mouse);
    glutKeyboardFunc(teclado);

    glutReshapeFunc(redimensiona);
    glutTimerFunc(0, timer, 34);

    glutMainLoop();
    return 0;
}