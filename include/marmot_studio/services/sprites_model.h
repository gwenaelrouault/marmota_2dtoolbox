#pragma once

#include <map>
#include <queue>
#include <atomic>
#include <optional>
#include <mutex>
#include <filesystem>
#include "editor_sprite.h"
#include "marmota_sprite.hpp"
#include "marmota_asset_store.hpp"
#include "marmota_cache.hpp"
#include "update_event.h"

using namespace std;

namespace marmot::studio
{
    class SpritesModel
    {
    public:
        SpritesModel(
            log4cpp::Category &logger,
            shared_ptr<marmota::MarmotaAssetStore> store,
            shared_ptr<marmota::MarmotaCache> cache) : _logger(logger), _filename(nullopt), _store(store), _db_cache(cache) {}
        virtual ~SpritesModel() {}

        void add_sprite(unique_ptr<EditorSprite> &item);
        void create_sprite();
        void remove_sprite();

        vector<unique_ptr<EditorSprite>> &get_sprites();

        void on_current_sprite(uint64_t id);
        optional<uint64_t> get_current_sprite();
        void on_no_sprite();

        void set_updated(bool flag);
        bool is_updated();

        bool update_model_from_cache(map<uint64_t, unique_ptr<EditorSprite>> &sprites);
        void load_cache_from_db(const filesystem::path &path);
        void create_new_sprite();
        void update_sprite(uint64_t id, const string &name);
        void create_new_state(uint64_t id, const string &name);

        optional<filesystem::path> _filename;
        atomic_bool _flag_updated;

    private:
        log4cpp::Category &_logger;
        shared_ptr<marmota::MarmotaAssetStore> _store;
        shared_ptr<marmota::MarmotaCache> _db_cache;
        optional<uint64_t> _current_sprite;
        mutex _mutex;
        queue<unique_ptr<UpdateEvt>> _evt_queue;
    };
}