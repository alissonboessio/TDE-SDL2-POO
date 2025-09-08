#define SDL_MAIN_HANDLED
#include "World.h"
#include "Casa.h"
#include "Arvore.h"
#include "Cerca.h"
#include "Sol.h"
#include "App.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string &line, char separador = ';') {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, separador)) {
        tokens.push_back(token);
    }
    return tokens;
}

World readMundoInfo(std::ifstream& file) {
    World world = World();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = split(line, ';');
        if (tokens.size() == 1) break;

        std::string chave = tokens[0];

        if (chave == "Resolucao") {
            world.setSRD(std::stoi(tokens[1]),std::stoi(tokens[2]));
        } else if (chave == "Metros") {
            world.setSRU(std::stoi(tokens[1]),std::stoi(tokens[2]));
        } else if (chave == "Cor") {
            world.setCorFundo(tokens[1]);
        } else {
            std::cerr << "Erro ao ler informações do mundo: " << line << "\n";
            exit(-1);
        }
    }
    return world;
}


Casa* readCasaInfo(std::ifstream& file) {
    Casa* casa = new Casa();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = split(line, ';');
        if (tokens.size() == 1) break;

        std::string chave = tokens[0];

        if (chave == "Localizacao") {
            casa->setX(std::stoi(tokens[1]));
            casa->setY(std::stoi(tokens[2]));
        } else if (chave == "Altura") {
            casa->setAltura(std::stoi(tokens[1]));
        } else if (chave == "Largura") {
            casa->setLargura(std::stoi(tokens[1]));
        } else if (chave == "CorParede") {
            casa->setCorParede(tokens[1]);
        } else if (chave == "CorTelhado") {
            casa->setCorTelhado(tokens[1]);
        } else if (chave == "CorPorta") {
            casa->setCorPorta(tokens[1]);
        } else if (chave == "Inclinacao") {
            casa->setInclinacao(std::stoi(tokens[1]));
        } else {
            std::cout << "\nErro ao ler informações da casa: " << chave;
            exit(-1);
        }
    }
    return casa;
}

Arvore* readArvoreInfo(std::ifstream& file) {
    Arvore* arvore = new Arvore();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = split(line, ';');
        if (tokens.size() == 1) break;

        std::string chave = tokens[0];

        if (chave == "Localizacao") {
            arvore->setX(std::stoi(tokens[1]));
            arvore->setY(std::stoi(tokens[2]));
        } else if (chave == "Altura") {
            arvore->setAltura(std::stoi(tokens[1]));
        } else if (chave == "Largura") {
            arvore->setLargura(std::stoi(tokens[1]));
        } else if (chave == "CorTronco") {
            arvore->setCorTronco(tokens[1]);
        } else if (chave == "CorFolhas") {
            arvore->setCorFolhas(tokens[1]);
        } else if (chave == "Inclinacao") {
            arvore->setInclinacao(std::stoi(tokens[1]));
        } else {
            std::cout << "\nErro ao ler informações da arvore: " << chave;
            exit(-1);
        }
    }
    return arvore;
}

Cerca* readCercaInfo(std::ifstream& file) {
    Cerca* cerca = new Cerca();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = split(line, ';');
        if (tokens.size() == 1) break;

        std::string chave = tokens[0];

        if (chave == "Localizacao") {
            cerca->setX(std::stoi(tokens[1]));
            cerca->setY(std::stoi(tokens[2]));
        } else if (chave == "Altura") {
            cerca->setAltura(std::stoi(tokens[1]));
        } else if (chave == "Largura") {
            cerca->setLargura(std::stoi(tokens[1]));
        } else if (chave == "Cor") {
            cerca->setCor(tokens[1]);
        } else if (chave == "Inclinacao") {
            cerca->setInclinacao(std::stoi(tokens[1]));
        } else {
            std::cout << "\nErro ao ler informações da cerca: " << chave;
            exit(-1);
        }
    }
    return cerca;
}

Sol* readSolInfo(std::ifstream& file) {
    Sol* sol = new Sol();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = split(line, ';');
        if (tokens.size() == 1) break;

        std::string chave = tokens[0];

        if (chave == "Localizacao") {
            sol->setX(std::stoi(tokens[1]));
            sol->setY(std::stoi(tokens[2]));
        } else if (chave == "Altura") {
            sol->setAltura(std::stoi(tokens[1]));
        } else if (chave == "Largura") {
            sol->setLargura(std::stoi(tokens[1]));
        } else if (chave == "Cor") {
            sol->setCor(tokens[1]);
        } else if (chave == "Inclinacao") {
            sol->setInclinacao(std::stoi(tokens[1]));
        } else {
            std::cout << "\nErro ao ler informações do sol: " << chave;
            exit(-1);
        }
    }
    return sol;
}


//EAE MEU TRANQUILIDADE?
int main() {

    std::ifstream file("Exemplo.csv");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    World world;
    std::vector<Shape*> shapes;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        auto tokens = split(line, ';');

        if (tokens.empty()) continue;

        std::string chave = tokens[0];

        if (chave == "Tela") {
            world = readMundoInfo(file);
        } else if (chave == "Casa") {
            shapes.push_back(readCasaInfo(file));
        } else if (chave == "Arvore") {
            shapes.push_back(readArvoreInfo(file));
        } else if (chave == "Cerca") {
            shapes.push_back(readCercaInfo(file));
        } else if (chave == "Sol") {
            shapes.push_back(readSolInfo(file));
        }
    }

    file.close();

    App app("SDL Orientado a Objetos", 640, 480);
    app.run();
    return 0;
}
