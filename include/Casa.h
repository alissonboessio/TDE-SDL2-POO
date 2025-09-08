#ifndef CASA_H
#define CASA_H

#include <SDL2/SDL.h>
#include "Shape.h"
#include "Primitives.h"
#include <string>

class Casa : public Shape {
private:
    int x, y, altura, largura, inclinacao;
    std::string corParede, corTelhado, corPorta; // utilizar getColor do Primitives

public:
    Casa() {}

    void draw(SDL_Surface* surface) override {
        if (!surface) return;

        // implementar desenho

    }

    // --- Getters ---
    int getX() const { return x; }
    int getY() const { return y; }
    int getAltura() const { return altura; }
    int getLargura() const { return largura; }
    std::string getCorParede() const { return corParede; }
    std::string getCorTelhado() const { return corTelhado; }
    std::string getCorPorta() const { return corPorta; }
    int getInclinacao() const { return inclinacao; }

    // --- Setters ---
    void setX(int valor) { x = valor; }
    void setY(int valor) { y = valor; }
    void setAltura(int valor) { altura = valor; }
    void setLargura(int valor) { largura = valor; }
    void setInclinacao(int valor) { inclinacao = valor; }
    void setCorParede(const std::string& cor) { corParede = cor; }
    void setCorTelhado(const std::string& cor) { corTelhado = cor; }
    void setCorPorta(const std::string& cor) { corPorta = cor; }

};

#endif // CASA_H
