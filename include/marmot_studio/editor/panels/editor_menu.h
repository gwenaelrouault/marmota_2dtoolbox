#pragma once
#include "editor_panel.h"
#include "menu_model.h"

namespace marmot::studio {
    class MainMenu : public EditorPanel
    {
    public:
        MainMenu(log4cpp::Category &logger, 
            shared_ptr<Worker> &worker, 
            SDL_Renderer *renderer, ImGuiIO &io, shared_ptr<MenuModel>& model) 
            : EditorPanel(MAIN_MENU, logger, worker, renderer, io) , _model(model) {}
        virtual ~MainMenu() {}

        virtual void display();
        private:
            shared_ptr<MenuModel>& _model;
    };
}