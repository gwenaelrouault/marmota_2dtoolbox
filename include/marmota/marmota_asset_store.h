#pragma once

#include <log4cpp/Category.hh>
#include <filesystem>

#include "table_entity.h"
#include "table_state.h"
#include "table_frame.h"
#include "model.h"

using namespace std;

namespace marmot::marmota
{
    class MarmotaAssetStore
    {
    public:
        MarmotaAssetStore(log4cpp::Category &logger) : 
        _logger(logger), 
        _db_index(nullptr), 
        _table_entity(nullptr), _table_state(nullptr), _table_frame(nullptr), _model(make_shared<Model>()) {}
        virtual ~MarmotaAssetStore() {}

        void open(const filesystem::path &path);
        uint64_t create_sprite(const string& name);
        int create_state(int entity_id, const string& name);
        int create_frame(int state_id);

        void load_entity(uint64_t id, Sprite& sprite);
    private:
        log4cpp::Category & _logger;
        SQLiteDB _db_index;
        unique_ptr<TableEntity> _table_entity;
        unique_ptr<TableState> _table_state;
        unique_ptr<TableFrame> _table_frame;
        shared_ptr<Model> _model;
    };
}