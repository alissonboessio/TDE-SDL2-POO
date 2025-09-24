#define SDL_MAIN_HANDLED
#include "World.h"
#include "Casa.h"
#include "Arvore.h"
#include "Cerca.h"
#include "Sol.h"
#include "Nuvem.h"
#include "App.h"
#include "Point.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// Função para remover espaços em branco extras
std::string trim(const std::string& s) {
    auto start = s.begin();
    while (start != s.end() && std::isspace((unsigned char)*start)) {
        start++;
    }
    auto end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace((unsigned char)*end));
    return std::string(start, end + 1);
}

std::vector<std::string> split(std::string line) {
    std::vector<std::string> tokens;

    char separador = ';';

    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, separador)) {
        tokens.push_back(trim(token));
    }

    return tokens;
}

World readMundoInfo(std::ifstream& file, std::string& proximoShape) {
    World world = World();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = split(line);
        if (tokens.size() == 1) {
            proximoShape = tokens[0];
            break;
        }

        std::string chave = tokens[0];

        if (chave == "Resolucao") {
            world.setSRD(std::stod(tokens[1]), std::stod(tokens[2]));
        } else if (chave == "Metros") {
            world.setSRU(std::stod(tokens[1]), std::stod(tokens[2]));
        } else if (chave == "Cor") {
            world.setCorFundo(tokens[1]);
        } else {
            std::cerr << "Erro ao ler informacoes do mundo: " << line << "\n";
            exit(-1);
        }
    }
    return world;
}

Casa* readCasaInfo(std::ifstream& file, std::string& proximoShape) {
    Casa* casa = new Casa();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = split(line);
        if (tokens.size() == 1) {
            proximoShape = tokens[0];
            break;
        }

        std::string chave = tokens[0];

        if (chave == "Localizacao") {
            casa->setPosic(Point{std::stod(tokens[1]), std::stod(tokens[2])});
        } else if (chave == "Altura") {
            casa->setAltura(std::stod(tokens[1]));
        } else if (chave == "Largura") {
            casa->setLargura(std::stod(tokens[1]));
        } else if (chave == "CorParede") {
            casa->setCorParede(tokens[1]);
        } else if (chave == "CorTelhado") {
            casa->setCorTelhado(tokens[1]);
        } else if (chave == "CorPorta") {
            casa->setCorPorta(tokens[1]);
        } else if (chave == "Inclinacao") {
            casa->setInclinacao(std::stod(tokens[1]));
        } else if (chave == "CorChamine") {
            casa->setCorChamine(tokens[1]);
        } else if (chave == "CorFumaca") {
            casa->setCorFumaca(tokens[1]);
        }
        else {
            std::cout << "\nAviso: chave desconhecida em Casa -> " << chave;
            exit(-1);
        }
    }

    return casa;
}

Arvore* readArvoreInfo(std::ifstream& file, std::string& proximoShape) {
    Arvore* arvore = new Arvore();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = split(line);
        if (tokens.size() == 1) {
            proximoShape = tokens[0];
            break;
        }

        std::string chave = tokens[0];

        if (chave == "Localizacao") {
            arvore->setPosic(Point{std::stod(tokens[1]), std::stod(tokens[2])});
        } else if (chave == "Altura") {
            arvore->setAltura(std::stod(tokens[1]));
        } else if (chave == "Largura") {
            arvore->setLargura(std::stod(tokens[1]));
        } else if (chave == "CorTronco") {
            arvore->setCorTronco(tokens[1]);
        } else if (chave == "CorFolhas") {
            arvore->setCorFolhas(tokens[1]);
        } else if (chave == "Inclinacao") {
            arvore->setInclinacao(std::stod(tokens[1]));
        } else {
            std::cout << "\nErro ao ler informacoes da arvore: " << chave;
            exit(-1);
        }
    }
    return arvore;
}

