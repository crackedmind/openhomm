//#include <iostream>
//#include <format>

import <format>;
import <iostream>;
import <SDL2/SDL.h>;
import openhomm.math;
import openhomm.application;


#if defined(WIN32) && defined(_MSC_VER)
#   ifdef __clang__
#       pragma clang diagnostic push
#       pragma clang diagnostic ignored "-Wlanguage-extension-token"
#       pragma clang diagnostic ignored "-Wmissing-variable-declarations"
#   endif
extern "C" {
    // https://gpuopen.com/amdpowerxpressrequesthighperformance/
    _declspec(dllexport) unsigned long AmdPowerXpressRequestHighPerformance = 0x00000001;
    // https://docs.nvidia.com/gameworks/content/technologies/desktop/optimus.htm
    _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
}
#   ifdef __clang__
#       pragma clang diagnostic pop
#   endif
#endif

int main(int argc, char** argv) {
    Application app(argc, argv);

    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        std::cout << std::format("SDL_Init fail {}\n", SDL_GetError());
        return 1;
    }

    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    SDL_Window* window = SDL_CreateWindow("Openhomm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        return 1;
    }

    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;
            }
        }
    }


    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}