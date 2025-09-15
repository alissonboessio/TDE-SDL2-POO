#ifndef CASA_H
#define CASA_H

#include <SDL2/SDL.h>
#include "Shape.h"
#include "Primitives.h"
#include "Point.h"
#include <string>
#include <vector>

class Casa : public Shape {
private:
    int altura, largura, inclinacao;
    Point posic;
    std::string corParede, corTelhado, corPorta; // utilizar getColor do Primitives

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

        Primitives::drawPolygon(surface, paredeTela, Primitives::getColor(surface, corParede));



        // teto
        std::vector<Point> tetoTela;
        tetoTela.reserve(pontosTeto.size());
        for (auto p : pontosTeto)
            tetoTela.push_back(p);

        Primitives::scalePolygon(tetoTela, largura, altura, 0,0);
        Primitives::translatePolygon(tetoTela, posic.getX(), posic.getY());

        for (auto& p : tetoTela)
            p = mundo.worldToScreen(p);

        Primitives::drawPolygon(surface, tetoTela, Primitives::getColor(surface, corTelhado));


        // porta
        std::vector<Point> portaTela;
        portaTela.reserve(pontosPorta.size());
        for (auto p : pontosPorta)
            portaTela.push_back(p);

        Primitives::scalePolygon(portaTela, largura, altura, 0,0);
        Primitives::translatePolygon(portaTela, posic.getX(), posic.getY());

        for (auto& p : portaTela)
            p = mundo.worldToScreen(p);

        Primitives::drawPolygon(surface, portaTela, Primitives::getColor(surface, corPorta));

    }

    std::vector<Point> pontosParede;
    std::vector<Point> pontosTeto;
    std::vector<Point> pontosPorta;

    // --- Getters ---
    Point getPosicao() const { return posic; }
    int getAltura() const { return altura; }
    int getLargura() const { return largura; }
    std::string getCorParede() const { return corParede; }
    std::string getCorTelhado() const { return corTelhado; }
    std::string getCorPorta() const { return corPorta; }
    int getInclinacao() const { return inclinacao; }

    // --- Setters ---
    void setPosic(Point ponto) { posic = ponto; }
    void setAltura(int valor) { altura = valor; }
    void setLargura(int valor) { largura = valor; }
    void setInclinacao(int valor) { inclinacao = valor; }
    void setCorParede(const std::string& cor) { corParede = cor; }
    void setCorTelhado(const std::string& cor) { corTelhado = cor; }
    void setCorPorta(const std::string& cor) { corPorta = cor; }

};

#endif // CASA_H
