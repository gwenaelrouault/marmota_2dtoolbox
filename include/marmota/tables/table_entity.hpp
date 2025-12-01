#pragma once

#include "index_table.hpp"
#include "marmota_sprite.hpp"
#include <cstdint>

namespace marmot::marmota
{
    class TableEntity : public IndexTable
    {
    public:
        TableEntity(log4cpp::Category &logger, SQLiteDB &db) : IndexTable(logger, db) {}
        virtual ~TableEntity() {}

        virtual void create();

        uint64_t new_entity(const string& name);

        void load_sprites(vector<shared_ptr<MarmotaSprite>>& sprites);
    };
}