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

#ifndef OPENSOLID__OBJECT_HPP
#define OPENSOLID__OBJECT_HPP

#include <string>
#include <unordered_map>

#include <boost/variant.hpp>

#include <OpenSolid/Core/config.hpp>
#include <OpenSolid/Core/Common/Error.hpp>
#include <OpenSolid/Core/Common/Conversion.hpp>
#include <OpenSolid/Core/Common/PropertyMap.hpp>
#include <OpenSolid/Core/Common/Serialization.hpp>
#include <OpenSolid/Core/Common/Deserialization.hpp>
#include <OpenSolid/Core/Common/Transformable.hpp>
#include <OpenSolid/Core/Scalar/Interval.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Core/Datum/Datum.hpp>
#include <OpenSolid/Core/Simplex/Simplex.hpp>
#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>
#include <OpenSolid/Core/Domain/Domain.hpp>

namespace opensolid
{
    template <>
    struct Serialization<Object>;

    template <>
    struct Deserialization<Object>;

    class Object :
        public PropertyMap<Object>,
        public Transformable<Object>,
        public Convertible<Object>
    {
    private:
        typedef boost::variant<
            bool,
            int,
            double,
            std::string,
            Interval,
            MatrixXd,
            MatrixXI,
            DatumXd,
            SimplexXd,
            Function,
            Geometry,
            Domain,
            Object
        > Variant;

        std::unordered_map<std::string, Variant> _properties;

        template <class Type>
        void setProperty(const std::string& name, const Type& value);

        template <class Type>
        void getProperty(const std::string& name, Type& value) const;

        OPENSOLID_CORE_EXPORT void throwPropertyError(
            const std::string& name,
            const std::string& requested_type
        ) const;

        friend class PropertyMap<Object>;
        friend struct GetObjectProperty;
        friend struct Serialization<Object>;
        friend struct Deserialization<Object>;
    public:
        OPENSOLID_CORE_EXPORT Object();

        OPENSOLID_CORE_EXPORT bool has(const std::string& name) const;

        OPENSOLID_CORE_EXPORT std::string type(const std::string& name) const;

        OPENSOLID_CORE_EXPORT Object transformed(
            const MatrixXd& matrix,
            const VectorXd& vector
        ) const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct TypeName<Object>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };

    template <>
    struct Serialization<Object>
    {
        OPENSOLID_CORE_EXPORT std::string operator()(const Object& argument) const;
    };

    template <>
    struct Deserialization<Object>
    {
        OPENSOLID_CORE_EXPORT Object operator()(const std::string& argument) const;
    };
}

////////// Errors //////////

namespace opensolid
{
    class ObjectPropertyError : public PropertyError
    {
    private:
        Object _object;
    public:
        OPENSOLID_CORE_EXPORT ObjectPropertyError(
            const Object& object,
            const std::string& name,
            const std::string& requested_type
        );
        
        ~ObjectPropertyError() throw () {}

        OPENSOLID_CORE_EXPORT const char* what() const throw() override;
        OPENSOLID_CORE_EXPORT Object object() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class Type>
    void Object::setProperty(const std::string& name, const Type& value) {
        _properties[name] = value;
    }

    template <class Type>
    void Object::getProperty(const std::string& name, Type& value) const {
        if (const Type* result = boost::get<Type>(&_properties.at(name))) {
            value = *result;
        } else {
            throw ObjectPropertyError(*this, name, TypeName<Type>()());
        }
    }
}

#endif
