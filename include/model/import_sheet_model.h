#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <optional>
#include <mutex>
#include "sdl_utils.h"

using namespace std;

namespace marmot
{
    class ImportSheetModel
    {
    public:

        ImportSheetModel() : _path(nullopt) {}

        virtual ~ImportSheetModel() {}

        void set_path(const string& filename);

        optional<filesystem::path>& get_path();

        void update_tiles(vector<SurfacePtr>& tiles);
        std::vector<SurfacePtr> get_tiles();

    private:
        optional<filesystem::path> _path;
        vector<SurfacePtr> _tiles;
        mutex _mutex;
    };
}