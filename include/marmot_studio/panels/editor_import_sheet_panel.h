#pragma once

#include <memory>
#include <string>
#include "editor_panel.h"
#include "import_sheet_model.h"
#include "import_sheet.h"

namespace marmot::studio
{
    class ImportSheetPanel : public EditorPanel
    {
    public:
        ImportSheetPanel(log4cpp::Category &logger, shared_ptr<Worker> worker, SDL_Renderer *renderer, ImGuiIO &io, shared_ptr<ImportSheetModel> sheet_model) : EditorPanel(IMPORT_SHEET_PANEL, logger, worker, renderer, io),
                                                                                                                       _model(sheet_model),
                                                                                                                       _width(DEFAULT_SPRITE_SIZE), _height(DEFAULT_SPRITE_SIZE) {}
        virtual ~ImportSheetPanel() {}

        virtual void display();

    private:
        void display_params();
        void display_sheet();
        void display_sheet_tile(TexturePtr& tile, int index, int width, int height);
        shared_ptr<ImportSheetModel> _model;
        vector<TexturePtr> _tiles;
        int _width;
        int _height;
    };
}