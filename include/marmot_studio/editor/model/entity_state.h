#pragma once

#include <string>
#include <vector>

#include "sdl_utils.h"

using namespace std;

namespace marmot::studio
{
    class EntityState
    {
    public:
        EntityState(const std::string &name) : _loop(false), _frame_speed(0), _speed(0), _name(name), _width(0), _height(0) {}
        virtual ~EntityState() {}

        string get_name();

        int get_width();
        void set_width(int width);

        int get_height();
        void set_height(int height);

        void create_frame(SDL_Renderer* renderer);
        void remove_frame();

        vector<TexturePtr> &get_frames();

        void replace_frame(TexturePtr img, int index);

        bool _loop;
        bool _frame_speed;
        int _speed;
    private:
        string _name;
        int _width;
        int _height;
        vector<TexturePtr> _frames;
    };
}