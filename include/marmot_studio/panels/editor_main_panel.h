#pragma once

#include <string>
#include <vector>
#include <memory>
#include <log4cpp/Category.hh>
#include "imgui.h"
#include <filesystem>
#include "imgui_impl_sdlrenderer2.h"
#include "editor_cmd.h"
#include "editor_sprites.h"
#include "editor_import_sheet_panel.h"
#include "worker.hpp"
#include "import_sheet_model.h"
#include "sprites_model.h"

using namespace std;

namespace marmot::studio
{

    class MainPanel
    {
    public:
        void display();

        MainPanel(
            SDL_Renderer *renderer,
            ImGuiIO &io,
            log4cpp::Category &logger,
            std::shared_ptr<Worker> worker,
            std::filesystem::path &path,
            shared_ptr<SpritesModel> sprites_model,
            shared_ptr<ImportSheetModel> sheet_model) : _renderer(renderer),
                                                         _io(io),
                                                         _logger(logger),
                                                         _worker(worker),
                                                         _workdir(path),
                                                         _cmd(make_unique<Cmd>(logger)),
                                                         _sprites_panel(make_unique<SpritesPanel>(logger, worker, renderer, io, sprites_model)),
                                                         _import_sheet_panel(make_unique<ImportSheetPanel>(logger, worker, renderer, io, sheet_model)),
                                                         _model(sprites_model) {}
        virtual ~MainPanel() {}

    private:
        SDL_Renderer *_renderer;
        ImGuiIO &_io;
        log4cpp::Category &_logger;
        shared_ptr<Worker> _worker;
        filesystem::path _workdir;
        unique_ptr<Cmd> _cmd;
        unique_ptr<SpritesPanel> _sprites_panel;
        unique_ptr<ImportSheetPanel> _import_sheet_panel;
        shared_ptr<SpritesModel> _model;
    };
}