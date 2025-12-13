#pragma once

#include "update_event.h"

namespace marmot::studio
{
    class UpdateStateEvt : public UpdateEvt
    {
    public:
        explicit UpdateStateEvt(uint64_t sprite_id, uint64_t id)
            : UpdateEvt(E_SPRITE, M_CREATE, id), _sprite_id(sprite_id) {}
        virtual ~UpdateStateEvt() {}

        bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;

    private:
        uint64_t _sprite_id;
    };
}