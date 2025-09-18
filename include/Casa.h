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
    Point posic, posicCorParede, posicCorTelhado, posicCorPorta;
    std::string corParede, corTelhado, corPorta; // utilizar getColor do Primitives
    std::vector<Point> pontosParede, pontosTeto, pontosPorta;

public:
    Casa() {

        pontosParede = {
            {0, 0}, {0, 0.5}, {1, 0.5}, {1, 0}
        };
        posicCorParede = {0.25, 0.25};

        pontosTeto = {
            {0, 0.5}, {0.5, 1}, {1, 0.5}
        };
        posicCorTelhado = {0.5, 0.8};

        pontosPorta = {
            {0.35, 0}, {0.35, 0.3}, {0.65, 0.3}, {0.65, 0}
        };
        posicCorPorta = {0.4, 0.2};

        altura = 1;
        largura = 1;
        inclinacao = 0;

    }

    void draw(SDL_Surface* surface, World mundo) override {
        if (!surface) return;

        // parede
        std::vector<Point> paredeTela;
        paredeTela.reserve(pontosParede.size());
        for (auto p : pontosParede)
            paredeTela.push_back(p);

        Primitives::scalePolygon(paredeTela, largura, altura, 0,0);
        Primitives::translatePolygon(paredeTela, posic.getX(), posic.getY());

        for (auto& p : paredeTela)
            p = mundo.worldToScreen(p);

        HtmlColor hc = HtmlColor();

        Primitives::drawPolygon(surface, paredeTela, hc.getColorUint32(corParede, surface));

        Point fillCorParede = Primitives::scalePoint(posicCorParede, largura, altura, 0,0);
        fillCorParede = mundo.worldToScreen(Primitives::translatePoint(fillCorParede, posic.getX(), posic.getY()));
        Primitives::floodFill(surface, fillCorParede.getX(), fillCorParede.getY(), hc.getColorUint32(corParede, surface));

        // teto
        std::vector<Point> tetoTela;
        tetoTela.reserve(pontosTeto.size());
        for (auto p : pontosTeto)
            tetoTela.push_back(p);

        Primitives::scalePolygon(tetoTela, largura, altura, 0,0);
        Primitives::translatePolygon(tetoTela, posic.getX(), posic.getY());

        for (auto& p : tetoTela)
            p = mundo.worldToScreen(p);

        Primitives::drawPolygon(surface, tetoTela, hc.getColorUint32(corTelhado, surface));

        Point fillCorTelhado = Primitives::scalePoint(posicCorTelhado, largura, altura, 0,0);
        fillCorTelhado = mundo.worldToScreen(Primitives::translatePoint(fillCorTelhado, posic.getX(), posic.getY()));
        Primitives::floodFill(surface, fillCorTelhado.getX(), fillCorTelhado.getY(), hc.getColorUint32(corTelhado, surface));

        // porta
        std::vector<Point> portaTela;
        portaTela.reserve(pontosPorta.size());
        for (auto p : pontosPorta)
            portaTela.push_back(p);

        Primitives::scalePolygon(portaTela, largura, altura, 0,0);
        Primitives::translatePolygon(portaTela, posic.getX(), posic.getY());

        for (auto& p : portaTela)
            p = mundo.worldToScreen(p);

        Primitives::drawPolygon(surface, portaTela, hc.getColorUint32(corPorta, surface));

        Point fillCorPorta = Primitives::scalePoint(posicCorPorta, largura, altura, 0,0);
        fillCorPorta = mundo.worldToScreen(Primitives::translatePoint(fillCorPorta, posic.getX(), posic.getY()));
        Primitives::floodFill(surface, fillCorPorta.getX(), fillCorPorta.getY(), hc.getColorUint32(corPorta, surface));
    }

    // --- Getters ---
    Point getPosicao() const { return posic; }
    int getAltura() const { return altura; }
    int getLargura() const { return largura; }
    std::string getCorParede() const { return corParede; }
    std::string getCorTelhado() const { return corTelhado; }
    std::string getCorPorta() const { return corPorta; }
    double getInclinacao() const { return inclinacao; }

    // --- Setters ---
    void setPosic(Point ponto) { posic = ponto; }
    void setAltura(int valor) { altura = valor; }
    void setLargura(int valor) { largura = valor; }
    void setInclinacao(double valor) { inclinacao = valor; }
    void setCorParede(const std::string& cor) { corParede = cor; }
    void setCorTelhado(const std::string& cor) { corTelhado = cor; }
    void setCorPorta(const std::string& cor) { corPorta = cor; }

};

#endif // CASA_H
