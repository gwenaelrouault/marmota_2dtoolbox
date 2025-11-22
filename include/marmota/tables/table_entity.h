#pragma once

#include "index_table.h"

namespace marmot::marmota
{
    class TableEntity : public IndexTable
    {
    public:
        TableEntity(log4cpp::Category &logger, SQLiteDB &db) : IndexTable(logger, db) {}
        virtual ~TableEntity() {}

        virtual void create();
    };
}