#pragma once

#include <memory>
#include <string>
#include "editor_panel.h"
#include "import_sheet_model.h"
#include "import_sheet.h"

constexpr int DEFAULT_SPRITE_SIZE = 32;

namespace marmot
{
    class GUIImportSpriteSheet : public EditorPanel
    {
    public:
        GUIImportSpriteSheet(log4cpp::Category &logger, shared_ptr<Worker> &worker, SDL_Renderer *renderer, ImGuiIO &io) : EditorPanel(logger, worker, renderer, io),
                                                                                                                           _model(make_shared<ImportSheetModel>()),
                                                                                                                           _width(DEFAULT_SPRITE_SIZE), _height(DEFAULT_SPRITE_SIZE) {}
        virtual ~GUIImportSpriteSheet() {}

        virtual void display();

    private:
        void display_params();
        void display_sheet();

        shared_ptr<ImportSheetModel> _model;
        int _width;
        int _height;
    };
}