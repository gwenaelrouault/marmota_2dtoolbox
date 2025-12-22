#pragma once

#include "editor_panel.h"
#include "editor_main_panel.h"
#include "editor_menu.h"
#include "import_sheet_model.h"
#include "asset_db.h"
#include "marmota_cache.hpp"

namespace marmot::studio
{
    class Editor : public EditorPanel
    {
    public:
        Editor(SDL_Renderer *renderer, 
            ImGuiIO &io, 
            log4cpp::Category &logger, 
            std::shared_ptr<Worker> worker, 
            std::filesystem::path &path, 
            std::shared_ptr<AssetDB> db,
            std::shared_ptr<marmota::MarmotaCache> cache)
            : EditorPanel(0, logger, worker, renderer, io)
        {
            // create models
            _sheet_model = make_shared<ImportSheetModel>();
            
            // create panels
            _menu = make_unique<MainMenu>(logger, worker, renderer, io, db);
            _main_panel = make_unique<MainPanel>(renderer, io, logger, worker, path, db, _sheet_model);
        }
        virtual ~Editor() {}

        virtual void display();

    private:
        shared_ptr<ImportSheetModel> _sheet_model;
        unique_ptr<MainPanel> _main_panel;
        unique_ptr<MainMenu> _menu;
    };
}