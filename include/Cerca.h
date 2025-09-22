#ifndef CERCA_H
#define CERCA_H

#include <SDL2/SDL.h>
#include "Shape.h"
#include "Primitives.h"
#include <string>

class Cerca : public Shape {
protected:
    int altura, largura;
    double inclinacao;
    std::string cor; // utilizar getColor do Primitives
    std::vector<std::vector<Point>> cercaVertical;
    std::vector<std::vector<Point>> barrasHorizontais; // <-- vários retângulos pequenos
    std::vector<Point> corCercaVerticalPosic;
    std::vector<Point> corCercaHorizontalPosic;
    Point posic;

public:
    Cerca() {
        // estacas verticais
        cercaVertical = {
            {{0.1, 0}, {0.3, 0}, {0.3, 0.8}, {0.2, 1}, {0.1, 0.8}},
            {{0.4, 0}, {0.6, 0}, {0.6, 0.8}, {0.5, 1}, {0.4, 0.8}},
            {{0.7, 0}, {0.9, 0}, {0.9, 0.8}, {0.8, 1}, {0.7, 0.8}}
        };

        corCercaVerticalPosic = {
            {0.2, 0.5}, {0.5, 0.5}, {0.8, 0.5}
        };

        // agora, ao invés de 1 retângulo, criamos 3 pequenos entre as estacas
        barrasHorizontais = {
            {{0.1, 0.3}, {0.3, 0.3}, {0.3, 0.5}, {0.1, 0.5}}, // entre estaca 1 e 2
            {{0.4, 0.3}, {0.6, 0.3}, {0.6, 0.5}, {0.4, 0.5}}, // entre estaca 2 e 3
            {{0.7, 0.3}, {0.9, 0.3}, {0.9, 0.5}, {0.7, 0.5}}  // após estaca 3
        };

        corCercaHorizontalPosic = {
            {0.2, 0.4}, {0.5, 0.4}, {0.8, 0.4}
        };

        altura = 1;
        largura = 1;
        inclinacao = 0;
    }

    void draw(SDL_Surface* surface, World mundo) override {
        if (!surface) return;

        HtmlColor hc;
        Uint32 corTela = hc.getColorUint32(cor, surface);

        // --- Desenhar estacas verticais ---
        int i = 0;
        for (const auto& poligonoOriginal : cercaVertical) {
            auto poligono = poligonoOriginal;

            Primitives::scalePolygon(poligono, largura, altura, 0, 0);
            Primitives::translatePolygon(poligono, posic.getX(), posic.getY());
            Primitives::rotatePolygon(poligono, inclinacao, posic.getX(), posic.getY());

            for (auto& p : poligono)
                p = mundo.worldToScreen(p);

            Primitives::drawPolygon(surface, poligono, corTela);

            Point fillCor = Primitives::scalePoint(corCercaVerticalPosic[i], largura, altura, 0, 0);
            fillCor = Primitives::translatePoint(fillCor, posic.getX(), posic.getY());
            fillCor = Primitives::rotatePoint(fillCor, inclinacao, posic.getX(), posic.getY());
            fillCor = mundo.worldToScreen(fillCor);

            Primitives::floodFill(surface, fillCor.getX(), fillCor.getY(), corTela, corTela);
            i++;
        }

        // --- Desenhar barras horizontais separadas ---
        int j = 0;
        for (auto barra : barrasHorizontais) {
            Primitives::scalePolygon(barra, largura, altura, 0, 0);
            Primitives::translatePolygon(barra, posic.getX(), posic.getY());
            Primitives::rotatePolygon(barra, inclinacao, posic.getX(), posic.getY());

            for (auto& p : barra)
                p = mundo.worldToScreen(p);

            Primitives::drawPolygon(surface, barra, corTela);

            Point fillCor = Primitives::scalePoint(corCercaHorizontalPosic[j], largura, altura, 0, 0);
            fillCor = Primitives::translatePoint(fillCor, posic.getX(), posic.getY());
            fillCor = Primitives::rotatePoint(fillCor, inclinacao, posic.getX(), posic.getY());
            fillCor = mundo.worldToScreen(fillCor);

            Primitives::floodFill(surface, fillCor.getX(), fillCor.getY(), corTela, corTela);
            j++;
        }
    }

    // --- Getters ---
    Point getPosicao() const { return posic; }
    int getAltura() const { return altura; }
    int getLargura() const { return largura; }
    double getInclinacao() const { return inclinacao; }
    std::string getCor() const { return cor; }

    // --- Setters ---
    void setPosic(Point ponto) { posic = ponto; }
    void setAltura(int valor) { altura = valor; }
    void setLargura(int valor) { largura = valor; }
    void setInclinacao(double valor) { inclinacao = valor; }
    void setCor(const std::string& cor) { this->cor = cor; }
};

#endif // CERCA_H
