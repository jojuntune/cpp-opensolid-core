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

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Bounds.hpp>
#include <OpenSolid/Core/Evaluation.hpp>
#include <OpenSolid/Core/Geometry/GeometryConstructors.hpp>
#include <OpenSolid/Core/Geometry/GeometryImplementation.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Set.hpp>
#include <OpenSolid/Core/Tetrahedron.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Utils/Convertible.hpp>
 
#include <OpenSolid/Core/Function/declarations.hpp>
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
        boost::intrusive_ptr<const GeometryImplementation> _implementation;
        const std::type_info* _type;
    public:
        OPENSOLID_CORE_EXPORT Geometry();
        OPENSOLID_CORE_EXPORT Geometry(const GeometryImplementation* implementation);

        OPENSOLID_CORE_EXPORT Geometry(const Function& function, const Domain& domain);
        OPENSOLID_CORE_EXPORT Geometry(int value);
        OPENSOLID_CORE_EXPORT Geometry(double value);
        OPENSOLID_CORE_EXPORT Geometry(const VectorXd& vector);

        template <class TVector>
        Geometry(const EigenBase<TVector>& vector);

        OPENSOLID_CORE_EXPORT Geometry(const LineSegment2d& lineSegment);
        OPENSOLID_CORE_EXPORT Geometry(const Triangle2d& triangle);
        OPENSOLID_CORE_EXPORT Geometry(const LineSegment3d& lineSegment);
        OPENSOLID_CORE_EXPORT Geometry(const Triangle3d& triangle);
        OPENSOLID_CORE_EXPORT Geometry(const Tetrahedron3d& tetrahedron);

        OPENSOLID_CORE_EXPORT const GeometryImplementation* implementation() const;
        
        OPENSOLID_CORE_EXPORT Function function() const;
        OPENSOLID_CORE_EXPORT Domain domain() const;
        
        template <class TArgument>
        Evaluation<Geometry, TArgument> operator()(const TArgument& argument) const;

        OPENSOLID_CORE_EXPORT void evaluate(const MapXcd& parameterValues, MapXd& results) const;
        OPENSOLID_CORE_EXPORT void evaluate(const MapXcI& parameterBounds, MapXI& results) const;
        
        OPENSOLID_CORE_EXPORT int numParameters() const;
        OPENSOLID_CORE_EXPORT int numDimensions() const;
        OPENSOLID_CORE_EXPORT bool isConstant() const;
        OPENSOLID_CORE_EXPORT VectorXI bounds() const;
        OPENSOLID_CORE_EXPORT Set<Geometry> boundaries() const;
        
        OPENSOLID_CORE_EXPORT Geometry transformed(
            const MatrixXd& transformMatrix,
            const VectorXd& transformVector
        ) const;
        
        OPENSOLID_CORE_EXPORT Geometry reversed() const;
    };

    OPENSOLID_CORE_EXPORT Geometry operator*(double multiplier, const Geometry& geometry);

    template <class TMatrix>
    Geometry operator*(const EigenBase<TMatrix>& transformationMatrix, const Geometry& geometry);

    template <class TVector>
    Geometry operator+(const Geometry& geometry, const EigenBase<TVector>& vector);
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
    template <class TVector>
    Geometry::Geometry(const EigenBase<TVector>& vector) {
        *this = Geometry(VectorXd(vector));
    }

    template <class TArgument>
    inline Evaluation<Geometry, TArgument> Geometry::operator()(const TArgument& argument) const {
        return Evaluation<Geometry, TArgument>(*this, argument);
    }

    template <class TMatrix>
    Geometry operator*(const EigenBase<TMatrix>& transformationMatrix, const Geometry& geometry) {
        return geometry.transformed(
            transformationMatrix.derived(),
            VectorXd::Zero(transformationMatrix.rows())
        );
    }

    template <class TVector>
    Geometry operator+(const Geometry& geometry, const EigenBase<TVector>& vector) {
        return geometry.transformed(
            MatrixXd::Identity(geometry.numDimensions(), geometry.numDimensions()),
            vector.derived()
        );
    }
}
