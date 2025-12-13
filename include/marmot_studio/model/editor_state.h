#pragma once

#include <string>
#include <vector>

#include "sdl_utils.h"
#include "marmota_state.hpp"

using namespace std;

namespace marmot::studio
{
    struct EditorState
    {
        EditorState(uint64_t id) : _id(id), _loop(false), _frame_speed(0), _speed(0), _width(0), _height(0) {}
        virtual ~EditorState() {}

        void set_name(const string& name);
        string get_name();

        int get_width();
        void set_width(int width);

        int get_height();
        void set_height(int height);

        void create_frame(SDL_Renderer* renderer);
        void remove_frame();

        vector<TexturePtr> &get_frames();

        void replace_frame(TexturePtr img, int index);

        void set(shared_ptr<marmota::MarmotaState> &other);

        uint64_t _id;
        bool _loop;
        bool _frame_speed;
        int _speed;

        string _name;
        int _width;
        int _height;
        vector<TexturePtr> _frames;
    };
}