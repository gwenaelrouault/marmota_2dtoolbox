#pragma once

#include <log4cpp/Category.hh>
#include "imgui_impl_sdlrenderer2.h"
#include "worker.h"

namespace marmot::studio
{
    class EditorPanel
    {
    public:
        EditorPanel(log4cpp::Category &logger, shared_ptr<Worker>& worker, SDL_Renderer* renderer, ImGuiIO & io) : _logger(logger), _worker(worker), _renderer(renderer), _io(io) {}
        virtual ~EditorPanel() {}
        virtual void display() = 0;

    protected:
        log4cpp::Category &_logger;
        shared_ptr<Worker>& _worker;
        SDL_Renderer *_renderer;
        ImGuiIO &_io;
    };

}
