#include "editor_main_panel.h"
#include "ImGuiFileDialog.h"

using namespace marmot::studio;

void MainPanel::display()
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
        string project_name = "PROJECT:";
        if (_filename.has_value()) {
            project_name += _filename.value().filename();
        }
        ImGui::TextUnformatted(project_name.c_str());
        ImGui::Separator();
        _sprites_panel->display();
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