#include "import_sheet_model.h"

using namespace marmot;

void ImportSheetModel::set_path(const string &filename)
{
    scoped_lock lock(_mutex);
    _path = filename;
}

optional<filesystem::path> &ImportSheetModel::get_path()
{
    scoped_lock lock(_mutex);
    return _path;
}

void ImportSheetModel::update_tiles(vector<SurfacePtr> &tiles)
{
    std::lock_guard<std::mutex> lock(_mutex);
    for (auto &t : tiles)
    {
        _tiles.push_back(std::move(t));
    }
    tiles.clear();
}

std::vector<SurfacePtr> ImportSheetModel::get_tiles()
{
    std::lock_guard<std::mutex> lock(_mutex);
    return _tiles;
}