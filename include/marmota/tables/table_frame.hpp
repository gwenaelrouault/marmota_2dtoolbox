#pragma once

#include "index_table.hpp"
#include "marmota_frame.hpp"
#include "marmota_state.hpp"

namespace marmot::marmota
{
    class TableFrame : public IndexTable
    {
    public:
        TableFrame(log4cpp::Category &logger, SQLiteDB &db) : IndexTable(logger, db) {}
        virtual ~TableFrame() {}

        virtual void create();

        void load_frames(shared_ptr<MarmotaState>& state);
    };
}