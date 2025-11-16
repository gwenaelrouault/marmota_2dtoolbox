#include "editor_menu.h"

using namespace marmot::studio;

void MainMenu::display() {
    static bool open_create = false;
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Fichier"))
        {
            if (ImGui::MenuItem("Nouveau"))
            {
                open_create = true;
            }
            ImGui::MenuItem("Ouvrir");
            ImGui::MenuItem("Quitter");
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}