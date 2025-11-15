#include "editor_main_panel.h"
#include "ImGuiFileDialog.h"

using namespace marmot;

void MainPanel::display()
{
    draw_menu_bar();
    draw_main_panel();
}

void MainPanel::draw_menu_bar()
{
    static bool open_create = false;
    static std::string project_file;
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

void MainPanel::draw_main_panel()
{
    static char input_buf[256] = "";
    ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Always);
    ImGui::SetNextWindowSize(_io.DisplaySize, ImGuiCond_Always);
    ImGui::Begin("#Main Window", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse);

    ImGui::Columns(2);

    // Colonne de gauche : éditeur de modèle
    ImGui::BeginChild("modelEditor", ImVec2(0, 0), true);
    ImGui::BeginTabBar("Settings#left_tabs_bar");
    if (ImGui::BeginTabItem("Sprites"))
    {
        _edModel->display();
        ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("map"))
    {
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
    ImGui::EndChild();
    ImGui::NextColumn();

    _import_sheet_panel->display();

    static bool scroll_to_bottom = false;
    ImGui::BeginChild("ConsoleOutput", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() - 20), false, ImGuiWindowFlags_HorizontalScrollbar);
    for (const auto &line : _cmd->get_history())
    {
        ImGui::TextUnformatted(line.c_str());
    }
    if (scroll_to_bottom)
    {
        ImGui::SetScrollHereY(1.0f);
    }
    scroll_to_bottom = false;
    ImGui::EndChild();
    bool reclaim_focus = false;
    ImGui::SetNextItemWidth(-FLT_MIN);
    if (ImGui::InputText("##ConsoleInput", input_buf, IM_ARRAYSIZE(input_buf), ImGuiInputTextFlags_EnterReturnsTrue))
    {
        _cmd->execute(input_buf);

        input_buf[0] = '\0';
        scroll_to_bottom = true;
        reclaim_focus = true;
    }
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1);

    ImGui::End();
}