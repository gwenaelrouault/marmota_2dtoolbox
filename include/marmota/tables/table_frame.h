#pragma once

#include "index_table.h"

namespace marmot::marmota
{
    class TableFrame : public IndexTable
    {
    public:
        TableFrame(log4cpp::Category &logger, SQLiteDB &db) : IndexTable(logger, db) {}
        virtual ~TableFrame() {}

        virtual void create();
    };
}