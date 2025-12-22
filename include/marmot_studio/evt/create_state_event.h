#pragma once

#include "update_entity_event.h"

namespace marmot::studio
{
    class CreateStateEvt : public UpdateEntityEvt
    {
    public:
        explicit CreateStateEvt(MarmotaId sprite_id, MarmotaId id)
            : UpdateEntityEvt(E_SPRITE, M_CREATE, id), _sprite_id(sprite_id) {}
        virtual ~CreateStateEvt() {}

        bool apply(map<MarmotaId, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;

        void print(std::ostream &os) const override;

        uint64_t get_sprite_id() const { return _sprite_id; }

    private:
        MarmotaId _sprite_id;
    };
}