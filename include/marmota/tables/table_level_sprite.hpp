#pragma once

#include "index_table.hpp"

namespace marmot::marmota
{
    class TableLevelSprite : public IndexTable
    {
    public:
        TableLevelSprite(log4cpp::Category &logger, SQLiteDB &db) : IndexTable(logger, db) {}
        virtual ~TableLevelSprite() {}

        virtual void create();

        uint64_t add_sprite_to_level(uint64_t sprite_id, uint64_t level_id);
    };
}