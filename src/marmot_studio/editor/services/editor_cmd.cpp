#include <sstream>
#include <iostream>
#include <iomanip>
#include "editor_cmd.h"

using namespace marmot;

void Cmd::execute(const std::string &cmd)
{
    _logger.infoStream() << "gwen2d:editor:execute " << cmd;
    _cmd_history.push_back("> " + cmd);
    auto tokens = parse_command(cmd);
    if (cmd == "help")
        _cmd_history.push_back("Commandes disponibles: help, clear, exit");
    else if (cmd == "clear")
        _cmd_history.clear();
    else if (cmd == "exit")
        _cmd_history.push_back("(exit non implémenté)");
    else
        _cmd_history.push_back("Commande inconnue: " + cmd);
}

std::vector<std::string> &Cmd::get_history()
{
    return _cmd_history;
}

std::vector<std::string> Cmd::parse_command(const std::string &line)
{
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> std::quoted(token))
    {
        tokens.push_back(token);
    }
    return tokens;
}
