#ifndef WORLD_H
#define WORLD_H

#include "Point.h"

#include <string>

class World
{
public:
    World() {}
    void setSRD(int width, int height) { SRD_width = width; SRD_height = height; }
    void setSRU(int width, int height) { SRU_width = width; SRU_height = height; }
    void setCorFundo(const std::string& cor) { corFundo = cor; }

    int getSRDWidth() const { return SRD_width; }
    int getSRDHeight() const { return SRD_height; }
    int getSRUHeight() const { return SRU_height; }
    int getSRUWidth() const { return SRU_width; }
    std::string getCorFundo() const { return corFundo; }

    Point worldToScreen(Point p) const {
        double xScreen = (p.getX() / static_cast<double>(SRU_width)) * SRD_width;
        double yScreen = SRD_height - (p.getY() / static_cast<double>(SRU_height)) * SRD_height;

        return {xScreen, yScreen};
    }

    double worldToScreen(double length) const {
        return (length / static_cast<double>(SRU_width)) * SRD_width;
    }

private:
    int SRD_width, SRD_height;
    int SRU_width, SRU_height;
    std::string corFundo;
};

#endif // WORLD_H
