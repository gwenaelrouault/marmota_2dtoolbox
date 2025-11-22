#pragma once

#include <log4cpp/Category.hh>
#include <filesystem>

#include "table_entity.h"
#include "table_state.h"
#include "table_frame.h"

using namespace std;

namespace marmot::marmota
{
    class MarmotaAssetStore
    {
    public:
        MarmotaAssetStore(log4cpp::Category &logger) : _db_index(nullptr), _table_entity(nullptr), _table_state(nullptr), _table_frame(nullptr) {}
        virtual ~MarmotaAssetStore() {}

        void open(const filesystem::path &path);

    private:
        SQLiteDB _db_index;
        unique_ptr<TableEntity> _table_entity;
        unique_ptr<TableState> _table_state;
        unique_ptr<TableFrame> _table_frame;
    };
}