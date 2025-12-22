#pragma once

#include "index_table.hpp"
#include "marmota_state.hpp"
#include "marmota_sprite.hpp"

namespace marmot::marmota
{
    class TableState : public IndexTable
    {
    public:
        TableState(log4cpp::Category &logger, SQLiteDB db) : IndexTable(logger, db) {}
        virtual ~TableState() {}

        virtual void create() override;

        virtual void delete_item(MarmotaId id) override;

        MarmotaId new_entity(MarmotaId sprite_id, const string &name);

        void load_states(shared_ptr<MarmotaSprite> sprite);

        shared_ptr<MarmotaState> load_state(MarmotaId id);

    private:
        shared_ptr<MarmotaState> make_state_from_result(sqlite3_stmt *stmt);
    };
}