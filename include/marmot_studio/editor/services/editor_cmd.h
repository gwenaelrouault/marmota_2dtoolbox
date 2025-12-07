#pragma once

#include <vector>
#include <string>
#include <log4cpp/Category.hh>

namespace marmot
{
    class Cmd
    {
    public:
        Cmd(log4cpp::Category &logger) : _logger(logger) {}

        void execute(const std::string &cmd);

        std::vector<std::string> &get_history();

    private:
        std::vector<std::string> parse_command(const std::string &line);

        log4cpp::Category &_logger;
        std::vector<std::string> _cmd_history;
    };
}