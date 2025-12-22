#pragma once

#include <string>
#include <vector>

#include "sdl_utils.h"
#include "marmota_state.hpp"
#include "editor_frame.h"

using namespace std;

namespace marmot::studio
{
    constexpr size_t INPUT_BUF_STATE_SIZE = 32;

    struct EditorState
    {
        EditorState(MarmotaId id) : _id(id), _loop(false), _frame_speed(0), _speed(0), _width(32), _height(32) {
            for(int i = 0; i < INPUT_BUF_STATE_SIZE; i++) {
                    _input_buf[i] = 0;
            }
        }
        virtual ~EditorState() {}

        void set_name(const string& name);
        string get_name();

        int get_width();
        void set_width(int width);

        int get_height();
        void set_height(int height);

        void create_frame(SDL_Renderer* renderer);
        void remove_frame();

        void replace_frame(TexturePtr img, int index);

        void set(shared_ptr<marmota::MarmotaState> &other);

        char _input_buf[INPUT_BUF_STATE_SIZE];

        MarmotaId _id;
        bool _loop;
        bool _frame_speed;
        int _speed;

        string _name;
        int _width;
        int _height;

        map<MarmotaId, unique_ptr<EditorFrame>> _frames;
    };
}