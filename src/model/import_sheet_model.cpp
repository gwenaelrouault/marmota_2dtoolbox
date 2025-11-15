#include "import_sheet_model.h"

using namespace marmot;

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
}

vector<SurfacePtr> ImportSheetModel::get_tiles()
{
    lock_guard<std::mutex> lock(_mutex);
    return _tiles;
}

int ImportSheetModel::get_width() {
    lock_guard<std::mutex> lock(_mutex);
    return _width;
}


int ImportSheetModel::get_height() {
    lock_guard<std::mutex> lock(_mutex);
    return _height;
}