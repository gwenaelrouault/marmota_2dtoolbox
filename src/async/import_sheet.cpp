#include "import_sheet.h"
#include "sdl_utils.h"

using namespace marmot;

void ImportSheetCallback::onSuccess()
{
}

void ImportSheetCallback::onFailed(int err_code)
{
}

int ImportSheetJob::execute()
{

    _logger.infoStream() << "ASYNC:import_sheet " << _path.c_str();
    vector<SurfacePtr> tiles;
    auto sheet = make_surface(IMG_Load(_path.c_str()));

    if (sheet != nullptr)
    {
        _logger.infoStream() << "ASYNC:import_sheet loaded " << _path.c_str() << " [size=" << sheet->w << "," << sheet->w << "]";
        int x_cell = 0;
        int y_cell = 0;
        for (int x = 0; x < sheet->w; x += _width, x_cell++)
        {
            for (int y = 0; y < sheet->h; y += _height, y_cell++)
            {
                SDL_Rect srcRect;
                srcRect.x = x;
                srcRect.y = y;
                srcRect.w = _width;
                srcRect.h = _height;
                auto tile = make_surface(SDL_CreateRGBSurface(
                    0,
                    _width, _height,
                    sheet->format->BitsPerPixel,
                    sheet->format->Rmask,
                    sheet->format->Gmask,
                    sheet->format->Bmask,
                    sheet->format->Amask));
                SDL_BlitSurface(sheet.get(), &srcRect, tile.get(), nullptr);
                tiles.push_back(std::move(tile));
                _logger.infoStream() << "ASYNC:import_sheet loaded tile ( " << x_cell << "," << y_cell << ")";
                _model->update_tiles(tiles, _path, _width, _height);
            }
        }
    }

    return 0;
}