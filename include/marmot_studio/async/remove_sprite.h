#pragma once

#include <filesystem>
#include <log4cpp/Category.hh>
#include <cstdint>
#include "task.hpp"
#include "sprites_model.h"

using namespace std;

using namespace marmot;

namespace marmot::studio
{

    constexpr int ERROR_SPRITE_REMOVE = 1;

    class RemoveSpriteJob
    {
    public:
        RemoveSpriteJob(log4cpp::Category &logger,
                        shared_ptr<SpritesModel> model,
                        uint64_t id)
            : _logger(logger), _model(model), _id(id) {}
        virtual ~RemoveSpriteJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<SpritesModel> _model;
        uint64_t _id;
    };

    class RemoveSprite : public Task<RemoveSpriteJob>
    {
    public:
        RemoveSprite(log4cpp::Category &logger, RemoveSpriteJob job) : Task(job), _logger(logger) {}
        virtual ~RemoveSprite() {}

    private:
        log4cpp::Category &_logger;
    };
}