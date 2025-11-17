#include "editor_state.h"

using namespace marmot::studio;

void StatePanel::display()
{
    ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen;
    if (ImGui::TreeNodeEx("Etats", flag))
    {
        ImGui::SameLine();
        float full_width = ImGui::GetContentRegionAvail().x;
        float button_size = ImGui::GetFrameHeight();
        float spacing = ImGui::GetStyle().ItemSpacing.x;
        float total_buttons_width = button_size * 2 + spacing;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + full_width - total_buttons_width);
        if (ImGui::Button("+", ImVec2(button_size, button_size)))
        {
        }
        ImGui::SameLine();
        if (ImGui::Button("-", ImVec2(button_size, button_size)))
        {
        }
        ImGui::TreePop();
    }
}
