#pragma once

#include "index_table.hpp"
#include "marmota_state.hpp"

namespace marmot::marmota
{
    class TableState : public IndexTable
    {
    public:
        TableState(log4cpp::Category &logger, SQLiteDB &db) : IndexTable(logger, db) {}
        virtual ~TableState() {}

        virtual void create();

        void load_states(vector<shared_ptr<MarmotaState>>& states, uint64_t entity_id);
    };
}