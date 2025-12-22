#pragma once

#include <filesystem>
#include <log4cpp/Category.hh>
#include <cstdint>
#include "task.hpp"
#include "asset_db.h"

using namespace std;

using namespace marmot;

namespace marmot::studio
{

    constexpr int ERROR_FRAME_CREATE = 1;

    class CreateFrameJob
    {
    public:
        explicit CreateFrameJob(log4cpp::Category &logger,
                       shared_ptr<AssetDB> db,
                       MarmotaId sprite_id,
                       MarmotaId state_id,
                       int num_frame,
                       int width,
                       int height)
            : _logger(logger), _db(db), sprite_id(sprite_id), state_id(state_id), _num_frame(num_frame), _width(width), _height(height) {}
        virtual ~CreateFrameJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<AssetDB> _db;
        MarmotaId sprite_id;
        MarmotaId state_id;
        int _num_frame;
        int _width;
        int _height;
    };

    class CreateFrame : public Task<CreateFrameJob>
    {
    public:
        explicit CreateFrame(log4cpp::Category &logger, CreateFrameJob job) : Task(job), _logger(logger) {}
        virtual ~CreateFrame() {}

    private:
        log4cpp::Category &_logger;
    };
}