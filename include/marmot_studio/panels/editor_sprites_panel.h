#pragma once

#include <memory>
#include <map>
#include <cstdint>
#include "sprites_model.h"
#include "editor_panel.h"
#include "marmota_asset_store.hpp"

namespace marmot::studio
{
    using namespace marmot;

    constexpr size_t INPUT_BUFFER_SIZE = 128;

    class SpritesPanel : public EditorPanel
    {
    public:
        SpritesPanel(log4cpp::Category &logger, 
            shared_ptr<Worker> worker, 
            SDL_Renderer *renderer, ImGuiIO &io,
            shared_ptr<SpritesModel> &sprites_model) : EditorPanel(SPRITES_PANEL, logger, worker, renderer, io),
             _model(sprites_model) {
                for(int i = 0; i < INPUT_BUFFER_SIZE; i++) {
                    _input_buf[i] = 0;
                }
             }
        virtual ~SpritesPanel() {}
        virtual void display();

    private:
        void display_entity(EditorSprite *entity);
        void display_states(EditorSprite *entity);
        void display_state(EditorState* state);
        void display_state_frames(EditorState *state);

        bool input_state_name(EditorState *state);
        bool input_size(EditorState *state);

        void update_sprite(uint64_t id, const string& name);

        void create_state(uint64_t id, const string& name);
        void remove_state();

        shared_ptr<SpritesModel> _model;
        char _input_buf[INPUT_BUFFER_SIZE];
        map<uint64_t, unique_ptr<EditorSprite>> _sprites;
    };

}
