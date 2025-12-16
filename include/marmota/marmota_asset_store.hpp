#pragma once

#include <log4cpp/Category.hh>
#include <filesystem>
#include "rocksdb/db.h"
#include "table_sprite.hpp"
#include "table_state.hpp"
#include "table_frame.hpp"
#include "table_level.hpp"
#include "table_level_sprite.hpp"
#include "marmota_cache.hpp"

using namespace std;

namespace marmot::marmota
{
    class MarmotaAssetStore
    {
    public:
        MarmotaAssetStore(log4cpp::Category &logger) : _logger(logger),
                                                       _db_index(nullptr),
                                                       _table_sprite(nullptr), 
                                                       _table_state(nullptr), 
                                                       _table_frame(nullptr),
                                                       _table_level(nullptr),
                                                       _table_level_sprite(nullptr),
                                                       _db_assets(nullptr) {}
        virtual ~MarmotaAssetStore() {}

        void open(shared_ptr<MarmotaCache> cache, const filesystem::path &path);
        
        uint64_t create_sprite(shared_ptr<MarmotaCache> cache);
        uint64_t create_state(shared_ptr<MarmotaCache> cache, uint64_t entity_id, const string &name);
        uint64_t create_frame(uint64_t state_id);

        void load_level(shared_ptr<MarmotaCache> cache, const string& name);
        void load_sprite(shared_ptr<MarmotaCache> cache, MarmotaId id);
        void load_state(shared_ptr<MarmotaCache> cache, MarmotaId sprite_id, MarmotaId id);

        void update_sprite(shared_ptr<MarmotaCache> cache, uint64_t id, const string& name);

        void remove_sprite(shared_ptr<MarmotaCache> cache, uint64_t id);

    private:

        inline void create_tables();

        log4cpp::Category &_logger;
        SQLiteDB _db_index;
        unique_ptr<TableSprite> _table_sprite;
        unique_ptr<TableState> _table_state;
        unique_ptr<TableFrame> _table_frame;
        unique_ptr<TableLevel> _table_level;
        unique_ptr<TableLevelSprite> _table_level_sprite;
        rocksdb::DB *_db_assets;
    };
}