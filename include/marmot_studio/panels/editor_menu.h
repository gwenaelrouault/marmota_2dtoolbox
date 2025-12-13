#pragma once

#include <filesystem>
#include "editor_panel.h"
#include "sprites_model.h"
#include "marmota_asset_store.hpp"


namespace marmot::studio {
    class MainMenu : public EditorPanel
    {
    public:
        MainMenu(log4cpp::Category &logger, 
            shared_ptr<Worker> worker, 
            SDL_Renderer *renderer, ImGuiIO &io, 
            shared_ptr<SpritesModel> sprites_model) 
            : EditorPanel(MAIN_MENU, logger, worker, renderer, io) , _sprites_model(sprites_model) {}
        virtual ~MainMenu() {}

        virtual void display();
        private:
            shared_ptr<SpritesModel> _sprites_model;
            filesystem::path _project_path;

    };
}