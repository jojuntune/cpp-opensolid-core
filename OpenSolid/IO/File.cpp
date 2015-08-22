/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
*  ian.e.mackenzie@gmail.com                                                        *
*                                                                                   *
*  This library is free software; you can redistribute it and/or                    *
*  modify it under the terms of the GNU Lesser General Public                       *
*  License as published by the Free Software Foundation; either                     *
*  version 2.1 of the License, or (at your option) any later version.               *
*                                                                                   *
*  This library is distributed in the hope that it will be useful,                  *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
*  Lesser General Public License for more details.                                  *
*                                                                                   *
*  You should have received a copy of the GNU Lesser General Public                 *
*  License along with this library; if not, write to the Free Software              *
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
*                                                                                   *
************************************************************************************/

#include "sqlite3.h"

#include <OpenSolid/IO/File.hpp>

#define FILE_OPEN_ERROR "FileOpenError"

namespace opensolid
{
    struct File::Handle
    {
        sqlite3* database;
        sqlite3_stmt* insert_statement;
        sqlite3_stmt* select_statement;
    };

    File::File(const std::string& filename, bool write_access) : m_handle(new File::Handle()) {
        int flags = write_access ?
            (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE) :
            SQLITE_OPEN_READONLY;
        int result = sqlite3_open_v2(
            filename.c_str(),
            &m_handle->database,
            flags,
            nullptr
        );
        if (result != SQLITE_OK) {throw FileOpenError(filename, mode);}
        if (mode != "r") {
            result = sqlite3_exec(
                _database,
                "BEGIN TRANSACTION;"
                "CREATE TABLE IF NOT EXISTS Model (key TEXT PRIMARY KEY, type TEXT, data BLOB);"
                "CREATE TABLE IF NOT EXISTS FunctionImplementation (pointer INTEGER PRIMARY KEY, data BLOB);"
                "CREATE TABLE IF NOT EXISTS GeometryImplementation (pointer INTEGER PRIMARY KEY, data BLOB);"
                "CREATE TABLE IF NOT EXISTS DomainImplementation (pointer INTEGER PRIMARY KEY, data BLOB);",
                nullptr,
                nullptr,
                nullptr
            );
            if (result) {throw FileOpenError(filename, mode);}
        }
        sqlite3_prepare_v2(
            _database,
            "INSERT OR REPLACE INTO Model VALUES (?1, ?2, ?3)",
            -1,
            &_insert_statement,
            nullptr
        );
        sqlite3_prepare_v2(
            _database,
            "SELECT type, data FROM Model WHERE key=?1",
            -1,
            &_select_statement,
            nullptr
        );
    }

    std::string File::filename() const {
    }
        
    File& File::set(const std::string& key, std::int64_t value) {
    }

    File& File::set(const std::string& key, double value) {
    }

    File& File::set(const std::string& key, const std::string& value) {
    }

    File& File::set(const std::string& key, const Object& value) {
    }

    bool File::has(const std::string& key) const {
    }

    std::int64_t File::size(const std::string& key) const {
    }

    std::int64_t File::getInt(const std::string& key, std::int64_t index = 0) const {
    }

    double File::getDouble(const std::string& key, std::int64_t index = 0) const {
    }

    std::string File::getString(const std::string& key, std::int64_t index = 0) const {
    }

    Object File::getObject(const std::string& key, std::int64_t index = 0) const {
    }
 
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
        if (mode() == "r") {throw FileSetValueError(filename(), mode());}
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
        if (mode != "r") {
            result = sqlite3_exec(
                _database,
                "BEGIN TRANSACTION;"
                "CREATE TABLE IF NOT EXISTS Model (key TEXT PRIMARY KEY, type TEXT, data BLOB);"
                "CREATE TABLE IF NOT EXISTS FunctionImplementation (pointer INTEGER PRIMARY KEY, data BLOB);"
                "CREATE TABLE IF NOT EXISTS GeometryImplementation (pointer INTEGER PRIMARY KEY, data BLOB);"
                "CREATE TABLE IF NOT EXISTS DomainImplementation (pointer INTEGER PRIMARY KEY, data BLOB);",
                nullptr,
                nullptr,
                nullptr
            );
            if (result) {throw FileOpenError(filename, mode);}
        }
        sqlite3_prepare_v2(
            _database,
            "INSERT OR REPLACE INTO Model VALUES (?1, ?2, ?3)",
            -1,
            &_insert_statement,
            nullptr
        );
        sqlite3_prepare_v2(
            _database,
            "SELECT type, data FROM Model WHERE key=?1",
            -1,
            &_select_statement,
            nullptr
        );
    }

    File::~File() {
        if (mode() != "r") {sqlite3_exec(_database, "COMMIT", nullptr, nullptr, nullptr);}
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
