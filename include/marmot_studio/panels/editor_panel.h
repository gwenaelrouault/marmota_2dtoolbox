#pragma once

#include <log4cpp/Category.hh>
#include "imgui_impl_sdlrenderer2.h"
#include "worker.hpp"
#include "sdl_utils.h"

using namespace std;

namespace marmot::studio
{
    constexpr int IMPORT_SHEET_PANEL = 1;
    constexpr int MAIN_PANEL = 2;
    constexpr int SPRITES_PANEL = 3;
    constexpr int MAIN_MENU = 4;

    class EditorPanel
    {
    public:
        EditorPanel(int num_panel, log4cpp::Category &logger, shared_ptr<Worker> worker, SDL_Renderer *renderer, ImGuiIO &io) 
        : _num_panel(num_panel), _logger(logger), _worker(worker), _renderer(renderer), _io(io) {}
        virtual ~EditorPanel() {}
        virtual void display() = 0;

    protected:
        int _num_panel;
        log4cpp::Category &_logger;
        shared_ptr<Worker> _worker;
        SDL_Renderer *_renderer;
        ImGuiIO &_io;
    };

    struct DragImagePayload
    {
        int panel_id;
        int index;
        SDL_Texture *texture;
    };
}
