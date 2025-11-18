#pragma once

#include <string>

using namespace std;

namespace marmot::studio
{
    class EntityState
    {
    public:
        EntityState(const std::string &name) : _name(name), _width(0), _height(0) {}
        virtual ~EntityState() {}

        string get_name();

        int get_width();
        void set_width(int width);

        int get_height();
        void set_height(int height);

    private:
        string _name;
        int _width;
        int _height;
    };
}