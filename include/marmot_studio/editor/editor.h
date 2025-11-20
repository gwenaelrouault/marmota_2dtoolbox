#pragma once

#include "editor_panel.h"
#include "editor_main_panel.h"
#include "editor_menu.h"
#include "import_sheet_model.h"
#include "sprites_model.h"

namespace marmot::studio
{
    class Editor : public EditorPanel
    {
    public:
        Editor(SDL_Renderer *renderer, ImGuiIO &io, log4cpp::Category &logger, std::shared_ptr<Worker> &worker, std::filesystem::path &path, std::shared_ptr<marmota::AssetsDB> &db)
            : EditorPanel(0, logger, worker, renderer, io)
        {
            _sheet_model = make_shared<ImportSheetModel>();
            _sprites_model = make_shared<SpritesModel>();
            _menu = make_unique<MainMenu>(logger, worker, renderer, io);
            _main_panel = make_unique<MainPanel>(renderer, io, logger, worker, path, db, _sprites_model, _sheet_model);
        }
        virtual ~Editor() {}

        virtual void display();

    private:
        shared_ptr<ImportSheetModel> _sheet_model;
        shared_ptr<SpritesModel> _sprites_model;
        unique_ptr<MainPanel> _main_panel;
        unique_ptr<MainMenu> _menu;
    };
}