#include <cxxopts.hpp>


void extract(const std::string& json_filename, const std::string& sheet_filenamen , const std::string& db_filename) {
}

int main(int argc, char *argv[])
{
    cxxopts::Options options("g2d_get_sprite", "Utilitaire de creation d'assets à partir de fichiers exports AseSprite");
    options.add_options()("j,json", "export JSON", cxxopts::value<std::string>())("s,sheet", "export PNG", cxxopts::value<std::string>())("o,output", "base de données", cxxopts::value<std::string>());
    auto result = options.parse(argc, argv);
    if (result.count("json") && result.count("sheet") && result.count("output")) {
        auto json_filename = result["json"].as<std::string>();
        auto sheet_filename = result["sheet"].as<std::string>();
        auto db_filename = result["output"].as<std::string>();
        extract(json_filename, sheet_filename, db_filename);
    }
    return 0;
}