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

#ifndef OPENSOLID__FILE_HPP
#define OPENSOLID__FILE_HPP

#include <string>
#include <memory>

#include <OpenSolid/Core/config.hpp>
#include <OpenSolid/Core/Common/Dictionary.hpp>
#include <OpenSolid/Core/Scalar/Interval.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Core/Datum/Datum.hpp>
#include <OpenSolid/Core/Simplex/Simplex.hpp>
#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>
#include <OpenSolid/Core/Domain/Domain.hpp>
#include <OpenSolid/Core/Object/Object.hpp>

struct sqlite3;
struct sqlite3_stmt;

namespace opensolid
{
    class File : public Dictionary<File>
    {
    private:
        std::string _filename;
        std::string _mode;
        sqlite3* _database;
        sqlite3_stmt* _insert_statement;
        sqlite3_stmt* _select_statement;

        OPENSOLID_CORE_EXPORT void getData(
            const std::string& name,
            std::string& type,
            std::string& data
        ) const;
        
        OPENSOLID_CORE_EXPORT void setData(
            const std::string& name,
            const std::string& type,
            const std::string& data
        );

        template <class Type>
        void setValue(const std::string& key, const Type& value);

        template <class Type>
        void getValue(const std::string& key, Type& value) const;

        OPENSOLID_CORE_EXPORT void throwDictionaryError(
            const std::string& name,
            const std::string& requested_type
        ) const;

        friend class Dictionary<File>;
        friend struct GetFileProperty;
    public:
        OPENSOLID_CORE_EXPORT File(const std::string& filename, const std::string& mode);
        OPENSOLID_CORE_EXPORT ~File();

        OPENSOLID_CORE_EXPORT std::string filename() const;
        OPENSOLID_CORE_EXPORT std::string mode() const;
        OPENSOLID_CORE_EXPORT bool has(const std::string& name) const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class FileError : public Error
    {
    private:
        std::string _filename;
        std::string _mode;
    public:
        OPENSOLID_CORE_EXPORT FileError(
            const std::string& filename,
            const std::string& mode
        );

        OPENSOLID_CORE_EXPORT std::string filename() const;
        OPENSOLID_CORE_EXPORT std::string mode() const;
    };

    class FileOpenError : public FileError
    {
    public:
        OPENSOLID_CORE_EXPORT FileOpenError(
            const std::string& filename,
            const std::string& mode
        );
        
        OPENSOLID_CORE_EXPORT ~FileOpenError() throw();
        
        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
    };

    class FileGetValueError : public FileError, public DictionaryError
    {
    public:
        OPENSOLID_CORE_EXPORT FileGetValueError(
            const std::string& filename,
            const std::string& mode,
            const std::string& key,
            const std::string& requested_type
        );
        
        OPENSOLID_CORE_EXPORT ~FileGetValueError() throw();

        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
    };

    class FileSetValueError : public FileError
    {
    public:
        OPENSOLID_CORE_EXPORT FileSetValueError(
            const std::string& filename,
            const std::string& mode
        );
        
        OPENSOLID_CORE_EXPORT ~FileSetValueError() throw();
        
        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    void File::setValue(const std::string& key, const Type& value) {
        Serialization<Type> serialization;
        setData(key, TypeName<Type>()(), serialization(value));
    }

    template <class Type>
    void File::getValue(const std::string& key, Type& value) const {
        std::string type;
        std::string data;
        getData(key, type, data);
        std::string expected_type = TypeName<Type>()();
        if (type != expected_type) {
            throw FileGetValueError(filename(), mode(), key, expected_type);
        }
        Deserialization<Type> deserialization;
        value = deserialization(data);
    }
}

#endif
