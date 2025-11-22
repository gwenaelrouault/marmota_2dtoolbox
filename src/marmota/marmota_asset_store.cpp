#include "marmota_asset_store.h"
#include "db_error.h"

using namespace marmot::marmota;

void MarmotaAssetStore::open(const filesystem::path& path) {
    sqlite3 *index_db = nullptr;
    int rc = sqlite3_open(path.c_str(), &index_db);
    if (rc) {
        sqlite3_close(index_db);
        throw DBException("Cannot open new project : cannot open metadata database");
    }
    _db_index = make_index_db(index_db);
}