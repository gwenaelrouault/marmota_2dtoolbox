#pragma once

#include "index_table.hpp"

namespace marmot::marmota
{
    class TableState : public IndexTable
    {
    public:
        TableState(log4cpp::Category &logger, SQLiteDB &db) : IndexTable(logger, db) {}
        virtual ~TableState() {}

        virtual void create();
    };
}