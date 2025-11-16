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

    constexpr int DEFAULT_SPRITE_SIZE = 32;
    
    class ImportSheetModel
    {
    public:

        ImportSheetModel() : _path(nullopt), _width(DEFAULT_SPRITE_SIZE), _height(DEFAULT_SPRITE_SIZE) {}

        virtual ~ImportSheetModel() {}

        optional<filesystem::path>& get_path();

        void update_tiles(vector<SurfacePtr>& tiles, const string& filename, int width, int height);

        void get_tiles(SDL_Renderer* renderer, vector<TexturePtr>& tiles);

        int get_width();

        int get_height();

    private:
        optional<filesystem::path> _path;
        vector<SurfacePtr> _tiles;
        int _width;
        int _height;
        mutex _mutex;
    };
}