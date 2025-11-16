#pragma once
#include "editor_panel.h"
#include "editor_main_panel.h"
#include "editor_menu.h"

namespace marmot::studio {
    class Editor : public EditorPanel {
public:
        Editor(SDL_Renderer *renderer, ImGuiIO &io, log4cpp::Category &logger, std::shared_ptr<Worker> &worker, std::filesystem::path &path, std::shared_ptr<marmota::AssetsDB> &db) 
        : EditorPanel(logger, worker, renderer, io), 
        _main_panel(make_unique<MainPanel>(renderer, io, logger, worker, path, db)),
        _menu(make_unique<MainMenu>(logger, worker, renderer, io)) {}
        virtual ~Editor() {}

        virtual void display();
        private:
            unique_ptr<MainPanel> _main_panel;
            unique_ptr<MainMenu> _menu;
    };
}