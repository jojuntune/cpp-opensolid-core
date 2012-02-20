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
#include <OpenSolid/Core/Common/Convertible.hpp>
#include <OpenSolid/Core/Common/Transformable.hpp>
#include <OpenSolid/Core/Scalar/Interval.hpp>
#include <OpenSolid/Core/Matrix/Matrix.hpp>
#include <OpenSolid/Core/Datum/Datum.hpp>
#include <OpenSolid/Core/Simplex/Simplex.hpp>
#include <OpenSolid/Core/Function/Function.hpp>
#include <OpenSolid/Core/Geometry/Geometry.hpp>
#include <OpenSolid/Core/Domain/Domain.hpp>

namespace OpenSolid
{
    class Object;

    template <>
    struct Conversion<Object, int>
    {
        OPENSOLID_CORE_EXPORT int operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, double>
    {
        OPENSOLID_CORE_EXPORT double operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, std::string>
    {
        OPENSOLID_CORE_EXPORT std::string operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, Interval>
    {
        OPENSOLID_CORE_EXPORT Interval operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, MatrixXd>
    {
        OPENSOLID_CORE_EXPORT MatrixXd operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, MatrixXI>
    {
        OPENSOLID_CORE_EXPORT MatrixXI operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, DatumXd>
    {
        OPENSOLID_CORE_EXPORT DatumXd operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, SimplexXd>
    {
        OPENSOLID_CORE_EXPORT SimplexXd operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, Function>
    {
        OPENSOLID_CORE_EXPORT Function operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, Geometry>
    {
        OPENSOLID_CORE_EXPORT Geometry operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, Domain>
    {
        OPENSOLID_CORE_EXPORT Domain operator()(const Object& object) const;
    };

    class Object : public Convertible<Object>, public Transformable<Object>
    {
    public:
        struct None
        {
            None() {}
        };
    private:
        boost::variant<
            None,
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
            Domain
        > _value;

        friend struct Conversion<Object, int>;
        friend struct Conversion<Object, double>;
        friend struct Conversion<Object, std::string>;
        friend struct Conversion<Object, Interval>;
        friend struct Conversion<Object, MatrixXd>;
        friend struct Conversion<Object, MatrixXI>;
        friend struct Conversion<Object, DatumXd>;
        friend struct Conversion<Object, SimplexXd>;
        friend struct Conversion<Object, Function>;
        friend struct Conversion<Object, Geometry>;
        friend struct Conversion<Object, Domain>;

        std::unordered_map<std::string, Object> _properties;
    public:
        OPENSOLID_CORE_EXPORT Object();
        OPENSOLID_CORE_EXPORT Object(int value);
        OPENSOLID_CORE_EXPORT Object(double value);
        OPENSOLID_CORE_EXPORT Object(const std::string& value);
        OPENSOLID_CORE_EXPORT Object(const Interval& value);

        template <class DerivedType>
        Object(const EigenBase<DerivedType>& value);

        OPENSOLID_CORE_EXPORT Object(const DatumXd& value);
        OPENSOLID_CORE_EXPORT Object(const SimplexXd& value);
        OPENSOLID_CORE_EXPORT Object(const Function& value);
        OPENSOLID_CORE_EXPORT Object(const Geometry& value);
        OPENSOLID_CORE_EXPORT Object(const Domain& value);

        OPENSOLID_CORE_EXPORT bool hasValue() const;
        OPENSOLID_CORE_EXPORT std::string valueType() const;
        OPENSOLID_CORE_EXPORT bool has(const std::string& name) const;
        OPENSOLID_CORE_EXPORT void set(const std::string& name, const Object& object);
        OPENSOLID_CORE_EXPORT Object get(const std::string& name) const;

        OPENSOLID_CORE_EXPORT Object transformed(
            const MatrixXd& matrix,
            const VectorXd& vector
        ) const;
    };

    template <>
    struct Conversion<Object, Vector2d>
    {
        OPENSOLID_CORE_EXPORT Vector2d operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, Vector3d>
    {
        OPENSOLID_CORE_EXPORT Vector3d operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, VectorXd>
    {
        OPENSOLID_CORE_EXPORT VectorXd operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, RowVector2d>
    {
        OPENSOLID_CORE_EXPORT RowVector2d operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, RowVector3d>
    {
        OPENSOLID_CORE_EXPORT RowVector3d operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, RowVectorXd>
    {
        OPENSOLID_CORE_EXPORT RowVectorXd operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, Matrix2d>
    {
        OPENSOLID_CORE_EXPORT Matrix2d operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, Matrix3d>
    {
        OPENSOLID_CORE_EXPORT Matrix3d operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, Vector2I>
    {
        OPENSOLID_CORE_EXPORT Vector2I operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, Vector3I>
    {
        OPENSOLID_CORE_EXPORT Vector3I operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, VectorXI>
    {
        OPENSOLID_CORE_EXPORT VectorXI operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, RowVector2I>
    {
        OPENSOLID_CORE_EXPORT RowVector2I operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, RowVector3I>
    {
        OPENSOLID_CORE_EXPORT RowVector3I operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, RowVectorXI>
    {
        OPENSOLID_CORE_EXPORT RowVectorXI operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, Matrix2I>
    {
        OPENSOLID_CORE_EXPORT Matrix2I operator()(const Object& object) const;
    };

    template <>
    struct Conversion<Object, Matrix3I>
    {
        OPENSOLID_CORE_EXPORT Matrix3I operator()(const Object& object) const;
    };

    class ObjectPropertyError : public Error
    {
    private:
        Object _object;
        std::string _name;
    public:
        OPENSOLID_CORE_EXPORT ObjectPropertyError(const Object& object, const std::string& name);

        OPENSOLID_CORE_EXPORT const char* what() const override;
        OPENSOLID_CORE_EXPORT Object object() const;
        OPENSOLID_CORE_EXPORT std::string name() const;
    };

    class ObjectConversionError : public Error
    {
    private:
        Object _object;
        std::string _requested_type;
    public:
        OPENSOLID_CORE_EXPORT ObjectConversionError(
            const Object& object,
            const std::string& requested_type
        );

        OPENSOLID_CORE_EXPORT const char* what() const override;
        OPENSOLID_CORE_EXPORT Object object() const;
        OPENSOLID_CORE_EXPORT std::string requestedType() const;
    };
}

////////// Implementation //////////

namespace OpenSolid
{
    template <class DerivedType>
    Object::Object(const EigenBase<DerivedType>& value) {
        _value = Matrix<typename DerivedType::Scalar, Dynamic, Dynamic>(value);
    }
}

#endif
