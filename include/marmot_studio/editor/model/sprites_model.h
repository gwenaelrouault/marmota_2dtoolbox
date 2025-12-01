#pragma once

#include <vector>
#include "entity.h"
#include <atomic>
#include <optional>
#include "marmota_sprite.hpp"
#include <mutex>

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

        void on_current_sprite(uint64_t id);
        optional<uint64_t> get_current_sprite();
        void on_no_sprite();

        void set_sprite(marmota::MarmotaSprite& sprite);

        void set_updated(bool flag);
        bool is_updated();

    private:
        vector<unique_ptr<Entity>> _sprites;
        optional<uint64_t>  _current_sprite;
        atomic_bool _flag_updated;
        mutex _mutex;
    };
}