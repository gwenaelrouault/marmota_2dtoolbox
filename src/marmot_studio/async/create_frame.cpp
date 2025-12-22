#include "create_frame.h"
#include "db_error.hpp"
#include "sdl_utils.h"

using namespace marmot::studio;

void CreateFrameJob::onSuccess()
{
    _logger.infoStream() << "ASYNC:CreateSprite:create new frame [OK]";
}

void CreateFrameJob::onFailed(int err_code)
{
    _logger.infoStream() << "ASYNC:CreateSprite:create new frame [KO]";
}

int CreateFrameJob::execute()
{
    try
    {
        _logger.infoStream() << "ASYNC:CreateSprite:create new sprite";
        auto frame = make_surface(SDL_CreateRGBSurfaceWithFormat(0, _width, _height, 32, SDL_PIXELFORMAT_RGBA32));
        SDL_FillRect(frame.get(), nullptr, SDL_MapRGBA(frame.get()->format, 255, 255, 255, 255));

        _db->create_new_sprite();
        _logger.infoStream() << "ASYNC:created new sprite";
    }
    catch (marmota::DBException &e)
    {
        _logger.errorStream() << "ASYNC:CreateSprite:Error(" << e.what() << ")";
        return ERROR_FRAME_CREATE;
    }
    return RESULT_OK;
}
