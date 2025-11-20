#pragma once

#include <vector>
#include "entity.h"

using namespace std;

namespace marmot::studio
{
    class SpritesModel
    {
    public:
        SpritesModel() {}
        virtual ~SpritesModel() {}

        void add_sprite(unique_ptr<Entity>& item);

        void create_sprite();

        void remove_sprite();

        vector<unique_ptr<Entity>>& get_sprites();

    private:
        vector<unique_ptr<Entity>> _sprites;
    };
}