#pragma once

#include <filesystem>
#include "editor_panel.h"
#include "sprites_model.h"
#include "marmota_asset_store.hpp"
#include "asset_db.h"


namespace marmot::studio {
    class MainMenu : public EditorPanel
    {
    public:
        MainMenu(log4cpp::Category &logger, 
            shared_ptr<Worker> worker, 
            SDL_Renderer *renderer, ImGuiIO &io, 
            shared_ptr<AssetDB> db) 
            : EditorPanel(MAIN_MENU, logger, worker, renderer, io) , _db(db) {}
        virtual ~MainMenu() {}

        virtual void display();
        private:
            shared_ptr<AssetDB> _db;
            filesystem::path _project_path;

    };
}