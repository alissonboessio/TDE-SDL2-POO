#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
private:
    double x, y;

public:
    // Construtor
    Point(double newX = 0, double newY = 0) {
        x = newX;
        y = newY;
    }

    // Getters
    double getX() {
        return x;
    };

    double getY() {
        return y;
    }

    // Setters
    void setX(double newX){
        x = newX;
    }
    void setY(double newY) {
        y = newY;
    }

    // Método utilitário
    void print() {
      std::cout << "Point(" << x << "," << y << ")" << std::endl;
    }
};

#endif

