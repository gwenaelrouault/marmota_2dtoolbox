#include "table_frame.hpp"
#include "db_error.hpp"

using namespace marmot::marmota;

void TableFrame::create()
{
    const char *query = R"(
        CREATE TABLE IF NOT EXISTS frame (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            num INTEGER NOT NULL DEFAULT 0,
            state_id  INTEGER NOT NULL,
            FOREIGN KEY (state_id) REFERENCES state(id)
                ON DELETE CASCADE
                ON UPDATE CASCADE  
            );
        )";
    exec(query);
    _logger.infoStream() << "Marmota:Table[FRAME]:created";
}

void TableFrame::load_frames(shared_ptr<MarmotaState> state)
{
    _logger.infoStream() << "Marmota:Table[FRAME]:load(" << state->_id << ")";
    state->_frames.clear();
    // create query -----------------------------------------------------------
    const char *query = R"(
        SELECT id,num,state_id FROM frame WHERE state_id = ?;
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_int(stmt, 1, state->_id);
    // fill vector with query result -------------------------------------------
    while (run_query(stmt) == SQLITE_ROW)
    {
        MarmotaId id = (MarmotaId)sqlite3_column_int(stmt, 0);
        state->_frames[id] = make_frame_from_result(stmt);
    }
    release_query(stmt);
    _logger.infoStream() << "Marmota:Table[FRAME]:Loaded " << state->_frames.size() << " from table frame for FRAME (" << state->_id << ")";
}

shared_ptr<MarmotaFrame> TableFrame::load_frame(MarmotaId id) {
    _logger.infoStream() << "Marmota:Table[FRAME]:load(" << id << ")";
    const char *query = R"(
        SELECT id,num,state_id FROM frame WHERE id=?;
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_int(stmt, 1, id);
    if (run_query(stmt) == SQLITE_ROW)
    {
        return make_frame_from_result(stmt);
    }
    release_query(stmt);
    throw DBException("No frame");
}

shared_ptr<MarmotaFrame> TableFrame::make_frame_from_result(sqlite3_stmt *stmt) {
    MarmotaId id = (MarmotaId) sqlite3_column_int(stmt, 0);
    int num = sqlite3_column_int(stmt, 1);
    MarmotaId state_id = sqlite3_column_int(stmt, 1);

    auto loaded = make_shared<MarmotaFrame>(id, state_id, num);
    _logger.infoStream() << "Marmota:Table[FRAME]:loaded(" << loaded << ")";
    release_query(stmt);
    return loaded;
}

void TableFrame::delete_item(MarmotaId id)
{
    _logger.infoStream() << "Marmota:Table[FRAME]:delete(" << id << ")";
}

MarmotaId TableFrame::new_entity(MarmotaId state_id, int num)
{
    _logger.infoStream() << "Marmota:Table[FRAME]:new(state=" << state_id << ")";
    MarmotaId id = 0;
    const char *query = R"(
        INSERT INTO frame (num,state_id) VALUES (?,?);
        )";
    sqlite3_stmt *stmt = prepare_query(query);
    sqlite3_bind_int(stmt, 1, num);
    sqlite3_bind_int(stmt, 2, state_id);
    if (run_query(stmt) != SQLITE_DONE)
    {
        release_query(stmt);
        raise_db_error("frame");
    }
    else
    {
        sqlite3_int64 newId = sqlite3_last_insert_rowid(_db.get());
        _logger.infoStream() << "Marmota:Table[FRAME]:added (" << newId << ")";
        release_query(stmt);
        id = (MarmotaId)newId;
    }
    return id;
}