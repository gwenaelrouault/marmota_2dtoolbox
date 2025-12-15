#pragma once

#include "update_event.h"

namespace marmot::studio
{
    class CreateStateEvt : public UpdateEvt
    {
    public:
        explicit CreateStateEvt(uint64_t sprite_id, uint64_t id)
            : UpdateEvt(E_SPRITE, M_CREATE, id), _sprite_id(sprite_id) {}
        virtual ~CreateStateEvt() {}

        bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) override;

        void print(std::ostream& os) const override;

        uint64_t get_sprite_id() const { return _sprite_id; }
        

    private:
        uint64_t _sprite_id;
    };
}