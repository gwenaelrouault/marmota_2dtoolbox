#pragma once

#include <string>
#include <exception>
#include <filesystem>
#include <optional>
#include <sqlite3.h>
#include "rocksdb/db.h"
#include <log4cpp/Category.hh>

using namespace std;

namespace marmot::marmota
{
    class AssetsDB
    {
    public:
        AssetsDB(log4cpp::Category &logger, const std::string &path) : _logger(logger), _workdir(path), _db_assets(nullptr), _db_metadata(nullptr), _name(nullopt) {}
        virtual ~AssetsDB() {}
        void create(const std::string &name);
        void close();

    private:
        log4cpp::Category &_logger;
        filesystem::path _workdir;
        sqlite3 *_db_metadata;
        rocksdb::DB *_db_assets;
        optional<std::string> _name;
        optional<std::filesystem::path> _db_metadata_path;
        optional<std::filesystem::path> _db_assets_path;

        inline static const string _metadata_suffix = "_metadata.db";
        inline static const string _assets_suffix = "_assets.db";
    };

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