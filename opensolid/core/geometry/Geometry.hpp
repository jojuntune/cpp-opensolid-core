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

#include <opensolid/Core/Common/Evaluation.hpp>
#include <opensolid/Core/Generic/TypeName.hpp>
#include <opensolid/Core/Generic/Bounds.hpp>
#include <opensolid/Core/Generic/Conversion.hpp>
#include <opensolid/Core/Generic/Transformable.hpp>
#include <opensolid/Core/Function/Function.hpp>
#include <opensolid/Core/Geometry/GeometryConstructors.hpp>
#include <opensolid/Core/Geometry/GeometryImplementation/GeometryImplementation.hpp>
#include <opensolid/Core/Matrix/Matrix.hpp>
#include <opensolid/Core/Set/Set.hpp>
#include <opensolid/Core/Simplex/Simplex.hpp>
#include <opensolid/Core/config.hpp>

#include <boost/intrusive_ptr.hpp>

namespace opensolid
{
    class Geometry :
        public GeometryConstructors,
        public Convertible<Geometry>,
        public Transformable<Geometry>
    {
    private:
        boost::intrusive_ptr<const GeometryImplementation> _implementation;
        const std::type_info* _type;
    public:
        OPENSOLID_CORE_EXPORT Geometry();
        OPENSOLID_CORE_EXPORT Geometry(const GeometryImplementation* implementation);

        OPENSOLID_CORE_EXPORT Geometry(const Function& function, const Domain& domain);
        OPENSOLID_CORE_EXPORT Geometry(int value);
        OPENSOLID_CORE_EXPORT Geometry(double value);
        OPENSOLID_CORE_EXPORT Geometry(const VectorXd& vector);
        OPENSOLID_CORE_EXPORT Geometry(const SimplexXd& simplex);

        template <class DerivedType>
        Geometry(const EigenBase<DerivedType>& vector);

        template <int dimensions_, int size_>
        Geometry(const Simplex<dimensions_, size_>& simplex);

        OPENSOLID_CORE_EXPORT const GeometryImplementation* implementation() const;
        
        OPENSOLID_CORE_EXPORT Function function() const;
        OPENSOLID_CORE_EXPORT Domain domain() const;
        
        template <class ArgumentType>
        Evaluation<Geometry, ArgumentType> operator()(const ArgumentType& argument) const;

        OPENSOLID_CORE_EXPORT void evaluate(const MapXcd& parameter_values, MapXd& results) const;
        OPENSOLID_CORE_EXPORT void evaluate(const MapXcI& parameter_bounds, MapXI& results) const;
        
        OPENSOLID_CORE_EXPORT int parameters() const;
        OPENSOLID_CORE_EXPORT int dimensions() const;
        OPENSOLID_CORE_EXPORT bool isConstant() const;
        OPENSOLID_CORE_EXPORT VectorXI bounds() const;
        OPENSOLID_CORE_EXPORT Set<Geometry> boundaries() const;
        OPENSOLID_CORE_EXPORT Geometry transformed(const MatrixXd& matrix, const VectorXd& vector) const;
        OPENSOLID_CORE_EXPORT Geometry reversed() const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct Bounds<Geometry>
    {
        typedef VectorXI Type;

        OPENSOLID_CORE_EXPORT VectorXI operator()(const Geometry& argument) const;
    };

    template <>
    struct Conversion<Geometry, double>
    {
        OPENSOLID_CORE_EXPORT double operator()(const Geometry& argument) const;
    };
    
    template <>
    struct Conversion<Geometry, Vector2d>
    {
        OPENSOLID_CORE_EXPORT Vector2d operator()(const Geometry& argument) const;
    };
    
    template <>
    struct Conversion<Geometry, Vector3d>
    {
        OPENSOLID_CORE_EXPORT Vector3d operator()(const Geometry& argument) const;
    };
    
    template <>
    struct Conversion<Geometry, VectorXd>
    {
        OPENSOLID_CORE_EXPORT VectorXd operator()(const Geometry& argument) const;
    };

    template <>
    struct TypeName<Geometry>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };
}

////////// Implementation //////////

#include <opensolid/Core/Domain/Domain.hpp>

namespace opensolid
{
    template <class DerivedType>
    Geometry::Geometry(const EigenBase<DerivedType>& vector) {
        *this = Geometry(VectorXd(vector));
    }

    template <int dimensions_, int size_>
    Geometry::Geometry(const Simplex<dimensions_, size_>& simplex) {
        *this = Geometry(SimplexXd(simplex));
    }

    template <class ArgumentType>
    inline Evaluation<Geometry, ArgumentType> Geometry::operator()(
        const ArgumentType& argument
    ) const {return Evaluation<Geometry, ArgumentType>(*this, argument);}
}
