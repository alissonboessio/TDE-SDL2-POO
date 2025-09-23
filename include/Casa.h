#ifndef CASA_H
#define CASA_H

#include <SDL2/SDL.h>
#include "Shape.h"
#include "Primitives.h"
#include "Point.h"
#include "HTMLColor.h"
#include <string>
#include <vector>

class Casa : public Shape {
private:
    int altura, largura;
    double inclinacao;
    Point posic;
    std::string corParede, corTelhado, corPorta, corChamine, corFumaca;
    std::vector<Point> pontosParede, pontosTeto, pontosPorta, pontosChamine;

public:
    Casa() {
        pontosParede = {
            {0, 0}, {0, 0.5}, {1, 0.5}, {1, 0}
        };

        pontosTeto = {
            {0, 0.5}, {0.5, 1}, {1, 0.5}
        };

        pontosPorta = {
            {0.35, 0}, {0.35, 0.3}, {0.65, 0.3}, {0.65, 0}
        };

        // Chaminé no lado esquerdo do telhado
        pontosChamine = {
            {0.15, 0.5}, {0.25, 0.5}, {0.25, 0.8}, {0.15, 0.8}
        };

        altura = 1;
        largura = 1;
        inclinacao = 0;
    }

std::vector<Point> fumacaRelativa = {
    {0.2, 1.0},
    {0.15, 1.3},
    {0.1, 1.5}
};


    void draw(SDL_Surface* surface, World mundo) override {
        if (!surface) return;
        HtmlColor hc;

        // --- Parede ---
        std::vector<Point> paredeTela = pontosParede;
        Primitives::scalePolygon(paredeTela, largura, altura, 0, 0);
        Primitives::translatePolygon(paredeTela, posic.getX(), posic.getY());
        Primitives::rotatePolygon(paredeTela, inclinacao, posic.getX(), posic.getY());
        for (auto& p : paredeTela) p = mundo.worldToScreen(p);

        Uint32 corParedeI = hc.getColorUint32(corParede, surface);
        Primitives::drawPolygon(surface, paredeTela, corParedeI);
        Primitives::scanFill(surface, paredeTela, corParedeI);

        // --- Telhado ---
        std::vector<Point> tetoTela = pontosTeto;
        Primitives::scalePolygon(tetoTela, largura, altura, 0, 0);
        Primitives::translatePolygon(tetoTela, posic.getX(), posic.getY());
        Primitives::rotatePolygon(tetoTela, inclinacao, posic.getX(), posic.getY());
        for (auto& p : tetoTela) p = mundo.worldToScreen(p);

        Uint32 corTelhadoI = hc.getColorUint32(corTelhado, surface);
        Primitives::drawPolygon(surface, tetoTela, corTelhadoI);
        Primitives::scanFill(surface, tetoTela, corTelhadoI);

        // --- Porta ---
        std::vector<Point> portaTela = pontosPorta;
        Primitives::scalePolygon(portaTela, largura, altura, 0, 0);
        Primitives::translatePolygon(portaTela, posic.getX(), posic.getY());
        Primitives::rotatePolygon(portaTela, inclinacao, posic.getX(), posic.getY());
        for (auto& p : portaTela) p = mundo.worldToScreen(p);

        Uint32 corPortaI = hc.getColorUint32(corPorta, surface);
        Primitives::drawPolygon(surface, portaTela, corPortaI);
        Primitives::scanFill(surface, portaTela, corPortaI);

        // --- Chaminé ---
        std::vector<Point> chamineTela = pontosChamine;
        Primitives::scalePolygon(chamineTela, largura, altura, 0, 0);
        Primitives::translatePolygon(chamineTela, posic.getX(), posic.getY());
        Primitives::rotatePolygon(chamineTela, inclinacao, posic.getX(), posic.getY());
        for (auto& p : chamineTela) p = mundo.worldToScreen(p);

        Uint32 corChamineI = hc.getColorUint32(corChamine, surface);
        Primitives::drawPolygon(surface, chamineTela, corChamineI);
        Primitives::scanFill(surface, chamineTela, corChamineI);

        double raioBaseSRU = 0.07;

        for (int i = 0; i < (int)fumacaRelativa.size(); i++) {
            Point centro = Primitives::scalePoint(fumacaRelativa[i], largura, altura, 0, 0);
            centro = Primitives::translatePoint(centro, posic.getX(), posic.getY());
            centro = Primitives::rotatePoint(centro, inclinacao, posic.getX(), posic.getY());
            centro = mundo.worldToScreen(centro);

            // raio menor a cada círculo
            double raioSRU = raioBaseSRU - i * 0.02;
            int raioTela = mundo.worldToScreen(Primitives::scaleLength(raioSRU, largura, altura));

            Uint32 corFumacaI = hc.getColorUint32(corFumaca, surface);
            Primitives::drawCircle(surface, centro.getX(), centro.getY(), raioTela, corFumacaI);
            Primitives::floodFill(surface, centro.getX(), centro.getY(), corFumacaI, corFumacaI);
        }
    }

    // --- Getters ---
    Point getPosicao() const { return posic; }
    int getAltura() const { return altura; }
    int getLargura() const { return largura; }
    std::string getCorParede() const { return corParede; }
    std::string getCorTelhado() const { return corTelhado; }
    std::string getCorPorta() const { return corPorta; }
    std::string getCorChamine() const { return corChamine; }
    std::string getCorFumaca() const { return corFumaca; }
    double getInclinacao() const { return inclinacao; }

    // --- Setters ---
    void setPosic(Point ponto) { posic = ponto; }
    void setAltura(int valor) { altura = valor; }
    void setLargura(int valor) { largura = valor; }
    void setInclinacao(double valor) { inclinacao = valor; }
    void setCorParede(const std::string& cor) { corParede = cor; }
    void setCorTelhado(const std::string& cor) { corTelhado = cor; }
    void setCorPorta(const std::string& cor) { corPorta = cor; }
    void setCorChamine(const std::string& cor) { corChamine = cor; }
    void setCorFumaca(const std::string& cor) { corFumaca = cor; }
};

#endif // CASA_H
