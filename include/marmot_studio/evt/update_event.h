#pragma once

#include <cstdint>
#include "editor_sprite.h"
#include "marmota_cache.hpp"

namespace marmot::studio
{
    enum EntityType
    {
        E_LEVEL,
        E_SPRITE,
        E_STATE,
        E_FRAME
    };

    enum ModificationType
    {
        M_CREATE,
        M_UPDATE,
        M_DELETE
    };

    class UpdateEvt
    {
    public:
        UpdateEvt(EntityType et, ModificationType mt, uint64_t id) : _entity(et), _type(mt), _id(id) {}
        virtual ~UpdateEvt() {}

        virtual bool apply(map<uint64_t, unique_ptr<EditorSprite>> &sprites, shared_ptr<marmota::MarmotaCache> &db_cache) = 0;

    protected:
        EntityType _entity;
        ModificationType _type;
        uint64_t _id;
    };
}