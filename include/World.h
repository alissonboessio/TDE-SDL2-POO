#ifndef WORLD_H
#define WORLD_H

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
    std::string getCorFundo() const { return corFundo; }

private:
    int SRD_width, SRD_height;
    int SRU_width, SRU_height;
    std::string corFundo;
};

#endif // WORLD_H
