#pragma once

#include <log4cpp/Category.hh>
#include <filesystem>
#include "rocksdb/db.h"
#include "table_sprite.hpp"
#include "table_state.hpp"
#include "table_frame.hpp"
#include "marmota_cache.hpp"

using namespace std;

namespace marmot::marmota
{
    class MarmotaAssetStore
    {
    public:
        MarmotaAssetStore(log4cpp::Category &logger) : _logger(logger),
                                                       _db_index(nullptr),
                                                       _table_sprite(nullptr), _table_state(nullptr), _table_frame(nullptr), _db_assets(nullptr) {}
        virtual ~MarmotaAssetStore() {}

        

        int create_state(int entity_id, const string &name);
        int create_frame(int state_id);

        void open(shared_ptr<MarmotaCache>& cache, const filesystem::path &path);
        uint64_t create_sprite(shared_ptr<MarmotaCache>& cache);
        void load_sprite(shared_ptr<MarmotaCache>& cache, uint64_t id);

    private:
        log4cpp::Category &_logger;
        SQLiteDB _db_index;
        unique_ptr<TableSprite> _table_sprite;
        unique_ptr<TableState> _table_state;
        unique_ptr<TableFrame> _table_frame;
        rocksdb::DB *_db_assets;
    };
}