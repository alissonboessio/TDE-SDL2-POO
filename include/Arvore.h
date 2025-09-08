#ifndef ARVORE_H
#define ARVORE_H

#include <SDL2/SDL.h>
#include "Shape.h"
#include "Primitives.h"
#include <string>

class Arvore : public Shape {
private:
    int x, y, altura, largura, inclinacao;
    std::string corTronco, corFolhas; // utilizar getColor do Primitives

public:
    Arvore() {}

    void draw(SDL_Surface* surface) override {
        if (!surface) return;

        // implementar desenho

    }

    // --- Getters ---
    int getX() const { return x; }
    int getY() const { return y; }
    int getAltura() const { return altura; }
    int getLargura() const { return largura; }
    std::string getCorTronco() const { return corTronco; }
    std::string getCorFolhas() const { return corFolhas; }
    int getInclinacao() const { return inclinacao; }

    // --- Setters ---
    void setX(int valor) { x = valor; }
    void setY(int valor) { y = valor; }
    void setAltura(int valor) { altura = valor; }
    void setLargura(int valor) { largura = valor; }
    void setInclinacao(int valor) { inclinacao = valor; }
    void setCorTronco(const std::string& cor) { corTronco = cor; }
    void setCorFolhas(const std::string& cor) { corFolhas = cor; }

};

#endif // ARVORE_H
