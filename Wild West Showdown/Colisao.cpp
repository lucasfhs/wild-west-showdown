#include "Colisao.hpp"
using namespace std;
bool colidiu(std::vector<Disparo> &d, Personagem &p)
{
    // Testa se o disparo do inimigo (ou do jogador) atingiu o jogador (ou o inimigo)
    if (!d.empty() && !p.getMorreu())
    {
        for (int i = d.size()-1; i>=0; i--)
        {
            double distancia = sqrt(pow((d.at(i).getDisparoX() + d.at(i).tamanhoDaBala/2) - (p.getPosicaoX() + p.getLarguraX()/2) , 2) + pow((d.at(i).getDisparoY()+ d.at(i).tamanhoDaBala/2) - (p.getPosicaoY() + p.getAlturaY()/2), 2));
            double tam_inimigo = p.getAlturaY()/2;
            if (distancia < tam_inimigo)
            {
                d.at(i).setDisparou(false);
                d.erase(d.begin() + i);
                return true;
            }
        }
    }

    return false;
}
bool colisaoComCavalo(Cavalo &d, Jogador &p)
{
    //Testa se o cavalo "passou por cima" do jogador
        double distancia = sqrt(pow(d.getPosicaoX() + d.getLarguraX() - p.getPosicaoX() - p.getLarguraX()/2.0, 2) + pow(d.getPosicaoY() + d.getAlturaY() + - p.getPosicaoY() - p.getAlturaY()/2.0 , 2));
        double tam_inimigo = p.getAlturaY()/2;

        if ((distancia < tam_inimigo) && !d.atingiu && !d.getMorreu())
        {
            return true;
        }
        
    return false;
}

