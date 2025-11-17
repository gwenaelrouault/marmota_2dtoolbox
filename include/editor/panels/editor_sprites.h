#pragma once

#include "editor_state.h"
#include "editor_sprites.h"
#include <memory>

namespace marmot::studio
{
    struct EditableHeader
    {
        std::string name = "Ma section";
        bool editing = false;
        bool requestFocus = false;
        char buffer[128]{};
    };

    class SpritesPanel : public EditorPanel
    {
    public:
        SpritesPanel(log4cpp::Category &logger, shared_ptr<Worker> &worker, SDL_Renderer *renderer, ImGuiIO &io) : EditorPanel(logger, worker, renderer, io),
            _state_panel(make_unique<StatePanel>(logger, worker, renderer, io)) {}
        virtual ~SpritesPanel() {}
        virtual void display();

    private:
        void draw_editable_header(EditableHeader *header);

        std::vector < std::unique_ptr <EditableHeader> > _sprites;
        std::unique_ptr<StatePanel> _state_panel;
    };

}
