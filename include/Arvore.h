#ifndef ARVORE_H
#define ARVORE_H

#include <SDL2/SDL.h>
#include "Shape.h"
#include "Primitives.h"
#include <string>

class Arvore : public Shape {
private:
    int altura, largura;
    double raioFolhaEsquerda, raioFolhaDireita, raioFolhaCentral, inclinacao;
    std::string corTronco, corFolhas; // utilizar getColor do Primitives
    Point posic, posicCorTronco, folhaEsquerda, folhaCentral, folhaDireita;
    std::vector<Point> pontosTroncoEsquerdo, pontosTroncoDireito, pontosTroncoFechamento, posicCorFolhas;

public:
    Arvore() {
        pontosTroncoEsquerdo = {
            {0.35, 0},{0.5, 0.3}, {0.35, 0.6}
        };

        pontosTroncoDireito = {
            {0.65, 0},{0.5, 0.3}, {0.65, 0.6}
        };
        pontosTroncoFechamento = {
            {0.35, 0},{0.65, 0}, {0.35, 0.6}, {0.65, 0.6}
        };
        posicCorTronco = {0.5, 0.3};

        folhaCentral = {0.5, 0.7};
        raioFolhaCentral = {0.25};
        folhaEsquerda = {0.3, 0.6};
        raioFolhaEsquerda = {0.2};
        folhaDireita = {0.7, 0.6};
        raioFolhaDireita = {0.2};

        altura = 1;
        largura = 1;
        inclinacao = 0;

    }

    void draw(SDL_Surface* surface, World mundo) override {
        if (!surface) return;

        //std::cout << posic.getX() << " - " << posic.getY() << " - " << largura << " - " << altura << " - " << "entrei\n";

        HtmlColor hc = HtmlColor();

        Uint32 corTroncoI = hc.getColorUint32(corTronco, surface);
        Uint32 corFolhasI = hc.getColorUint32(corFolhas, surface);

        // tronco esquerdo
        std::vector<Point> troncoTela;
        troncoTela.reserve(pontosTroncoEsquerdo.size());
        for (auto p : pontosTroncoEsquerdo)
            troncoTela.push_back(p);

        Primitives::scalePolygon(troncoTela, largura, altura, 0,0);
        Primitives::translatePolygon(troncoTela, posic.getX(), posic.getY());

        for (auto& p : troncoTela)
            p = mundo.worldToScreen(p);

        Primitives::drawBezier(surface, troncoTela[0],troncoTela[1],troncoTela[2], corTroncoI);

        // tronco direito
        troncoTela.clear();
        troncoTela.reserve(pontosTroncoDireito.size());
        for (auto p : pontosTroncoDireito)
            troncoTela.push_back(p);

        Primitives::scalePolygon(troncoTela, largura, altura, 0,0);
        Primitives::translatePolygon(troncoTela, posic.getX(), posic.getY());

        for (auto& p : troncoTela)
            p = mundo.worldToScreen(p);

        Primitives::drawBezier(surface, troncoTela[0],troncoTela[1],troncoTela[2], corTroncoI);

        // fechamentos tronco
        troncoTela.clear();
        troncoTela.reserve(pontosTroncoFechamento.size());
        for (auto p : pontosTroncoFechamento)
            troncoTela.push_back(p);

        Primitives::scalePolygon(troncoTela, largura, altura, 0,0);
        Primitives::translatePolygon(troncoTela, posic.getX(), posic.getY());

        for (auto& p : troncoTela)
            p = mundo.worldToScreen(p);

        Primitives::drawLine(surface, troncoTela[0],troncoTela[1], corTroncoI);
        Primitives::drawLine(surface, troncoTela[2],troncoTela[3], corTroncoI);

        Point fillCorTronco = Primitives::scalePoint(posicCorTronco, largura, altura, 0,0);
        fillCorTronco = mundo.worldToScreen(Primitives::translatePoint(fillCorTronco, posic.getX(), posic.getY()));
        Primitives::floodFill(surface, fillCorTronco.getX(), fillCorTronco.getY(), corTroncoI, corTroncoI);


        // copas
        Point centroCopaCentral = Primitives::scalePoint(folhaCentral, largura, altura, 0,0);
        centroCopaCentral = mundo.worldToScreen(Primitives::translatePoint(centroCopaCentral, posic.getX(), posic.getY()));
        double raioCopaCentral = mundo.worldToScreen(Primitives::scaleLength(raioFolhaCentral, largura, altura));

        Primitives::drawCircle(surface, centroCopaCentral.getX(), centroCopaCentral.getY(), raioCopaCentral, corFolhasI);
        Primitives::floodFill(surface, centroCopaCentral.getX(), centroCopaCentral.getY(), corFolhasI, corFolhasI);


        Point centroCopaEsquerda = Primitives::scalePoint(folhaEsquerda, largura, altura, 0,0);
        centroCopaEsquerda = mundo.worldToScreen(Primitives::translatePoint(centroCopaEsquerda, posic.getX(), posic.getY()));
        double raioCopaEsquerda = mundo.worldToScreen(Primitives::scaleLength(raioFolhaEsquerda, largura, altura));

        Primitives::drawCircle(surface, centroCopaEsquerda.getX(), centroCopaEsquerda.getY(), raioCopaEsquerda, corFolhasI);
        Primitives::floodFill(surface, centroCopaEsquerda.getX() - raioCopaEsquerda / 2, centroCopaEsquerda.getY(), corFolhasI, corFolhasI);


        Point centroCopaDireita = Primitives::scalePoint(folhaDireita, largura, altura, 0,0);
        centroCopaDireita = mundo.worldToScreen(Primitives::translatePoint(centroCopaDireita, posic.getX(), posic.getY()));
        double raioCopaDireita = mundo.worldToScreen(Primitives::scaleLength(raioFolhaDireita, largura, altura));

        Primitives::drawCircle(surface, centroCopaDireita.getX(), centroCopaDireita.getY(), raioCopaDireita, corFolhasI);
        Primitives::floodFill(surface, centroCopaDireita.getX() + raioCopaDireita / 2, centroCopaDireita.getY(), corFolhasI, corFolhasI);

    }



    // --- Getters ---
    Point getPosicao() const { return posic; }
    int getAltura() const { return altura; }
    int getLargura() const { return largura; }
    std::string getCorTronco() const { return corTronco; }
    std::string getCorFolhas() const { return corFolhas; }
    double getInclinacao() const { return inclinacao; }

    // --- Setters ---
    void setPosic(Point ponto) { posic = ponto; }
    void setAltura(int valor) { altura = valor; }
    void setLargura(int valor) { largura = valor; }
    void setInclinacao(double valor) { inclinacao = valor; }
    void setCorTronco(const std::string& cor) { corTronco = cor; }
    void setCorFolhas(const std::string& cor) { corFolhas = cor; }

};

#endif // ARVORE_H
