#define SDL_MAIN_HANDLED
#include <SDL3/SDL_main.h>

import <SDL3/SDL.h>;
import openhomm.math;
import openhomm.application;
import openhomm.core;
import openhomm.io;
import std;

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
    SDL_SetMainReady();

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        core::error("SDL_Init fail {}\n", SDL_GetError());
        return 1;
    }

    SDL_LogSetOutputFunction([](void* userdata, int category, SDL_LogPriority priority, const char* message) {
        core::log_level level = [priority]() {
            switch (priority) {
            case SDL_LOG_PRIORITY_VERBOSE:  return core::log_level::trace;
            case SDL_LOG_PRIORITY_DEBUG:    return core::log_level::debug;
            case SDL_LOG_PRIORITY_INFO:     return core::log_level::info;
            case SDL_LOG_PRIORITY_WARN:     return core::log_level::warning;
            case SDL_LOG_PRIORITY_ERROR:    return core::log_level::error;
            case SDL_LOG_PRIORITY_CRITICAL: return core::log_level::critical;
            default:                        return core::log_level::none;
            }
        }();

        core::log(level, "{}", message);
    }, nullptr);

    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    SDL_Window* window = SDL_CreateWindow("Openhomm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
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

        //Clear screen
        SDL_RenderClear(renderer);

        //Render texture to screen
        //SDL_RenderCopy(renderer, gTexture, NULL, NULL);

        //Update screen
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
