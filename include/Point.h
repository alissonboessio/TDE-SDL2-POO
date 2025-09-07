#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
private:
    int x, y;

public:
    // Construtor
    Point(int newX = 0, int newY = 0) {
        x = newX;
        y = newY;
    }

    // Getters
    int getX() {
        return x;
    };

    int getY() {
        return y;
    }

    // Setters
    void setX(int newX){
        x = newX;
    }
    void setY(int newY) {
        y = newY;
    }

    // Método utilitário
    void print() {
      std::cout << "Point(" << x << "," << y << ")" << std::endl;
    }
};

#endif

