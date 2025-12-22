#pragma once

#include <memory>
#include <map>
#include <cstdint>
#include "editor_panel.h"
#include "asset_db.h"

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
                     shared_ptr<AssetDB> db) : EditorPanel(SPRITES_PANEL, logger, worker, renderer, io),
                                               _db(db)
        {
            for (int i = 0; i < INPUT_BUFFER_SIZE; i++)
            {
                _input_buf[i] = 0;
            }
        }
        virtual ~SpritesPanel() {}
        virtual void display();

    private:
        void display_entity(EditorSprite *entity);
        void display_states(EditorSprite *entity);
        void display_state(EditorSprite *sprite, EditorState *state);
        void display_state_frames(EditorState *state);

        bool input_state_name(EditorState *state);
        bool input_size(EditorState *state);

        void update_sprite(MarmotaId id, const string &name);

        void create_state(MarmotaId id, const string &name);

        void create_frame(MarmotaId sprite_id, MarmotaId state_id, int num_frame, int width, int height);

        void remove_state();

        shared_ptr<AssetDB> _db;
        char _input_buf[INPUT_BUFFER_SIZE];
        map<MarmotaId, unique_ptr<EditorSprite>> _sprites;
    };
}
