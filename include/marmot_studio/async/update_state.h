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

    constexpr int ERROR_STATE_UPDATE = 1;

    class UpdateStateJob
    {
    public:
        explicit UpdateStateJob(log4cpp::Category &logger,
                        shared_ptr<AssetDB> db,
                        MarmotaId sprite_id,
                        MarmotaId id,
                        const string& name,
                        bool loop,
                        int speed,
                        int width,
                        int height)
            : _logger(logger), _db(db), _id(id), _sprite_id(sprite_id), _name(name), _loop(loop), _speed(speed), _width(width), _height(height) {}
        virtual ~UpdateStateJob() {}
        int execute();
        void onSuccess();
        void onFailed(int err_code);

    private:
        log4cpp::Category &_logger;
        shared_ptr<AssetDB> _db;
        MarmotaId _id;
        MarmotaId _sprite_id;
        string _name;
        bool _loop;
        bool _frame_speed;
        int _speed;
        int _width;
        int _height;
    };

    class UpdateState : public Task<UpdateStateJob>
    {
    public:
        explicit UpdateState(log4cpp::Category &logger, UpdateStateJob job) : Task(job), _logger(logger) {}
        virtual ~UpdateState() {}

    private:
        log4cpp::Category &_logger;
    };
}