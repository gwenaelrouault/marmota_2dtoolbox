#pragma once

#include <string>
#include <filesystem>
#include<optional>

using namespace std;

namespace marmot::studio
{
        struct MenuModel {
            MenuModel() : _filename(nullopt) {}

            optional<filesystem::path> _filename;
        };
    
}