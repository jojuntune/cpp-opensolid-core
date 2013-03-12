/*************************************************************************************
 *                                                                                   *
 *  OpenSolid is a generic library for the representation and manipulation of        *
 *  geometric objects such as points, curves, surfaces, and volumes.                 *
 *                                                                                   *
 *  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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
 *************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Bounds.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Domain.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Set.hpp>
#include <OpenSolid/Core/Tetrahedron.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Triangle.hpp>

#include <OpenSolid/Core/Geometry/GeometryConstructors.hpp>
#include <OpenSolid/Core/Matrix/MatrixReturnValue.hpp>

#include <OpenSolid/Core/Geometry/declarations.hpp>

#include <boost/intrusive_ptr.hpp>

namespace opensolid
{
    class Geometry :
        public GeometryConstructors,
        public Convertible<Geometry>,
        public Transformable<Geometry>
    {
    private:
        Function _function;
        Domain _domain;
        VectorXI _bounds;
    public:
        OPENSOLID_CORE_EXPORT Geometry();
        
        OPENSOLID_CORE_EXPORT Geometry(const Function& function, const Domain& domain);

        OPENSOLID_CORE_EXPORT Geometry(const LineSegment2d& lineSegment);
        OPENSOLID_CORE_EXPORT Geometry(const Triangle2d& triangle);
        OPENSOLID_CORE_EXPORT Geometry(const LineSegment3d& lineSegment);
        OPENSOLID_CORE_EXPORT Geometry(const Triangle3d& triangle);
        OPENSOLID_CORE_EXPORT Geometry(const Tetrahedron3d& tetrahedron);
        
        const Function& function() const;
        const Domain& domain() const;
        const VectorXI& bounds() const;
        
        template <class TArgument>
        MatrixReturnValue<FunctionImplementation, TArgument> operator()(
            const TArgument& argument
        ) const;
        
        OPENSOLID_CORE_EXPORT int numParameters() const;
        OPENSOLID_CORE_EXPORT int numDimensions() const;
        OPENSOLID_CORE_EXPORT Set<Geometry> boundaries() const;
        
        OPENSOLID_CORE_EXPORT Geometry reversed() const;
    };

    OPENSOLID_CORE_EXPORT Geometry operator*(double multiplier, const Geometry& geometry);
    OPENSOLID_CORE_EXPORT Geometry operator*(const MatrixXd& matrix, const Geometry& geometry);
    OPENSOLID_CORE_EXPORT Geometry operator+(const Geometry& geometry, const VectorXd& vector);
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct Bounds<Geometry>
    {
        typedef VectorXI Type;

        OPENSOLID_CORE_EXPORT VectorXI operator()(const Geometry& geometry) const;
    };

    template <>
    struct Conversion<Geometry, double>
    {
        OPENSOLID_CORE_EXPORT double operator()(const Geometry& geometry) const;
    };
    
    template <>
    struct Conversion<Geometry, Vector2d>
    {
        OPENSOLID_CORE_EXPORT Vector2d operator()(const Geometry& geometry) const;
    };
    
    template <>
    struct Conversion<Geometry, Vector3d>
    {
        OPENSOLID_CORE_EXPORT Vector3d operator()(const Geometry& geometry) const;
    };
    
    template <>
    struct Conversion<Geometry, VectorXd>
    {
        OPENSOLID_CORE_EXPORT VectorXd operator()(const Geometry& geometry) const;
    };

    template <int iNumTransformedDimensions>
    struct Transformed<Geometry, iNumTransformedDimensions>
    {
        typedef Geometry Type;
    };
}

////////// Implementation //////////

#include <OpenSolid/Core/Domain.hpp>

namespace opensolid
{
    inline const Function&
    Geometry::function() const {
        return _function;
    }

    inline const Domain&
    Geometry::domain() const {
        return _domain;
    }

    inline const VectorXI&
    Geometry::bounds() const {
        return _bounds;
    }

    template <class TArgument>
    inline MatrixReturnValue<FunctionImplementation, TArgument>
    Geometry::operator()(const TArgument& argument) const {
        return function()(argument);
    }
}
