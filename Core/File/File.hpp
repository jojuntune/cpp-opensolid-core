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
#include <OpenSolid/Core/Common/PropertyMap.hpp>
#include <OpenSolid/Core/Scalar/Interval.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Core/Datum/Datum.hpp>
#include <OpenSolid/Core/Simplex/Simplex.hpp>
#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>
#include <OpenSolid/Core/Domain/Domain.hpp>
#include <OpenSolid/Core/Object/Object.hpp>

struct sqlite3;

namespace opensolid
{
    class File : public PropertyMap<File>
    {
    private:
        std::string _filename;
        std::string _mode;

        struct SQL;
        std::unique_ptr<SQL> _sql;

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
        void setProperty(const std::string& name, const Type& value);

        template <class Type>
        void getProperty(const std::string& name, Type& value) const;

        OPENSOLID_CORE_EXPORT void throwPropertyError(
            const std::string& name,
            const std::string& requested_type
        ) const;

        friend class PropertyMap<File>;
        friend struct GetFileProperty;
    public:
        OPENSOLID_CORE_EXPORT File(const std::string& filename);
        OPENSOLID_CORE_EXPORT ~File();

        OPENSOLID_CORE_EXPORT std::string filename() const;
        OPENSOLID_CORE_EXPORT void open(const std::string& mode);
        OPENSOLID_CORE_EXPORT std::string mode() const;
        OPENSOLID_CORE_EXPORT bool isOpen() const;
        OPENSOLID_CORE_EXPORT void close();
        OPENSOLID_CORE_EXPORT bool has(const std::string& name) const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class FileOpenError : public Error
    {
    private:
        std::string _filename;
        std::string _mode;
        bool _is_open;
    public:
        OPENSOLID_CORE_EXPORT FileOpenError(
            const std::string& filename,
            const std::string& mode,
            bool is_open
        );
        
        OPENSOLID_CORE_EXPORT const char* what() const;
        OPENSOLID_CORE_EXPORT std::string filename() const;
        OPENSOLID_CORE_EXPORT std::string mode() const;
        OPENSOLID_CORE_EXPORT bool isOpen() const;
    };

    class FilePropertyError : public PropertyError
    {
    private:
        std::string _filename;
        std::string _mode;
        bool _is_open;
    public:
        OPENSOLID_CORE_EXPORT FilePropertyError(
            const std::string& filename,
            const std::string& mode,
            bool is_open,
            const std::string& name,
            const std::string& requested_type
        );

        OPENSOLID_CORE_EXPORT const char* what() const;
        OPENSOLID_CORE_EXPORT std::string filename() const;
        OPENSOLID_CORE_EXPORT std::string mode() const;
        OPENSOLID_CORE_EXPORT bool isOpen() const;
    };

    class FileSetPropertyError : public Error
    {
    private:
        std::string _filename;
        std::string _mode;
        bool _is_open;
    public:
        OPENSOLID_CORE_EXPORT FileSetPropertyError(
            const std::string& filename,
            const std::string& mode,
            bool is_open
        );
        
        OPENSOLID_CORE_EXPORT const char* what() const;
        OPENSOLID_CORE_EXPORT std::string filename() const;
        OPENSOLID_CORE_EXPORT std::string mode() const;
        OPENSOLID_CORE_EXPORT bool isOpen() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    void File::setProperty(const std::string& name, const Type& value) {
        Serialization<Type> serialization;
        setData(name, TypeName<Type>()(), serialization(value));
    }

    template <class Type>
    void File::getProperty(const std::string& name, Type& value) const {
        std::string type;
        std::string data;
        getData(name, type, data);
        std::string expected_type = TypeName<Type>()();
        if (type != expected_type) {
            throw FilePropertyError(filename(), mode(), isOpen(), name, expected_type);
        }
        Deserialization<Type> deserialization;
        value = deserialization(data);
    }
}

#endif
