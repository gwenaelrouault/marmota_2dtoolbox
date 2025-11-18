#include "editor_sprites.h"

using namespace marmot::studio;

void SpritesPanel::display()
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
        _sprites->create_sprite();
    }
    ImGui::SameLine();
    if (ImGui::Button("-", ImVec2(button_size, button_size)))
    {
        _sprites->remove_sprite();
    }
    for (const auto &sprite : _sprites->get_sprites())
    {
        display_entity(sprite.get());
    }
}

void SpritesPanel::display_entity(Entity *entity)
{
    ImGui::PushID(entity);
    if (entity->is_editing())
    {
        ImGui::SetNextItemWidth(-1);
        if (entity->is_requested_focus())
        {
            ImGui::SetKeyboardFocusHere();
            entity->set_request_focus(false);
        }
        if (ImGui::InputText("##edit", entity->_buffer, IM_ARRAYSIZE(entity->_buffer),
                             ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
        {
            ImGui::SetKeyboardFocusHere();
            entity->set_name(entity->_buffer);
            entity->set_editing(false);
        }
        if (!ImGui::IsItemActive() && !ImGui::IsItemHovered())
        {
            entity->set_name(entity->_buffer);
            entity->set_editing(false);
        }
        ImGui::PopID();
        return;
    }

    bool open = ImGui::CollapsingHeader(entity->getName().c_str(),
                                        ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth);

    if (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter))
    {
        entity->set_editing(true);
        entity->set_request_focus(true);
        std::snprintf(entity->_buffer, sizeof(entity->_buffer), "%s", entity->getName().c_str());
        ImGui::PopID();
        return;
    }
    if (open)
    {
        display_states(entity);
    }
    ImGui::PopID();
}

void SpritesPanel::display_states(Entity *entity)
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
            entity->create_new_state();
        }
        ImGui::SameLine();
        if (ImGui::Button("-", ImVec2(button_size, button_size)))
        {
            entity->remove_state();
        }
        for (const auto &state : entity->get_states())
        {
            display_state(state.get());
        }
        ImGui::TreePop();
    }
}

void SpritesPanel::display_state(EntityState *state)
{
    ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen;
    if (ImGui::TreeNodeEx(state->get_name().c_str(), flag))
    {
        static int width = 0;
        static int height = 0;
        ImGui::TextUnformatted("size");
        ImGui::SameLine();

        ImGui::TextUnformatted("Width");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::InputInt("##width", &width);

        ImGui::SameLine();
        ImGui::TextUnformatted("Height");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::InputInt("##height", &height);
        state->set_height(height);
        state->set_width(width);
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
