#pragma once

#include <filesystem>
#include "editor_panel.h"
#include "menu_model.h"
#include "sprites_model.h"
#include "marmota_asset_store.h"


namespace marmot::studio {
    class MainMenu : public EditorPanel
    {
    public:
        MainMenu(log4cpp::Category &logger, 
            shared_ptr<Worker> &worker, 
            SDL_Renderer *renderer, ImGuiIO &io, 
            shared_ptr<marmota::MarmotaAssetStore> &store,
            shared_ptr<MenuModel>& model, shared_ptr<SpritesModel>& sprites_model) 
            : EditorPanel(MAIN_MENU, logger, worker, renderer, io) , _model(model), _sprites_model(sprites_model), _store(store) {}
        virtual ~MainMenu() {}

        virtual void display();
        private:
            shared_ptr<MenuModel>& _model;
            shared_ptr<SpritesModel>& _sprites_model;
            shared_ptr<marmota::MarmotaAssetStore> &_store;
            filesystem::path _project_path;

    };
}