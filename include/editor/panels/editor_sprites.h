#pragma once

#include "editor_sprites.h"
#include "sprites_model.h"
#include "editor_panel.h"
#include <memory>

namespace marmot::studio
{
    class SpritesPanel : public EditorPanel
    {
    public:
        SpritesPanel(log4cpp::Category &logger, shared_ptr<Worker> &worker, SDL_Renderer *renderer, ImGuiIO &io, shared_ptr<SpritesModel> &sprites_model) : EditorPanel(logger, worker, renderer, io),
             _sprites(sprites_model) {}
        virtual ~SpritesPanel() {}
        virtual void display();

    private:
        void display_entity(Entity *entity);
        void display_states(Entity *entity);
        void display_state(EntityState* state);

        shared_ptr<SpritesModel> & _sprites;
    };

}
