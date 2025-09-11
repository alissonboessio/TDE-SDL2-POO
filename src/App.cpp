#include "App.h"
#include "Rectangle.h"
#include "Circle.h"
#include "CircleFilled.h"
#include "CircleFilledAA.h"

App::App(const std::string& title, int w, int h)
    : window(nullptr), surface(nullptr), running(false),
      width(w), height(h), title(title) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cerr << "Erro ao criar janela: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    surface = SDL_GetWindowSurface(window);
}

App::~App() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::run() {
    running = true;

    while (running) {


        // Limpar fundo
        clear(255, 255, 255);

        /*Uint32 red = Primitives::rgbToUint32(surface, 255, 0, 0);
        Uint32 green = Primitives::rgbToUint32(surface, 0, 255, 0);
        Uint32 blue = Primitives::rgbToUint32(surface, 0, 0, 255);
        Uint32 black = Primitives::rgbToUint32(surface, 0, 0, 0);*/


        // Criar um retângulo vermelho
       /* Rectangle rect(50, 50, 200, 150, red);
        rect.draw(surface);

        Circle circ(300, 300, 100, black);
        circ.draw(surface);

        CircleFilled circf(300, 300, 70, green);
        circf.draw(surface);

        CircleFilledAA circfa(500, 100, 70, blue);
        circfa.draw(surface);*/

        Primitives::Point pontos[4];

        pontos[0].x = 10;
        pontos[0].y = 10;

        pontos[1].x = 300;
        pontos[1].y = 10;

        pontos[2].x = 300;
        pontos[2].y = 200;

        pontos[3].x = 10;
        pontos[3].y = 200;

        Primitives::drawPolygon(surface, pontos, 4, Primitives::getColor(surface, "Red"));

        Primitives::translatePolygon(pontos, 4, 30, 30);

        Primitives::drawPolygon(surface, pontos, 4, Primitives::getColor(surface, "Blue"));


        handleEvents();

        // Atualizar tela
        present();
    }
}

void App::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_WINDOWEVENT &&
            event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
            surface = SDL_GetWindowSurface(window);
            width = surface->w;
            height = surface->h;
            std::cout << "Size changed: " << width << ", " << height << "\n";
        }

    }
}

void App::clear(Uint8 r, Uint8 g, Uint8 b) {
    Uint32 color = SDL_MapRGB(surface->format, r, g, b);
    SDL_FillRect(surface, NULL, color);
}

void App::present() {
    SDL_UpdateWindowSurface(window);
}
