#include "editor_sprites.h"
#include "create_entity.h"

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
        _model->create_sprite();
    }
    ImGui::SameLine();
    if (ImGui::Button("-", ImVec2(button_size, button_size)))
    {
        _model->remove_sprite();
    }
    if (_model.get()->is_updated()) {
        _model.get()->set_updated(false);
    }
    for (const auto &sprite : _model->get_sprites())
    {
        display_entity(sprite.get());
    }
}

void SpritesPanel::display_entity(Entity *entity)
{
    ImGui::PushID(entity);
    if (entity->_editing)
    {
        ImGui::SetNextItemWidth(-1);
        if (entity->_request_focus)
        {
            ImGui::SetKeyboardFocusHere();
            entity->_request_focus = false;
        }
        if (ImGui::InputText("##edit", entity->_buffer, IM_ARRAYSIZE(entity->_buffer),
                             ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
        {
            ImGui::SetKeyboardFocusHere();
            entity->_name = entity->_buffer;
            entity->_editing = false;
        }
        if (!ImGui::IsItemActive() && !ImGui::IsItemHovered())
        {
            entity->_name = entity->_buffer;
            entity->_editing = false;
        }
        ImGui::PopID();
        return;
    }

    bool open = ImGui::CollapsingHeader(entity->_name.c_str(),
                                        ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth);

    if (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter))
    {
        entity->_editing = true;
        entity->_request_focus = true;
        std::snprintf(entity->_buffer, sizeof(entity->_buffer), "%s", entity->_name.c_str());
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

bool SpritesPanel::input_state_name(EntityState *state)
{
    if (ImGui::InputText("name", _input_buf, INPUT_BUFFER_SIZE)) {
        state->set_name(_input_buf);
        return true;
    }
    return false;
}

bool SpritesPanel::input_size(EntityState *state)
{
    static int width = 32;
    static int height = 32;
    bool updated = false;
    ImGui::TextUnformatted("size");
    ImGui::SameLine();
    ImGui::TextUnformatted("Width=");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    if (ImGui::InputInt("##width", &width)) {
        updated = true;
    }
    ImGui::SameLine();
    ImGui::TextUnformatted("Height=");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    if (ImGui::InputInt("##height", &height)) {
        updated = true;
    }
    state->set_width(width);
    state->set_height(height);
    return updated;
}

void SpritesPanel::display_state(EntityState *state)
{
    bool updated_state = false;
    ImGui::Separator();
    ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen;
    if (ImGui::TreeNodeEx(state->get_name().c_str(), flag))
    {
        updated_state = input_state_name(state) && updated_state;
        updated_state = input_size(state) && updated_state;

        float full_width = ImGui::GetContentRegionAvail().x;
        float button_size = ImGui::GetFrameHeight();
        float spacing = ImGui::GetStyle().ItemSpacing.x;
        float total_buttons_width = button_size * 2 + spacing;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + full_width - total_buttons_width);
        if (ImGui::Button("+", ImVec2(button_size, button_size)))
        {
            _logger.infoStream() << "EDITOR:create_frame (" << state->get_width() << "," << state->get_height() << ")";
            state->create_frame(_renderer);
        }
        ImGui::SameLine();
        if (ImGui::Button("-", ImVec2(button_size, button_size)))
        {
            _logger.infoStream() << "EDITOR:remove_frame";
            state->remove_frame();
        }
        display_state_frames(state);
        ImGui::Checkbox("loop", &state->_loop);
        ImGui::Checkbox("Frames speed", &state->_frame_speed);
        ImGui::SameLine();

        ImGui::TextUnformatted("speed");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100);
        ImGui::InputInt("##state_speed", &state->_speed, 10);
        ImGui::TreePop();
    }
}

void SpritesPanel::display_state_frames(EntityState *state)
{
    auto &frames = state->get_frames();
    int count_frames = frames.size();
    int frame_index = 1;
    for (auto &tex : frames)
    {
        ImGui::Image((void *)tex.get(), ImVec2(state->get_width(), state->get_height()));

        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("FRAME_INDEX"))
            {
                IM_ASSERT(payload->DataSize == sizeof(DragImagePayload));
                const DragImagePayload *data = (const DragImagePayload *)payload->Data;

                int src_panel = data->panel_id;
                int src_index = data->index;
                auto src_tex = make_texture(data->texture);
                state->replace_frame(src_tex, frame_index - 1);
            }
            ImGui::EndDragDropTarget();
        }
        if (frame_index++ < count_frames)
        {
            ImGui::SameLine();
        }
    }
}
