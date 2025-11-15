#include "editor_model.h"

using namespace marmot;

void draw_editable_header(EditableHeader *header)
{
    ImGui::PushID(header);
    if (header->editing)
    {
        ImGui::SetNextItemWidth(-1);
        if (header->requestFocus)
        {
            ImGui::SetKeyboardFocusHere();
            header->requestFocus = false;
        }
        if (ImGui::InputText("##edit", header->buffer, IM_ARRAYSIZE(header->buffer),
                             ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
        {
            ImGui::SetKeyboardFocusHere();
            header->name = header->buffer;
            header->editing = false;
        }
        if (!ImGui::IsItemActive() && !ImGui::IsItemHovered())
        {
            header->name = header->buffer;
            header->editing = false;
        }
        ImGui::PopID();
        return;
    }

    bool open = ImGui::CollapsingHeader(header->name.c_str(),
                                        ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth);

    if (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter))
    {
        header->editing = true;
        header->requestFocus = true;
        std::snprintf(header->buffer, sizeof(header->buffer), "%s", header->name.c_str());
        ImGui::PopID();
        return;
    }
    if (open)
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
    ImGui::PopID();
}

void EditorModel::display()
{
    ImGui::TextUnformatted("Ajouter / supprimer des sprites");
    ImGui::SameLine();
    float full_width = ImGui::GetContentRegionAvail().x;
    float button_size = ImGui::GetFrameHeight();
    float spacing = ImGui::GetStyle().ItemSpacing.x;
    float total_buttons_width = button_size * 2 + spacing;
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + full_width - total_buttons_width);
    if (ImGui::Button("+", ImVec2(button_size, button_size)))
    {
        _sprites.push_back(std::make_unique<EditableHeader>("Nouveau"));
    }
    ImGui::SameLine();
    if (ImGui::Button("-", ImVec2(button_size, button_size)))
    {
    }

    for (const auto &sprite : _sprites)
    {
        draw_editable_header(sprite.get());
    }
}
