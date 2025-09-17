#ifndef SOL_H
#define SOL_H

#include <SDL2/SDL.h>
#include "Shape.h"
#include "Primitives.h"
#include <string>

class Sol : public Shape {
private:
    int altura, largura, inclinacao;
    std::string cor;
    double raio;
    Point posic, posicSol;
    std::vector<Point> pontosRaios;

public:
    Sol() {

        raio = 0.5;
        posicSol = {0.5, 0.5};
        pontosRaios = {
            {0, 0.5}, {0.25, 0.5}, {0.5, 1}, {0.5, 0.75}, {0.75, 0.5}, {1, 0.5}, {0.5, 0}, {0.5, 0.25}
        };

        altura = 1;
        largura = 1;
        inclinacao = 0;
    }

    void draw(SDL_Surface* surface, World mundo) override {
        if (!surface) return;

        Uint32 corSol = Primitives::getColor(surface, cor);

        Point centroSol = Primitives::scalePoint(posicSol, largura, altura, 0,0);
        centroSol = mundo.worldToScreen(Primitives::translatePoint(centroSol, posic.getX(), posic.getY()));
        double raioSol = mundo.worldToScreen(Primitives::scaleLength(raio, largura, altura));

        Primitives::drawCircle(surface, centroSol.getX(), centroSol.getY(), raioSol, corSol);
        Primitives::floodFill(surface, centroSol.getX(), centroSol.getY(), corSol, corSol);

        std::vector<Point> raiosTela;
        raiosTela.reserve(pontosRaios.size());
        for (auto p : pontosRaios)
            raiosTela.push_back(p);

        Primitives::scalePolygon(raiosTela, largura, altura, 0,0);
        Primitives::translatePolygon(raiosTela, posic.getX(), posic.getY());

        for (auto& p : raiosTela)
            p = mundo.worldToScreen(p);

        for (int i = 0; i + 1 < raiosTela.size(); i += 2) {
            Point p1 = raiosTela[i];
            Point p2 = raiosTela[i + 1];
            Primitives::drawLine(surface, p1, p2, corSol);
        }


    }

    // --- Getters ---
    Point getPosicao() const { return posic; }
    int getAltura() const { return altura; }
    int getLargura() const { return largura; }
    std::string getCor() const { return cor; }
    int getInclinacao() const { return inclinacao; }

    // --- Setters ---
    void setPosic(Point ponto) { posic = ponto; }
    void setAltura(int valor) { altura = valor; }
    void setLargura(int valor) { largura = valor; }
    void setInclinacao(int valor) { inclinacao = valor; }
    void setCor(const std::string& cor) { this->cor = cor; }

};

#endif // SOL_H
