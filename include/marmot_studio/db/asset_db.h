#pragma once

#include <mutex>
#include <filesystem>
#include <log4cpp/Category.hh>
#include "marmota_asset_store.hpp"
#include "marmota_cache.hpp"
#include "event_queue.h"

namespace marmot::studio
{
    class AssetDB
    {
    public:
        explicit AssetDB(log4cpp::Category &logger, shared_ptr<marmota::MarmotaCache> cache, shared_ptr<EventQueue> queue) 
            : _logger(logger), _cache(cache), _store(make_unique<marmot::marmota::MarmotaAssetStore>(logger)), _queue(queue) {}
        virtual ~AssetDB() {}

        void open_db(const filesystem::path &path);

        void load_level(const std::string& level_name);
        
        void create_new_sprite();
        void update_sprite(MarmotaId id, const string &name);
        void remove_sprite(MarmotaId id);

        void create_new_state(MarmotaId id, const string &name);
        void delete_state(MarmotaId sprite_id, MarmotaId id);

        void create_new_frame(MarmotaId sprite_id, MarmotaId state_id, int num);


        bool get(map<MarmotaId, unique_ptr<EditorSprite>> &sprites);
        
    private:
        log4cpp::Category &_logger;
        shared_ptr<marmota::MarmotaCache> _cache;
        unique_ptr<marmot::marmota::MarmotaAssetStore> _store;
        shared_ptr<EventQueue> _queue;
        
        mutex _mutex;
    };
}