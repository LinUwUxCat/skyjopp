#include "render.hpp"

/**
 * @brief Construct a new Renderer object, initialising SDL and, if enabled, Dear ImGui.
 * @param name The window name.
 */
Renderer::Renderer(const char* name){
    has_to_exit = false;
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920,1080,SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL){
        exit_err("Window is null!");
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL){
        exit_err("Renderer is null!");
    }
    #ifdef USEDEARIMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);
    #endif //USEDEARIMGUI
}

Renderer::Renderer(){
    Renderer("Skyjo");
}

void Renderer::render(){
    if (has_to_exit) exit(0);
    #ifdef USEDEARIMGUI
    render_imgui();
    #endif //USEDEARIMGUI
    SDL_SetRenderDrawColor(renderer, (Uint8)0, (Uint8)0, (Uint8)0, (Uint8)255);
    SDL_RenderClear(renderer);
    //render(renderer); Main game render
    #ifdef USEDEARIMGUI
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    #endif //USEDEARIMGUI
    SDL_RenderPresent(renderer);
}
/**
 * @brief Render all Dear ImGui components. 
 */
void Renderer::render_imgui(){
    #ifndef USEDEARIMGUI
    return;
    #endif //USEDEARIMGUI
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    if(ImGui::BeginMainMenuBar()){
        if (ImGui::BeginMenu("Debug")){
            ImGui::MenuItem("Quit", NULL, &has_to_exit);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    ImGui::Render();
}

