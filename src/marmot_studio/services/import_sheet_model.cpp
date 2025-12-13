#include "import_sheet_model.h"

using namespace marmot::studio;

optional<filesystem::path> &ImportSheetModel::get_path()
{
    scoped_lock lock(_mutex);
    return _path;
}

void ImportSheetModel::update_tiles(vector<SurfacePtr> &tiles, const string& filename, int width, int height)
{
    lock_guard<std::mutex> lock(_mutex);
    _tiles.clear();
    _path = filename;
    _width = width;
    _height = height;
    for (auto &t : tiles)
    {
        _tiles.push_back(std::move(t));
    }
    _updated = true;
}

void ImportSheetModel::get_tiles(SDL_Renderer* renderer, vector<TexturePtr>& tiles)
{
    lock_guard<std::mutex> lock(_mutex);
    for (auto &t : _tiles)
    {
        auto tex = SDL_CreateTextureFromSurface(renderer, t.get());
        tiles.push_back(std::move(make_texture(tex)));
    }
    _updated = false;
}

bool ImportSheetModel::updated() {
    lock_guard<std::mutex> lock(_mutex);
    return _updated;
}

int ImportSheetModel::get_width() {
    lock_guard<std::mutex> lock(_mutex);
    return _width;
}


int ImportSheetModel::get_height() {
    lock_guard<std::mutex> lock(_mutex);
    return _height;
}