#pragma once

#include <string>

using namespace std;

namespace marmot::marmota
{
    class DBException : public exception
    {
    public:
        explicit DBException(string message)
            : _message(std::move(message)) {}

        const char *what() const noexcept override
        {
            return _message.c_str();
        }

    private:
        std::string _message;
    };
}