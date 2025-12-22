#pragma once

#include "update_entity_event.h"

namespace marmot::studio
{
    class DeleteSpriteEvt : public UpdateEntityEvt
    {
    public:
        explicit DeleteSpriteEvt(MarmotaId id) : UpdateEntityEvt(E_SPRITE, M_CREATE, id) {}
        virtual ~DeleteSpriteEvt() {}

        bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;

        void print(std::ostream& os) const override;
    };
}