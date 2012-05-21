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
    void File::getData(
        const std::string& key,
        std::string& type,
        std::string& data
    ) const {
        sqlite3_bind_text(_select_statement, 1, key.c_str(), key.size(), SQLITE_STATIC);
        if (sqlite3_step(_select_statement) != SQLITE_ROW) {throwDictionaryError(key, "");}
        type.assign(
            (const char*) sqlite3_column_text(_select_statement, 0),
            sqlite3_column_bytes(_select_statement, 0)
        );
        data.assign(
            (const char*) sqlite3_column_text(_select_statement, 1),
            sqlite3_column_bytes(_select_statement, 1)
        );
        sqlite3_reset(_select_statement);
        sqlite3_clear_bindings(_select_statement);
    }
        
    void File::setData(
        const std::string& key,
        const std::string& type,
        const std::string& data
    ) {
        sqlite3_bind_text(_insert_statement, 1, key.c_str(), key.size(), SQLITE_STATIC);
        sqlite3_bind_text(_insert_statement, 2, type.c_str(), type.size(), SQLITE_STATIC);
        sqlite3_bind_blob(_insert_statement, 3, data.c_str(), data.size(), SQLITE_STATIC);
        if (sqlite3_step(_insert_statement) != SQLITE_DONE) {
            throw FileSetValueError(filename(), mode());
        }
        sqlite3_reset(_insert_statement);
        sqlite3_clear_bindings(_insert_statement);
    }

    void File::throwDictionaryError(
        const std::string& key,
        const std::string& requested_type
    ) const {throw FileGetValueError(filename(), mode(), key, requested_type);}

    File::File(const std::string& filename, const std::string& mode) :
        _filename(filename),
        _mode(mode),
        _database(nullptr),
        _insert_statement(nullptr),
        _select_statement(nullptr) {
        int flags = 0;
        if (mode == "r") {
            flags = SQLITE_OPEN_READONLY;
        } else if (mode == "rw") {
            flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
        } else {
            throw FileOpenError(filename, mode);
        }
        int result = sqlite3_open_v2(filename.c_str(), &_database, flags, nullptr);
        if (result) {throw FileOpenError(filename, mode);}
        result = sqlite3_exec(
            _database,
            "BEGIN TRANSACTION;"
            "CREATE TABLE IF NOT EXISTS Model (Key TEXT PRIMARY KEY, Type TEXT, Data BLOB);"
            "CREATE TABLE IF NOT EXISTS FunctionImplementation (Pointer INTEGER PRIMARY KEY, Data BLOB);"
            "CREATE TABLE IF NOT EXISTS GeometryImplementation (Pointer INTEGER PRIMARY KEY, Data BLOB);"
            "CREATE TABLE IF NOT EXISTS DomainImplementation (Pointer INTEGER PRIMARY KEY, Data BLOB);",
            nullptr,
            nullptr,
            nullptr
        );
        if (result) {throw FileOpenError(filename, mode);}
        sqlite3_prepare_v2(
            _database,
            "INSERT OR REPLACE INTO Model VALUES (?1, ?2, ?3)",
            -1,
            &_insert_statement,
            nullptr
        );
        sqlite3_prepare_v2(
            _database,
            "SELECT type, data FROM Model WHERE Key=?1",
            -1,
            &_select_statement,
            nullptr
        );
    }

    File::~File() {
        sqlite3_exec(_database, "COMMIT", nullptr, nullptr, nullptr);
        sqlite3_close(_database);
        sqlite3_finalize(_insert_statement);
        sqlite3_finalize(_select_statement);
    }

    std::string File::filename() const {return _filename;}

    std::string File::mode() const {return _mode;}

    bool File::has(const std::string& key) const {
        sqlite3_bind_text(_select_statement, 1, key.c_str(), key.size(), SQLITE_STATIC);
        bool result = sqlite3_step(_select_statement) != SQLITE_DONE;
        sqlite3_reset(_select_statement);
        return result;
    }

    FileError::FileError(const std::string& filename, const std::string& mode) :
        _filename(filename), _mode(mode) {}

    std::string FileError::filename() const {return _filename;}

    std::string FileError::mode() const {return _mode;}

    FileOpenError::FileOpenError(
        const std::string& filename,
        const std::string& mode
    ) : FileError(filename, mode) {}
    
    FileOpenError::~FileOpenError() throw() {}

    const char* FileOpenError::what() const throw() {
        return "FileOpenError";
    }

    FileGetValueError::FileGetValueError(
        const std::string& filename,
        const std::string& mode,
        const std::string& key,
        const std::string& requested_type
    ) : FileError(filename, mode), DictionaryError(key, requested_type) {}
    
    FileGetValueError::~FileGetValueError() throw() {}

    const char* FileGetValueError::what() const throw() {
        return "FileGetValueError";
    }

    FileSetValueError::FileSetValueError(
        const std::string& filename,
        const std::string& mode
    ) : FileError(filename, mode) {}
    
    FileSetValueError::~FileSetValueError() throw() {}

    const char* FileSetValueError::what() const throw() {
        return "FileSetValueError";
    }
}
