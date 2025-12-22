#include "editor_sprites_panel.h"
#include "create_sprite.h"
#include "update_sprite.h"
#include "create_state.h"
#include "remove_sprite.h"
#include "create_frame.h"
#include "update_state.h"
#include "delete_state.h"

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
        auto async_create = make_unique<CreateSprite>(_logger, CreateSpriteJob{_logger, _db});
        _worker->async(std::move(async_create));
    }
    _db->get(_sprites);
    for (const auto &[id, sprite] : _sprites)
    {
        display_entity(sprite.get());
    }
}

void SpritesPanel::display_entity(EditorSprite *entity)
{
    ImGui::PushID(entity);
    float full_width = ImGui::GetContentRegionAvail().x;
    float button_size = ImGui::GetFrameHeight();
    float spacing = ImGui::GetStyle().ItemSpacing.x;
    float total_buttons_width = button_size + spacing;
    float left_width = full_width - total_buttons_width;
    if (entity->_editing)
    {

        ImGui::SetNextItemWidth(left_width);
        _logger.infoStream() << " WIDTH " << left_width;
        if (entity->_request_focus)
        {
            ImGui::SetKeyboardFocusHere();
            entity->_request_focus = false;
        }
        if (ImGui::InputText("##edit", entity->_buffer, IM_ARRAYSIZE(entity->_buffer),
                             ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll))
        {
            ImGui::SetKeyboardFocusHere();
            entity->_editing = false;
            update_sprite(entity->_id, entity->_buffer);
        }
        if (!ImGui::IsItemActive() && !ImGui::IsItemHovered())
        {
            entity->_name = entity->_buffer;
            entity->_editing = false;
            update_sprite(entity->_id, entity->_buffer);
        }
        ImGui::PopID();
        return;
    }

    bool open = ImGui::CollapsingHeader(entity->_name.c_str(),
                                        ImGuiTreeNodeFlags_DefaultOpen);

    if (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter))
    {
        entity->_editing = true;
        entity->_request_focus = true;
        std::snprintf(entity->_buffer, sizeof(entity->_buffer), "%s", entity->_name.c_str());
        ImGui::PopID();
        return;
    }

    // ImGui::SetCursorPosX(ImGui::GetCursorPosX() + full_width - total_buttons_width);
    if (ImGui::Button("delete", ImVec2(80, button_size)))
    {
        auto async_remove = make_unique<RemoveSprite>(_logger, RemoveSpriteJob{_logger, _db, entity->_id});
        _worker->async(std::move(async_remove));
    }
    if (open)
    {
        display_states(entity);
    }
    ImGui::PopID();
}

void SpritesPanel::display_states(EditorSprite *entity)
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
        if (ImGui::Button("+##stateAdd", ImVec2(button_size, button_size)))
        {
            create_state(entity->_id, "");
        }
        for (const auto &[id, state] : entity->_states)
        {
            display_state(entity, state.get());
        }
        ImGui::TreePop();
    }
}

bool SpritesPanel::input_state_name(EditorState *state)
{
    if (ImGui::InputText("name", state->_input_buf, INPUT_BUF_STATE_SIZE))
    {
        state->set_name(_input_buf);
        return true;
    }
    return false;
}

bool SpritesPanel::input_size(EditorState *state)
{
    bool updated = false;
    ImGui::TextUnformatted("size");
    ImGui::SameLine();
    ImGui::TextUnformatted("Width=");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    if (ImGui::InputInt("##width", &state->_width))
    {
        updated = true;
    }
    ImGui::SameLine();
    ImGui::TextUnformatted("Height=");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    if (ImGui::InputInt("##height", &state->_height))
    {
        updated = true;
    }
    return updated;
}

void SpritesPanel::display_state(EditorSprite* sprite, EditorState *state)
{
    ImGui::PushID(state);
    bool updated_state = false;
    ImGui::Separator();
    ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_DefaultOpen;
    if (ImGui::TreeNodeEx(state->get_name().c_str(), flag))
    {
        if (ImGui::Button("save##savestate"))
        {
            auto async_update = make_unique<UpdateState>(_logger, UpdateStateJob{_logger, _db, sprite->_id, state->_id, state->_name, state->_loop, state->_speed, state->_width, state->_height});
            _worker->async(std::move(async_update));
        }
        ImGui::SameLine();
        if (ImGui::Button("del##deletestate"))
        {
            auto async_delete = make_unique<DeleteState>(_logger, DeleteStateJob{_logger, _db, sprite->_id, state->_id});
            _worker->async(std::move(async_delete));
        }
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
    ImGui::PopID();
}

void SpritesPanel::create_frame(MarmotaId sprite_id, MarmotaId state_id, int num_frame, int width, int height)
{
    auto frame = make_surface(SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32));
    SDL_FillRect(frame.get(), nullptr, SDL_MapRGBA(frame.get()->format, 255, 255, 255, 255));
    auto async_create = make_unique<CreateFrame>(_logger, CreateFrameJob(_logger, _db, sprite_id, state_id, 1, width, height));
    _worker->async(std::move(async_create));
    // auto tex = make_texture(SDL_CreateTextureFromSurface(_renderer, frame.get()));
}

void SpritesPanel::display_state_frames(EditorState *state)
{
    /*
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
        */
}

void SpritesPanel::update_sprite(uint64_t id, const string &name)
{
    auto async_update = make_unique<UpdateSprite>(
        _logger,
        UpdateSpriteJob{_logger, _db, id, name});
    _worker->async(std::move(async_update));
}

void SpritesPanel::create_state(uint64_t id, const string &name)
{
    _logger.infoStream() << "EDITOR:create_state:(" << id << "," << name << ")";

    auto async_create = make_unique<CreateState>(
        _logger,
        CreateStateJob{_logger, _db, id, name});
    _worker->async(std::move(async_create));
}

void SpritesPanel::remove_state()
{
}
