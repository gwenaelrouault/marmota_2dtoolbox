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
#include "editor_sprites.h"
#include "editor_import_sheet_panel.h"
#include "worker.h"

using namespace std;

namespace marmot::studio
{

    class MainPanel
    {
    public:
        void display();

        MainPanel(SDL_Renderer *renderer, ImGuiIO &io, log4cpp::Category &logger, std::shared_ptr<Worker> &worker, std::filesystem::path &path, std::shared_ptr<marmota::AssetsDB> &db) : _renderer(renderer),
                                                                                                                                                                                 _io(io),
                                                                                                                                                                                 _logger(logger),
                                                                                                                                                                                 _worker(worker),
                                                                                                                                                                                 _workdir(path),
                                                                                                                                                                                 _db(db),
                                                                                                                                                                                 _cmd(make_unique<Cmd>(logger)),
                                                                                                                                                                                 _edModel(make_unique<EditorModel>(logger)),
                                                                                                                                                                                 _import_sheet_panel(make_unique<ImportSheetPanel>(logger, worker, renderer, io)) {}
        virtual ~MainPanel() {}

    private:
    
        SDL_Renderer *_renderer;
        ImGuiIO &_io;
        log4cpp::Category &_logger;
        shared_ptr<Worker> _worker;
        filesystem::path _workdir;
        shared_ptr<marmota::AssetsDB> &_db;
        unique_ptr<Cmd> _cmd;
        unique_ptr<EditorModel> _edModel;
        unique_ptr<ImportSheetPanel> _import_sheet_panel;
    };
}