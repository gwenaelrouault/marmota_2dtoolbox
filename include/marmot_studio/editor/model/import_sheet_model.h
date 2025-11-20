#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <optional>
#include <mutex>
#include "sdl_utils.h"

using namespace std;

namespace marmot::studio
{

    constexpr int DEFAULT_SPRITE_SIZE = 32;
    
    class ImportSheetModel
    {
    public:

        ImportSheetModel() : _path(nullopt), _width(DEFAULT_SPRITE_SIZE), _height(DEFAULT_SPRITE_SIZE), _updated(false) {}

        virtual ~ImportSheetModel() {}

        optional<filesystem::path>& get_path();

        void update_tiles(vector<SurfacePtr>& tiles, const string& filename, int width, int height);

        void get_tiles(SDL_Renderer* renderer, vector<TexturePtr>& tiles);

        int get_width();

        int get_height();

        bool updated();

    private:
        optional<filesystem::path> _path;
        int _width;
        int _height;
        bool _updated;
        vector<SurfacePtr> _tiles;
        mutex _mutex;
    };
}