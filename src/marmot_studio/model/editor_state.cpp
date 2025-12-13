#include "editor_state.h"

using namespace marmot;
using namespace marmot::studio;

string EditorState::get_name()
{
    return _name;
}

int EditorState::get_height()
{
    return _height;
}

int EditorState::get_width()
{
    return _width;
}

void EditorState::set_width(int width)
{
    _width = width;
}

void EditorState::set_height(int height)
{
    _height = height;
}

void EditorState::set_name(const string &name)
{
    _name = name;
}

void EditorState::create_frame(SDL_Renderer *renderer)
{
    auto frame = make_surface(SDL_CreateRGBSurfaceWithFormat(0, _width, _height, 32, SDL_PIXELFORMAT_RGBA32));
    SDL_FillRect(frame.get(), nullptr, SDL_MapRGBA(frame.get()->format, 255, 255, 255, 255));
    auto tex = make_texture(SDL_CreateTextureFromSurface(renderer, frame.get()));
    _frames.push_back(std::move(tex));
}

void EditorState::remove_frame()
{
    if (!_frames.empty())
    {
        _frames.pop_back();
    }
}

vector<TexturePtr> &EditorState::get_frames()
{
    return _frames;
}

void EditorState::replace_frame(TexturePtr img, int index)
{
    _frames.at(index).swap(img);
}

void EditorState::set(shared_ptr<marmota::MarmotaState> &other)
{
    _id = other->_id;
    _name = other->_name;
    _loop = other->_loop;
    _speed = other->_speed;
    _width = other->_width;
    _height = other->_height;
    _frame_speed = false;
}