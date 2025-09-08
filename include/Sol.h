#ifndef SOL_H
#define SOL_H

#include <SDL2/SDL.h>
#include "Shape.h"
#include "Primitives.h"
#include <string>

class Sol : public Shape {
private:
    int x, y, altura, largura, inclinacao;
    std::string cor; // utilizar getColor do Primitives

public:
    Sol() {}

    void draw(SDL_Surface* surface) override {
        if (!surface) return;

        // implementar desenho

    }

    // --- Getters ---
    int getX() const { return x; }
    int getY() const { return y; }
    int getAltura() const { return altura; }
    int getLargura() const { return largura; }
    std::string getCor() const { return cor; }
    int getInclinacao() const { return inclinacao; }

    // --- Setters ---
    void setX(int valor) { x = valor; }
    void setY(int valor) { y = valor; }
    void setAltura(int valor) { altura = valor; }
    void setLargura(int valor) { largura = valor; }
    void setInclinacao(int valor) { inclinacao = valor; }
    void setCor(const std::string& cor) { this->cor = cor; }

};

#endif // SOL_H
