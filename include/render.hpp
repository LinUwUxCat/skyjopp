#ifndef _SKYJO_RENDER
#define _SKYJO_RENDER

#include "messages.hpp"
#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer.h"
class Renderer{
    public:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool has_to_exit;
        Renderer(const char* name);
        Renderer();
        void render();
        void render_imgui();

};

#endif //_SKYJO_RENDER