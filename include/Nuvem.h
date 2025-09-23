#ifndef NUVEM_H
#define NUVEM_H

#include <SDL2/SDL.h>
#include "Shape.h"
#include "Primitives.h"
#include <string>

class Nuvem : public Shape {
private:
    int altura, largura, inclinacao;
    std::string cor;
    std::vector<double> raioCirculos;
    std::vector<Point> posicCirculos, base;
    Point posic;

    public:
        Nuvem() {
            raioCirculos = {0.15, 0.082, 0.1, 0.15, 0.05, 0.1, 0.05, 0.1, 0.1, 0.1, 0.16, 0.08, 0.18, 0.1, 0.1};

            posicCirculos = {
                {0.15, 0.7}, {0.3, 0.8}, {0.4, 0.8}, {0.55, 0.8}, {0.65, 0.8}, {0.72, 0.8}, {0.83, 0.8}, {0.9, 0.65}, {0.9, 0.5}, {0.85, 0.25}, {0.65, 0.2}, {0.5, 0.2}, {0.35, 0.2}, {0.15, 0.2}, {0.1, 0.5}
            };
            base = {{0.1, 0.2}, {0.9, 0.2}, {0.9, 0.8}, {0.1, 0.8}};

            altura = 1;
            largura = 1;
            inclinacao = 0;
        }

    void draw(SDL_Surface* surface, World mundo) override {
        if (!surface) return;


        HtmlColor hc = HtmlColor();

        Uint32 corNuvem = hc.getColorUint32(cor, surface);

        for (int i = 0; i < raioCirculos.size(); i++) {

            Point posicCirculo = Primitives::scalePoint(posicCirculos[i], largura, altura, 0,0);
            posicCirculo = Primitives::translatePoint(posicCirculo, posic.getX(), posic.getY());
            posicCirculo = Primitives::rotatePoint(posicCirculo, inclinacao, posic.getX(), posic.getY());
            posicCirculo = mundo.worldToScreen(posicCirculo);
            double raioCirc = mundo.worldToScreen(Primitives::scaleLength(raioCirculos[i], largura, altura));
            Primitives::drawCircle(surface, posicCirculo.getX(), posicCirculo.getY(), raioCirc, corNuvem);
            Primitives::floodFill(surface, posicCirculo.getX(), posicCirculo.getY() + raioCirc - 5, corNuvem, corNuvem);
        }


        std::vector<Point> rectTela = base;
        Primitives::scalePolygon(rectTela, largura, altura, 0, 0);
        Primitives::translatePolygon(rectTela, posic.getX(), posic.getY());
        Primitives::rotatePolygon(rectTela, inclinacao, posic.getX(), posic.getY());
        for (auto& p : rectTela) p = mundo.worldToScreen(p);

        Primitives::drawPolygon(surface, rectTela, corNuvem);
        Primitives::scanFill(surface, rectTela, corNuvem);


    }

    // --- Getters ---
    Point getPosicao() const { return posic; }
    int getAltura() const { return altura; }
    int getLargura() const { return largura; }
    std::string getCor() const { return cor; }
    double getInclinacao() const { return inclinacao; }

    // --- Setters ---
    void setPosic(Point ponto) { posic = ponto; }
    void setAltura(int valor) { altura = valor; }
    void setLargura(int valor) { largura = valor; }
    void setInclinacao(double valor) { inclinacao = valor; }
    void setCor(const std::string& cor) { this->cor = cor; }

};

#endif // NUVEM_H
