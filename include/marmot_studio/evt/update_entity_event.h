#pragma once

#include "update_event.h"

namespace marmot::studio
{
    class UpdateEntityEvt : public UpdateEvt
    {
    public:
        UpdateEntityEvt(EntityType et, ModificationType mt, uint64_t id) : UpdateEvt(et, mt), _id(id) {}
        virtual ~UpdateEntityEvt() {}

        virtual bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) = 0;

        uint64_t get_id() const { return _id; }

    protected:
        uint64_t _id;
    };
}