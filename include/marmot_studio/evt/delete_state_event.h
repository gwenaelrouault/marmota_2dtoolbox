#pragma once

#include "update_entity_event.h"

namespace marmot::studio
{
    class DeleteStateEvt : public UpdateEntityEvt
    {
    public:
        explicit DeleteStateEvt(MarmotaId sprite_id, MarmotaId id)
            : UpdateEntityEvt(E_SPRITE, M_CREATE, id), _sprite_id(sprite_id) {}
        virtual ~DeleteStateEvt() {}

        bool apply(map<MarmotaId, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;

        MarmotaId get_sprite_id() const { return _sprite_id; }

        void print(std::ostream& os) const override;

    private:
        MarmotaId _sprite_id;
    };
}