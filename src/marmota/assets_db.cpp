#include "assets_db.h"

using namespace marmot::marmota;

namespace fs = std::filesystem;

void AssetsDB::create(const std::string &name)
{
   _logger.infoStream() << "gwen2d:DB:try to create " << name;
    fs::path project_path = _workdir / name;
    if (fs::exists(project_path))
    {
        throw DBException("Cannot create new project : already exists");
    }
    if (!fs::create_directories(project_path)) {
        throw DBException("Cannot create project directory");
    }
    _logger.infoStream() << "gwen2d:DB:" << project_path.c_str() << " created";
    rocksdb::DB *db;
    rocksdb::Options options;
    options.create_if_missing = true;
    fs::path assets_db_path = project_path / _assets_suffix;
    rocksdb::Status status = rocksdb::DB::Open(options, assets_db_path, &db);
    if (!status.ok())
    {
        throw DBException("Cannot create new project : cannot open asset database");
    }
    _logger.infoStream() << "gwen2d:DB:" << assets_db_path.c_str() << " created";
    sqlite3 *metadata_db = nullptr;
    fs::path metadata_db_path = project_path / _metadata_suffix;
    int rc = sqlite3_open(metadata_db_path.c_str(), &metadata_db);
    if (rc)
    {
        sqlite3_close(metadata_db);
        delete db;
        throw DBException("Cannot create new project : cannot open metadata database");
    }
    _logger.infoStream() << "gwen2d:DB:" << metadata_db_path.c_str() << " created";
    _db_metadata = metadata_db;
    _db_metadata_path = metadata_db_path;
    _db_assets_path = assets_db_path;
    _db_assets = db;
    _name = name;
}

void AssetsDB::close()
{
    if (_name.has_value())
    {
        _logger.infoStream() << "gwen2d:DB:close " << _name.value();
        if (_db_assets != nullptr)
        {
            delete _db_assets;
            _db_assets_path = std::nullopt;
        }
        if (_db_metadata != nullptr)
        {
            sqlite3_close(_db_metadata);
            _db_assets_path = std::nullopt;
        }
        _name = std::nullopt; 
    }
}