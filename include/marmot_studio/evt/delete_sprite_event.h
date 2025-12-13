#pragma once

#include "update_event.h"

namespace marmot::studio
{
    class DeleteSpriteEvt : public UpdateEvt
    {
    public:
        explicit DeleteSpriteEvt(uint64_t sprite_id, uint64_t id) : UpdateEvt(E_SPRITE, M_CREATE, id) {}
        virtual ~DeleteSpriteEvt() {}

        bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;
    };
}