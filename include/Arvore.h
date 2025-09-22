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
    std::string corTronco, corFolhas; // usar HtmlColor em Primitives
    Point posic, posicCorTronco, folhaEsquerda, folhaCentral, folhaDireita;
    std::vector<Point> pontosTroncoEsquerdo, pontosTroncoDireito, pontosTroncoFechamento, posicCorFolhas;

public:
    Arvore() {
        // curvas do tronco em SRU normalizadas (0..1)
        pontosTroncoEsquerdo = {
            {0.35, 0}, {0.5, 0.3}, {0.35, 0.6}
        };
        pontosTroncoDireito = {
            {0.65, 0}, {0.5, 0.3}, {0.65, 0.6}
        };

        // (retângulo “base” do tronco — ainda útil se quiser fallback)
        pontosTroncoFechamento = {
            {0.35, 0},{0.65, 0}, {0.35, 0.6}, {0.65, 0.6}
        };

        posicCorTronco = {0.5, 0.3};

        // copas
        folhaCentral = {0.5, 0.7};
        raioFolhaCentral = 0.25;
        folhaEsquerda = {0.3, 0.6};
        raioFolhaEsquerda = 0.2;
        folhaDireita = {0.7, 0.6};
        raioFolhaDireita = 0.2;

        altura = 1;
        largura = 1;
        inclinacao = 0;
    }

    void draw(SDL_Surface* surface, World mundo) override {
        if (!surface) return;

        HtmlColor hc = HtmlColor();
        Uint32 corTroncoI = hc.getColorUint32(corTronco, surface);
        Uint32 corFolhasI = hc.getColorUint32(corFolhas, surface);

        std::vector<Point> troncoEsq = pontosTroncoEsquerdo;
        std::vector<Point> troncoDir = pontosTroncoDireito;

        Primitives::scalePolygon(troncoEsq, largura, altura, 0, 0);
        Primitives::translatePolygon(troncoEsq, posic.getX(), posic.getY());
        Primitives::rotatePolygon(troncoEsq, inclinacao, posic.getX(), posic.getY());

        Primitives::scalePolygon(troncoDir, largura, altura, 0, 0);
        Primitives::translatePolygon(troncoDir, posic.getX(), posic.getY());
        Primitives::rotatePolygon(troncoDir, inclinacao, posic.getX(), posic.getY());

        for (auto& p : troncoEsq) p = mundo.worldToScreen(p);
        for (auto& p : troncoDir) p = mundo.worldToScreen(p);

        std::vector<Point> curvaEsq = Primitives::sampleBezier(troncoEsq[0], troncoEsq[1], troncoEsq[2], 30);
        std::vector<Point> curvaDir = Primitives::sampleBezier(troncoDir[0], troncoDir[1], troncoDir[2], 30);

        //constrói tronco
        std::vector<Point> troncoFechado;
        troncoFechado.reserve(curvaEsq.size() + curvaDir.size());
        troncoFechado.insert(troncoFechado.end(), curvaEsq.begin(), curvaEsq.end());
        troncoFechado.insert(troncoFechado.end(), curvaDir.rbegin(), curvaDir.rend());

        //scanline
        Primitives::scanFill(surface, troncoFechado, corTroncoI);

        //redesenhar contorno para acabamento (curvas + linhas topo/base)
        Primitives::drawBezier(surface, troncoEsq[0], troncoEsq[1], troncoEsq[2], corTroncoI);
        Primitives::drawBezier(surface, troncoDir[0], troncoDir[1], troncoDir[2], corTroncoI);

        //linhas de topo e base para ficar bem fechado visualmente
        Primitives::drawLine(surface, troncoEsq.front(), troncoDir.front(), corTroncoI);   // base
        Primitives::drawLine(surface, troncoEsq.back(),  troncoDir.back(),  corTroncoI);   // topo

        // ===== COPAS (círculos preenchidos) =====
        Point cCentro = Primitives::scalePoint(folhaCentral, largura, altura, 0, 0);
        cCentro = Primitives::translatePoint(cCentro, posic.getX(), posic.getY());
        cCentro = Primitives::rotatePoint(cCentro, inclinacao, posic.getX(), posic.getY());
        cCentro = mundo.worldToScreen(cCentro);
        double rCentro = mundo.worldToScreen(Primitives::scaleLength(raioFolhaCentral, largura, altura));
        Primitives::drawCircle(surface, cCentro.getX(), cCentro.getY(), rCentro, corFolhasI);
        Primitives::floodFill(surface, cCentro.getX(), cCentro.getY(), corFolhasI, corFolhasI);

        Point cEsq = Primitives::scalePoint(folhaEsquerda, largura, altura, 0, 0);
        cEsq = Primitives::translatePoint(cEsq, posic.getX(), posic.getY());
        cEsq = Primitives::rotatePoint(cEsq, inclinacao, posic.getX(), posic.getY());
        cEsq = mundo.worldToScreen(cEsq);
        double rEsq = mundo.worldToScreen(Primitives::scaleLength(raioFolhaEsquerda, largura, altura));
        Primitives::drawCircle(surface, cEsq.getX(), cEsq.getY(), rEsq, corFolhasI);
        Primitives::floodFill(surface, cEsq.getX() - rEsq / 2, cEsq.getY(), corFolhasI, corFolhasI);

        Point cDir = Primitives::scalePoint(folhaDireita, largura, altura, 0, 0);
        cDir = Primitives::translatePoint(cDir, posic.getX(), posic.getY());
        cDir = Primitives::rotatePoint(cDir, inclinacao, posic.getX(), posic.getY());
        cDir = mundo.worldToScreen(cDir);
        double rDir = mundo.worldToScreen(Primitives::scaleLength(raioFolhaDireita, largura, altura));
        Primitives::drawCircle(surface, cDir.getX(), cDir.getY(), rDir, corFolhasI);
        Primitives::floodFill(surface, cDir.getX() + rDir / 2, cDir.getY(), corFolhasI, corFolhasI);
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
