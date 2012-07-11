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


#include <OpenSolid/Core/Database/Database.hpp>

#include <sqlite/sqlite3.h>

#include <sstream>

namespace opensolid
{
    bool Database::tableExists(const std::string& name) const {
        sqlite3_bind_text(
            _table_check_statement,
            1,
            name.c_str(),
            name.size(),
            SQLITE_STATIC
        );
        sqlite3_step(_table_check_statement);
        bool result = sqlite3_column_int(_table_check_statement, 0) == 1;
        sqlite3_reset(_table_check_statement);
        sqlite3_clear_bindings(_table_check_statement);
    }

    void Database::createTableIfNecessary(
        const std::string& type_name,
        const TypeDescription& type_description
    ) {
        if (!tableExists(type_name)) {
            std::stringstream stream;
            stream << "CREATE TABLE " << type_name;
            stream << "(";
            stream << (type_name + "ID") << " INTEGER PRIMARY KEY, ";
            for (int i = 0; i < type_description.size(); ++i) {
                std::string item_type_name = type_description.typeName(i);
                bool item_is_list = type_description.isList(i);
                std::string item_name = type_description.name(i);
                if (item_is_list) {
                    stream << (item_name + "ID") << " INTEGER, ";
                }
            }
            stream << ");";
        }
    }

    //void Database::createListTableIfNecessary(
    //    const std::string& type_name,
    //    const TypeDescription& type_description
    //) {
    //    createTableIfNecessary(type_name, type_description);
    //    std::string table_name = type_name + TypeName<List>()();
    //    if (!tableExists(table_name)) {
    //        std::stringstream stream;
    //        stream << "CREATE TABLE [" << table_name << "] ";
    //        stream << "(";
    //        stream << "ListID INTEGER, ";
    //        stream << "ItemIndex INTEGER, ";
    //        if (type_name == TypeName<int>()()) {
    //            stream << "Item INTEGER, ";
    //        } else if (type_name == TypeName<double>()()) {
    //            stream << "Item REAL, ";
    //        } else if (type_name == TypeName<std::string>()()) {
    //            stream << "Item TEXT, ";
    //        } else {
    //            stream << "ItemID INTEGER, ";
    //        }
    //        stream << "PRIMARY KEY (ListID, ItemIndex)";
    //        stream << ");";
    //        std::string statement = stream.str();
    //        sqlite3_exec(_database, statement.c_str(), nullptr, nullptr, nullptr);
    //    }
    //}

    int Database::insert(
        const std::string& type_name,
        const TypeDescription& type_description,
        const List& data
    ) {
        assert(type_description.size() <= TypeDescription::MAX_SIZE);
        sqlite3_stmt* insert_statement = _insert_statements[type_description.size()];
        for (int i = 0; i < type_description.size(); ++i) {
            std::string item_type_name = type_description.typeName(i);
            if (item_type_name == TypeName<int>()()) {
            } else if (item_type_name == TypeName<double>()()) {
            } else if (item_type_name == TypeName<std::string>()()) {
            } else {
            }
            if ( i == type_description.size() - 1 ) {
                stream << ")";
            } else {
                stream << ", ";
            }
        }
    }

    std::vector<List> Database::select(
        const std::string& type,
        const TypeDescription& type_description,
        const std::string& clause
    ) const {
    }

    /*
    void Database::getData(
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
        
    void Database::setData(
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
    */

    Database::Database(const std::string& filename, Mode mode) :
        _filename(filename),
        _mode(mode),
        _database(nullptr),
        _insert_statements(TypeDescription::MAX_SIZE + 1) {

        int flags = mode == READ_ONLY ?
            SQLITE_OPEN_READONLY :
            SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;

        int result = sqlite3_open_v2(filename.c_str(), &_database, flags, nullptr);
        if (result) {throw DatabaseOpenError(filename, mode);}

        if (mode == READ_WRITE) {
            sqlite3_exec(_database, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);
        }

        sqlite3_prepare_v2(
            _database,
            "SELECT count(*) FROM SQLITE_MASTER WHERE type='table' AND name=?;",
            -1,
            &_table_check_statement,
            nullptr
        );

        if (!tableExists("Lists")) {
            sqlite3_exec(
                _database,
                "CREATE TABLE Lists (ListID INTEGER PRIMARY KEY, Type TEXT);",
                nullptr,
                nullptr,
                nullptr
            );
        }
        if (!tableExists("ListItems")) {
            sqlite3_exec(
                _database,
                "CREATE TABLE ListItems "
                "(ListID INTEGER, ItemIndex INTEGER, Item, PRIMARY KEY (ListID, ItemIndex));",
                nullptr,
                nullptr,
                nullptr
            );
        }
    }

    Database::~Database() {
        if (mode() == READ_WRITE) {
            sqlite3_exec(_database, "END TRANSACTION;", nullptr, nullptr, nullptr);
        }
        sqlite3_close(_database);
        for (int i = 1; i <= TypeDescription::MAX_SIZE; ++i) {
            sqlite3_finalize(_insert_statements[i]);
        }
        sqlite3_finalize(_table_check_statement);
    }

    std::string Database::filename() const {return _filename;}

    Database::Mode Database::mode() const {return _mode;}

    DatabaseError::DatabaseError(const std::string& filename, Database::Mode mode) :
        _filename(filename), _mode(mode) {}

    std::string DatabaseError::filename() const {return _filename;}

    Database::Mode DatabaseError::mode() const {return _mode;}

    DatabaseOpenError::DatabaseOpenError(
        const std::string& filename,
        Database::Mode mode
    ) : DatabaseError(filename, mode) {}
    
    DatabaseOpenError::~DatabaseOpenError() throw() {}

    const char* DatabaseOpenError::what() const throw() {
        return "DatabaseOpenError";
    }

    DatabaseInsertError::DatabaseInsertError(
        const std::string& filename,
        Database::Mode mode
    ) : DatabaseError(filename, mode) {}
    
    DatabaseInsertError::~DatabaseInsertError() throw() {}

    const char* DatabaseInsertError::what() const throw() {
        return "DatabaseInsertError";
    }
}
