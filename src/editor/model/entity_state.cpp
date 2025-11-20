#include "entity_state.h"

using namespace marmot;
using namespace marmot::studio;

string EntityState::get_name()
{
    return _name;
}

int EntityState::get_height()
{
    return _height;
}

int EntityState::get_width()
{
    return _width;
}

void EntityState::set_width(int width)
{
    _width = width;
}

void EntityState::set_height(int height)
{
    _height = height;
}

void EntityState::create_frame(SDL_Renderer* renderer) {
    auto frame = make_surface(SDL_CreateRGBSurfaceWithFormat(0, _width, _height, 32, SDL_PIXELFORMAT_RGBA32));
    SDL_FillRect(frame.get(), nullptr, SDL_MapRGBA(frame.get()->format, 255, 255, 255, 255));
    auto tex = make_texture(SDL_CreateTextureFromSurface(renderer, frame.get()));
    _frames.push_back(std::move(tex));
}

void EntityState::remove_frame() {
    _frames.pop_back();
}

vector<TexturePtr> &EntityState::get_frames() {
    return _frames;
}

void EntityState::replace_frame(TexturePtr img, int index) {
    _frames.at(index).swap(img);
}