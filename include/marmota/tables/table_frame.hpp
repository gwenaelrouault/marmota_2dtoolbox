#pragma once

#include "index_table.hpp"
#include "marmota_frame.hpp"

namespace marmot::marmota
{
    class TableFrame : public IndexTable
    {
    public:
        TableFrame(log4cpp::Category &logger, SQLiteDB &db) : IndexTable(logger, db) {}
        virtual ~TableFrame() {}

        virtual void create();

        void load_frames(vector<shared_ptr<MarmotaFrame>>& frames, uint64_t state_id);
    };
}