/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <sqlite/sqlite3.h>
#include <OpenSolid/Core/File/File.hpp>

namespace opensolid
{
    struct File::SQL
    {
        sqlite3* database;
        sqlite3_stmt* insert_statement;
        sqlite3_stmt* select_statement;
    };

    void File::getData(
        const std::string& name,
        std::string& type,
        std::string& data
    ) const {
        if (!isOpen()) {throw FilePropertyError(filename(), mode(), isOpen(), "", "");}
        sqlite3_bind_text(_sql->select_statement, 1, name.c_str(), name.size(), SQLITE_STATIC);
        if (sqlite3_step(_sql->select_statement) != SQLITE_ROW) {throwPropertyError(name, "");}
        type.assign(
            (const char*) sqlite3_column_text(_sql->select_statement, 0),
            sqlite3_column_bytes(_sql->select_statement, 0)
        );
        data.assign(
            (const char*) sqlite3_column_text(_sql->select_statement, 1),
            sqlite3_column_bytes(_sql->select_statement, 1)
        );
        sqlite3_reset(_sql->select_statement);
        sqlite3_clear_bindings(_sql->select_statement);
    }
        
    void File::setData(
        const std::string& name,
        const std::string& type,
        const std::string& data
    ) {
        if (!isOpen()) {throw FilePropertyError(filename(), mode(), isOpen(), "", "");}
        sqlite3_bind_text(_sql->insert_statement, 1, name.c_str(), name.size(), SQLITE_STATIC);
        sqlite3_bind_text(_sql->insert_statement, 2, type.c_str(), type.size(), SQLITE_STATIC);
        sqlite3_bind_blob(_sql->insert_statement, 3, data.c_str(), data.size(), SQLITE_STATIC);
        if (sqlite3_step(_sql->insert_statement) != SQLITE_DONE) {
            throw FileSetPropertyError(filename(), mode(), isOpen());
        }
        sqlite3_reset(_sql->insert_statement);
        sqlite3_clear_bindings(_sql->insert_statement);
    }

    void File::throwPropertyError(
        const std::string& name,
        const std::string& requested_type
    ) const {throw FilePropertyError(filename(), mode(), isOpen(), name, requested_type);}

    File::File(const std::string& filename) : _filename(filename) {}

    File::~File() {close();}

    std::string File::filename() const {return _filename;}

    void File::open(const std::string& mode) {
        if (isOpen()) {throw FileOpenError(filename(), mode, isOpen());}
        sqlite3* database = nullptr;
        int flags = 0;
        if (mode == "r") {
            flags = SQLITE_OPEN_READONLY;
        } else if (mode == "rw") {
            flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
        } else {
            throw FileOpenError(filename(), mode, isOpen());
        }
        int result = sqlite3_open_v2(filename().c_str(), &database, flags, nullptr);
        if (result) {throw FileOpenError(filename(), mode, isOpen());}
        _mode = mode;
        _sql.reset(new File::SQL);
        _sql->database = database;
        result = sqlite3_exec(
            _sql->database,
            "BEGIN TRANSACTION;"
            "CREATE TABLE IF NOT EXISTS Model (name TEXT PRIMARY KEY, type TEXT, data BLOB);"
            "CREATE TABLE IF NOT EXISTS FunctionImplementation (pointer INTEGER PRIMARY KEY, data BLOB);"
            "CREATE TABLE IF NOT EXISTS GeometryImplementation (pointer INTEGER PRIMARY KEY, data BLOB);"
            "CREATE TABLE IF NOT EXISTS DomainImplementation (pointer INTEGER PRIMARY KEY, data BLOB);",
            nullptr,
            nullptr,
            nullptr
        );
        if (result) {throw FileOpenError(filename(), mode, isOpen());}
        sqlite3_prepare_v2(
            _sql->database,
            "INSERT OR REPLACE INTO Model VALUES (?1, ?2, ?3)",
            -1,
            &(_sql->insert_statement),
            nullptr
        );
        sqlite3_prepare_v2(
            _sql->database,
            "SELECT type, data FROM Model WHERE name=?1",
            -1,
            &(_sql->select_statement),
            nullptr
        );
    }

    std::string File::mode() const {return _mode;}

    bool File::isOpen() const {return _sql;}

    void File::close() {
        if (isOpen()) {
            sqlite3_exec(_sql->database, "COMMIT", nullptr, nullptr, nullptr);
            sqlite3_close(_sql->database);
            sqlite3_finalize(_sql->insert_statement);
            sqlite3_finalize(_sql->select_statement);
            _sql.reset();
        }
    }

    bool File::has(const std::string& name) const {
        if (!isOpen()) {throw FilePropertyError(filename(), mode(), isOpen(), "", "");}
        sqlite3_bind_text(_sql->select_statement, 1, name.c_str(), name.size(), SQLITE_STATIC);
        bool result = sqlite3_step(_sql->select_statement) != SQLITE_DONE;
        sqlite3_reset(_sql->select_statement);
        return result;
    }

    FileOpenError::FileOpenError(
        const std::string& filename,
        const std::string& mode,
        bool is_open
    ) : _filename(filename), _mode(mode), _is_open(is_open) {}
    
    FileOpenError::~FileOpenError() throw() {}

    const char* FileOpenError::what() const {
        return "FileOpenError";
    }

    std::string FileOpenError::filename() const {return _filename;}

    std::string FileOpenError::mode() const {return _mode;}

    FilePropertyError::FilePropertyError(
        const std::string& filename,
        const std::string& mode,
        bool is_open,
        const std::string& name,
        const std::string& requested_type
    ) : PropertyError(name, requested_type), _filename(filename), _mode(mode), _is_open(is_open) {}
    
    FilePropertyError::~FilePropertyError() throw() {}

    const char* FilePropertyError::what() const {
        return "FilePropertyError";
    }

    std::string FilePropertyError::filename() const {return _filename;}

    std::string FilePropertyError::mode() const {return _mode;}

    bool FilePropertyError::isOpen() const {return _is_open;}

    FileSetPropertyError::FileSetPropertyError(
        const std::string& filename,
        const std::string& mode,
        bool is_open
    ) : _filename(filename), _mode(mode), _is_open(is_open) {}
    
    FileSetPropertyError::~FileSetPropertyError() throw() {}

    const char* FileSetPropertyError::what() const {
        return "FileSetPropertyError";
    }

    std::string FileSetPropertyError::filename() const {return _filename;}

    std::string FileSetPropertyError::mode() const {return _mode;}
}
