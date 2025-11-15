#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <string>

void draw_menu_bar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Fichier")) {
            ImGui::MenuItem("Nouveau");
            ImGui::MenuItem("Ouvrir");
            ImGui::MenuItem("Quitter");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void draw_device_screen(double height) {
    ImGui::BeginChild("SDL Frame", ImVec2(0, height), true);
    ImGui::Text("Zone de rendu SDL (simulée)");
    ImGui::Dummy(ImVec2(400, 200));
    ImGui::EndChild();
}

void draw_main_panel(ImGuiIO& io) {
    char text_buffer[4096] = "Écris ton code ici...";
    ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_Always);
    ImGui::Begin("Main Window", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse);

    ImGui::Columns(2);

    // Colonne de gauche : éditeur de texte
    ImGui::BeginChild("TextEditor", ImVec2(0, 0), true);
    ImGui::Text("Éditeur de texte");
    ImGui::InputTextMultiline("##Text", text_buffer, IM_ARRAYSIZE(text_buffer),
                                  ImVec2(-FLT_MIN, ImGui::GetContentRegionAvail().y));
    ImGui::EndChild();
    ImGui::NextColumn();

    // Colonne de droite : split vertical
    float childHeight = ImGui::GetContentRegionAvail().y / 2.0f;

    draw_device_screen(childHeight);

    ImGui::BeginChild("ImGui Panel", ImVec2(0, 0), true);
    ImGui::Text("Panneau ImGui en bas");
    ImGui::Button("Exécuter");
    ImGui::SameLine();
    ImGui::Button("Analyser");
    ImGui::EndChild();

    ImGui::End();
}

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);

    // SDL OpenGL context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_Window* window = SDL_CreateWindow("ImGui + SDL + OpenGL",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // vsync

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                running = false;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        draw_menu_bar();

        draw_main_panel(io);
        
        ImGui::Render();
        glViewport(0, 0, 1280, 720);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
