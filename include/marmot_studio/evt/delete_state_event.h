#pragma once

#include "update_event.h"

namespace marmot::studio
{
    class DeleteStateEvt : public UpdateEvt
    {
    public:
        explicit DeleteStateEvt(uint64_t sprite_id, uint64_t id)
            : UpdateEvt(E_SPRITE, M_CREATE, id), _sprite_id(sprite_id) {}
        virtual ~DeleteStateEvt() {}

        bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;

        uint64_t get_sprite_id() const { return _sprite_id; }

        void print(std::ostream& os) const override;

    private:
        uint64_t _sprite_id;
    };
}