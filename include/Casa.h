#ifndef CASA_H
#define CASA_H

#include "HtmlColor.h"
#include <SDL2/SDL.h>
#include "Shape.h"
#include "Primitives.h"
#include <string>

class Casa : public Shape {
protected:
    int altura, largura;
    double inclinacao;
    Point posic;
    std::string corParede, corTelhado, corPorta, corChamine, corFumaca;
    std::vector<Point> pontosParede, pontosTeto, pontosPorta, pontosChamine;

public:
    Casa() {
        altura = 1;
        largura = 1;
        inclinacao = 0;
    }

    std::vector<Point> fumacaRelativa = {
        {0.2, 0.8},
        {0.15, 0.9},
        {0.1, 1.0}
    };

    void draw(SDL_Surface* surface, World mundo) override {
        if (!surface) return;

        HtmlColor hc;

        // --- PAREDE ---
        Uint32 corParedeTela = hc.getColorUint32(corParede, surface);
        std::vector<Point> parede = {{0.1,0}, {0.9,0}, {0.9,0.5}, {0.1,0.5}};
        Primitives::scalePolygon(parede, largura, altura, 0, 0);
        Primitives::translatePolygon(parede, posic.getX(), posic.getY());
        Primitives::rotatePolygon(parede, inclinacao, posic.getX(), posic.getY());
        for (auto &p : parede) p = mundo.worldToScreen(p);
        Primitives::drawPolygon(surface, parede, corParedeTela);
        Primitives::scanFill(surface, parede, corParedeTela);

        // --- TELHADO ---
        Uint32 corTelhadoTela = hc.getColorUint32(corTelhado, surface);
        std::vector<Point> telhado = {{0,0.5}, {1,0.5}, {0.5,0.8}};
        Primitives::scalePolygon(telhado, largura, altura, 0, 0);
        Primitives::translatePolygon(telhado, posic.getX(), posic.getY());
        Primitives::rotatePolygon(telhado, inclinacao, posic.getX(), posic.getY());
        for (auto &p : telhado) p = mundo.worldToScreen(p);
        Primitives::drawPolygon(surface, telhado, corTelhadoTela);
        Primitives::scanFill(surface, telhado, corTelhadoTela);

        // --- PORTA ---
        Uint32 corPortaTela = hc.getColorUint32(corPorta, surface);
        std::vector<Point> porta = {{0.4,0}, {0.6,0}, {0.6,0.25}, {0.4,0.25}};
        Primitives::scalePolygon(porta, largura, altura, 0, 0);
        Primitives::translatePolygon(porta, posic.getX(), posic.getY());
        Primitives::rotatePolygon(porta, inclinacao, posic.getX(), posic.getY());
        for (auto &p : porta) p = mundo.worldToScreen(p);
        Primitives::drawPolygon(surface, porta, corPortaTela);
        Primitives::scanFill(surface, porta, corPortaTela);

        // --- CHAMINÉ ---
        Uint32 corChamineTela = hc.getColorUint32(corChamine, surface);
        std::vector<Point> chamine = {
            {0.15,0.5}, {0.28,0.5}, {0.28,0.7}, {0.15,0.7}
        };
        Primitives::scalePolygon(chamine, largura, altura, 0, 0);
        Primitives::translatePolygon(chamine, posic.getX(), posic.getY());
        Primitives::rotatePolygon(chamine, inclinacao, posic.getX(), posic.getY());
        for (auto &p : chamine) p = mundo.worldToScreen(p);
        Primitives::drawPolygon(surface, chamine, corChamineTela);
        Primitives::scanFill(surface, chamine, corChamineTela);

        // --- FUMAÇA ---
        Uint32 corFumacaTela = hc.getColorUint32(corFumaca, surface);
        double raioBaseSRU = 0.07; // fumaça menor e mais realista

        for (int i = 0; i < (int)fumacaRelativa.size(); i++) {
            Point centro = Primitives::scalePoint(fumacaRelativa[i], largura, altura, 0, 0);
            centro = Primitives::translatePoint(centro, posic.getX(), posic.getY());
            centro = Primitives::rotatePoint(centro, inclinacao, posic.getX(), posic.getY());
            centro = mundo.worldToScreen(centro);

            // raio decresce a cada círculo
            double raioSRU = raioBaseSRU - i * 0.02;
            int raioTela = mundo.worldToScreen(Primitives::scaleLength(raioSRU, largura, altura));

            Primitives::drawCircle(surface, centro.getX(), centro.getY(), raioTela, corFumacaTela);
            Primitives::floodFill(surface, centro.getX(), centro.getY(), corFumacaTela, corFumacaTela);

        }
    }

    // --- Getters/Setters ---
    Point getPosicao() const { return posic; }
    int getAltura() const { return altura; }
    int getLargura() const { return largura; }
    double getInclinacao() const { return inclinacao; }
    std::string getCorParede() const { return corParede; }
    std::string getCorTelhado() const { return corTelhado; }
    std::string getCorPorta() const { return corPorta; }
    std::string getCorChamine() const { return corChamine; }
    std::string getCorFumaca() const { return corFumaca; }

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
