#include "App.h"
#include "Circle.h"
#include "CircleFilled.h"
#include "CircleFilledAA.h"
#include "Casa.h"
#include "World.h"

App::App(const std::string& title, World mundo)
    : window(nullptr), surface(nullptr), running(false),
      width(mundo.getSRDWidth()), height(mundo.getSRDHeight()), title(title), mundo(mundo) {

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

void App::run(const std::vector<Shape*>& shapes) {
    running = true;

    while (running) {

        // Limpar fundo

        HtmlColor hc = HtmlColor();
        clear(hc.getColorUint32(getMundo().getCorFundo(), surface));

        for (auto shape : shapes) {
            shape->draw(surface, getMundo());

        }

        handleEvents();

        // Atualizar tela
        present();
        //std::cin.get();
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
            mundo.setSRD(surface->w, surface->h);
            std::cout << "Size changed: " << width << ", " << height << "\n";
        }

    }
}

void App::clear(Uint32 color) {
    SDL_FillRect(surface, NULL, color);
}

void App::present() {
    SDL_UpdateWindowSurface(window);
}
