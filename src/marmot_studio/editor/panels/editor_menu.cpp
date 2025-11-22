#include "editor_menu.h"
#include "ImGuiFileDialog.h"

using namespace marmot::studio;

void MainMenu::display()
{
    static bool open_create = false;
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Fichier"))
        {
            if (ImGui::MenuItem("Nouveau"))
            {
                IGFD::FileDialogConfig config;
                config.path = ".";
                config.flags = ImGuiFileDialogFlags_Modal;
                config.sidePaneWidth = 200;
                open_create = true;
                ImGuiFileDialog::Instance()->OpenDialog(
                    "NewProject",
                    "Sélectionnez un nouveau projet",
                    ".m",
                    config);
            }
            ImGui::MenuItem("Ouvrir");
            ImGui::MenuItem("Quitter");
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    if (ImGuiFileDialog::Instance()->Display("NewProject"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            _model->_filename = ImGuiFileDialog::Instance()->GetFilePathName();
        }
        ImGuiFileDialog::Instance()->Close();
    }
}