Cerca* readCercaInfo(std::ifstream& file, std::string& proximoShape) {
    Cerca* cerca = new Cerca();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = split(line);
        if (tokens.size() == 1) {
            proximoShape = tokens[0];
            break;
        }

        std::string chave = tokens[0];

        if (chave == "Localizacao") {
            cerca->setPosic(Point{std::stod(tokens[1]), std::stod(tokens[2])});
        } else if (chave == "Altura") {
            cerca->setAltura(std::stod(tokens[1]));
        } else if (chave == "Largura") {
            cerca->setLargura(std::stod(tokens[1]));
        } else if (chave == "Cor") {
            cerca->setCor(tokens[1]);
        } else if (chave == "Inclinacao") {
            cerca->setInclinacao(std::stod(tokens[1]));
        } else {
            std::cout << "\nErro ao ler informacoes da cerca: " << chave;
            exit(-1);
        }
    }
    return cerca;
}

Sol* readSolInfo(std::ifstream& file, std::string& proximoShape) {
    Sol* sol = new Sol();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = split(line);
        if (tokens.size() == 1) {
            proximoShape = tokens[0];
            break;
        }

        std::string chave = tokens[0];

        if (chave == "Localizacao") {
            sol->setPosic(Point{std::stod(tokens[1]), std::stod(tokens[2])});
        } else if (chave == "Altura") {
            sol->setAltura(std::stod(tokens[1]));
        } else if (chave == "Largura") {
            sol->setLargura(std::stod(tokens[1]));
        } else if (chave == "Cor") {
            sol->setCor(tokens[1]);
        } else if (chave == "Inclinacao") {
            sol->setInclinacao(std::stod(tokens[1]));
        } else {
            std::cout << "\nErro ao ler informacoes do sol: " << chave;
            exit(-1);
        }
    }
    return sol;
}

Nuvem* readNuvemInfo(std::ifstream& file, std::string& proximoShape) {
    Nuvem* nuvem = new Nuvem();
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto tokens = split(line);
        if (tokens.size() == 1) {
            proximoShape = tokens[0];
            break;
        }

        std::string chave = tokens[0];

        if (chave == "Localizacao") {
            nuvem->setPosic(Point{std::stod(tokens[1]), std::stod(tokens[2])});
        } else if (chave == "Altura") {
            nuvem->setAltura(std::stod(tokens[1]));
        } else if (chave == "Largura") {
            nuvem->setLargura(std::stod(tokens[1]));
        } else if (chave == "Cor") {
            nuvem->setCor(tokens[1]);
        } else if (chave == "Inclinacao") {
            nuvem->setInclinacao(std::stod(tokens[1]));
        } else {
            std::cout << "\nErro ao ler informacoes da nuvem: " << chave;
            exit(-1);
        }
    }
    return nuvem;
}

int main() {
    std::ifstream file("Entrega.csv");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    World world;
    std::vector<Shape*> shapes;
    std::string proximoShape = "";

    while (true) {
        if (proximoShape == "") {
            if (!std::getline(file, line)) break; // acabou arquivo
            if (line.empty()) continue;
        }

        auto tokens = split(line);
        if (tokens.empty()) {
            proximoShape = "";
            continue;
        }

        std::string chave = tokens[0];
        if (proximoShape != "") {
            chave = proximoShape;
        }

        if (chave == "Tela") {
            proximoShape = "";
            world = readMundoInfo(file, proximoShape);
        }
        if (chave == "Casa") {
            proximoShape = "";
            shapes.push_back(readCasaInfo(file, proximoShape));
        }
        if (chave == "Arvore") {
            proximoShape = "";
            shapes.push_back(readArvoreInfo(file, proximoShape));
        }
        if (chave == "Cerca") {
            proximoShape = "";
            shapes.push_back(readCercaInfo(file, proximoShape));
        }
        if (chave == "Sol") {
            proximoShape = "";
            shapes.push_back(readSolInfo(file, proximoShape));
        }
        if (chave == "Nuvem") {
            proximoShape = "";
            shapes.push_back(readNuvemInfo(file, proximoShape));
        }
    }

    file.close();

    App app("SDL Mundo CSV", world);
    app.run(shapes);
    return 0;
}
