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

#pragma once

#include <opensolid/Core/config.hpp>

#include <OpenSolid/Core/config.hpp>
#include <OpenSolid/Core/Common/List.hpp>
#include <OpenSolid/Core/Common/TypeDescription.hpp>
#include <OpenSolid/Core/Scalar/Interval.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Core/Datum/Datum.hpp>
#include <OpenSolid/Core/Simplex/Simplex.hpp>
#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>
#include <OpenSolid/Core/Domain/Domain.hpp>
#include <OpenSolid/Core/Object/Object.hpp>

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <unordered_map>

struct sqlite3;
struct sqlite3_stmt;

namespace opensolid
{
    class Database
    {
    public:
        enum Mode {READ_ONLY, READ_WRITE};
    private:
        std::string _filename;
        Mode _mode;
        sqlite3* _database;
        sqlite3_stmt* _table_check_statement;
        std::unordered_map<std::string, sqlite3_stmt*> _insert_statements;
        std::unordered_map<std::string, sqlite3_stmt*> _list_insert_statements;
        std::unordered_map<std::string, sqlite3_stmt*> _select_statements;
        std::unordered_map<std::string, sqlite3_stmt*> _list_select_statements;

        OPENSOLID_CORE_EXPORT bool tableExists(const std::string& name) const;

        OPENSOLID_CORE_EXPORT void createTableIfNecessary(
            const std::string& type_name,
            const TypeDescription& type_description
        );

        OPENSOLID_CORE_EXPORT void createListTableIfNecessary(
            const std::string& type_name,
            const TypeDescription& type_description
        );
        
        OPENSOLID_CORE_EXPORT int insert(
            const std::string& type_name,
            const TypeDescription& type_description,
            const List& data
        );

        OPENSOLID_CORE_EXPORT std::vector<List> select(
            const std::string& type_name,
            const TypeDescription& type_description,
            const std::string& clause
        ) const;

        Database(const Database& other);
        void operator=(const Database& other);
    public:
        OPENSOLID_CORE_EXPORT Database(const std::string& filename, Mode mode);
        OPENSOLID_CORE_EXPORT ~Database();

        OPENSOLID_CORE_EXPORT std::string filename() const;
        OPENSOLID_CORE_EXPORT Mode mode() const;

        template <class Type>
        int insert(const Type& value);

        template <class Type>
        std::vector<Type> select(const std::string& clause) const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class DatabaseError : public Error
    {
    private:
        std::string _filename;
        Database::Mode _mode;
    public:
        OPENSOLID_CORE_EXPORT DatabaseError(
            const std::string& filename,
            Database::Mode mode
        );

        OPENSOLID_CORE_EXPORT std::string filename() const;
        OPENSOLID_CORE_EXPORT Database::Mode mode() const;
    };

    class DatabaseOpenError : public DatabaseError
    {
    public:
        OPENSOLID_CORE_EXPORT DatabaseOpenError(
            const std::string& filename,
            Database::Mode mode
        );
        
        OPENSOLID_CORE_EXPORT ~DatabaseOpenError() throw();
        
        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
    };

    class DatabaseInsertError : public DatabaseError
    {
    public:
        OPENSOLID_CORE_EXPORT DatabaseInsertError(
            const std::string& filename,
            Database::Mode mode
        );
        
        OPENSOLID_CORE_EXPORT ~DatabaseInsertError() throw();
        
        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    int Database::insert(const Type& value) {
        static std::string type_name = TypeName<Type>()();
        static TypeDescription type_description = TypeDescriptionFunction<Type>()();
        return insert(type_name, type_description, List::from(value));
    }

    template <class Type>
    std::vector<Type> Database::select(const std::string& clause) const {
        static std::string type_name = TypeName<Type>()();
        static TypeDescription type_description = TypeDescriptionFunction<Type>()();
        std::vector<List> temp = select(type_name, type_description, clause);
        std::vector<Type> results(temp.size());
        std::transform(temp.begin(), temp.end(), results.begin(), Conversion<List, Type>());
        return results;
    }
}
