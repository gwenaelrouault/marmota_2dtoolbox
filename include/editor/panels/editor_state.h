#pragma once
#include "editor_panel.h"

namespace marmot::studio
{
    class StatePanel : public EditorPanel
    {
    public:
        StatePanel(log4cpp::Category &logger, shared_ptr<Worker> &worker, SDL_Renderer *renderer, ImGuiIO &io) : EditorPanel(logger, worker, renderer, io) {}
        virtual ~StatePanel() {}

        virtual void display();
    };

}