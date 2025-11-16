#include <filesystem>
#include <string>
#include <stdio.h>
#include <memory>
#include "imgui.h"
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <SDL.h>
#include <SDL_image.h>
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <CLI/CLI.hpp>
#include "yaml-cpp/yaml.h"
#include "editor_main_panel.h"
#include "assets_db.h"

constexpr int WIN_WIDTH = 1280;
constexpr int WIN_HEIGHT= 720;

using namespace marmot;

int main(int argc, char** argv) {
    // parse arguments ========================================================
    CLI::App app{"GWEN 2D"};
    std::string config_file;
    app.add_option("-c,--config", config_file, "Chemin vers le fichier de configuration du serveur")->required();
    CLI11_PARSE(app, argc, argv);

    // load config file =======================================================
    std::string log_config;
    YAML::Node config = YAML::LoadFile(config_file);
    auto logger_config = config["logger"].as<std::string>();
    std::filesystem::path workdir_path = config["workdir"].as<std::string>();

    // configure logger =======================================================
    log4cpp::PropertyConfigurator::configure(logger_config.c_str());
    log4cpp::Category& logger = log4cpp::Category::getRoot();

    // init SDL ===============================================================
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
    SDL_Window* window = SDL_CreateWindow("ImGui SDL2 Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Erreur SDL_image: " << IMG_GetError() << "\n";
        return 1;
    }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
    ImGuiIO& io = ImGui::GetIO(); 

    // init editor ============================================================
    auto db = std::make_shared<marmota::AssetsDB>(logger, workdir_path);
    auto worker = std::make_shared<marmot::Worker>();
    auto editor = std::make_unique<studio::MainPanel>(renderer, io, logger, worker, workdir_path, db);

    // main loop   ============================================================
    bool done = false;
    SDL_Event event;
    while (!done)
    {
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) done = true;
        }

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Spritesheet Panel");
        editor->display();
        ImGui::End();

        ImGui::Render();
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }

    // cleanup ================================================================
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    worker->stop();
    return 0;
}