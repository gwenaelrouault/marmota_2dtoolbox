#pragma once

#include <string>
#include <vector>
#include <memory>
#include <log4cpp/Category.hh>
#include "imgui.h"
#include <filesystem>
#include "imgui_impl_sdlrenderer2.h"
#include "assets_db.h"
#include "editor_cmd.h"
#include "editor_model.h"
#include "editor_gui_import_sheet.h"
#include "worker.h"

using namespace std;

namespace marmot
{

    class GUI
    {
    public:
        void display();

        GUI(SDL_Renderer *renderer, ImGuiIO &io, log4cpp::Category &logger, std::shared_ptr<Worker>& worker, std::filesystem::path &path, std::shared_ptr<AssetsDB> &db) : _renderer(renderer),
                                                                                                                                          _io(io),
                                                                                                                                          _logger(logger),
                                                                                                                                          _worker(worker),
                                                                                                                                          _workdir(path),
                                                                                                                                          _db(db),
                                                                                                                                          _cmd(make_unique<Cmd>(logger)),
                                                                                                                                          _edModel(make_unique<EditorModel>(logger)),
                                                                                                                                          _import_sheet_panel(make_unique<GUIImportSpriteSheet>(logger, worker, renderer, io)) {}
        virtual ~GUI() {}

    private:
        void draw_menu_bar();
        void draw_main_panel();
        void show_new_project(bool &open_dialog, std::string &new_file_name);

        SDL_Renderer *_renderer;
        ImGuiIO &_io;
        log4cpp::Category &_logger;
        shared_ptr<Worker> _worker;
        filesystem::path _workdir;
        shared_ptr<AssetsDB> &_db;
        unique_ptr<Cmd> _cmd;
        unique_ptr<EditorModel> _edModel;
        unique_ptr<GUIImportSpriteSheet> _import_sheet_panel;
    };
}