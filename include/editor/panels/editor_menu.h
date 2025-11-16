#pragma once
#include "editor_panel.h"


namespace marmot::studio {
    class MainMenu : public EditorPanel
    {
    public:
        MainMenu(log4cpp::Category &logger, shared_ptr<Worker> &worker, SDL_Renderer *renderer, ImGuiIO &io) : EditorPanel(logger, worker, renderer, io) {}
        virtual ~MainMenu() {}

        virtual void display();
    };
}