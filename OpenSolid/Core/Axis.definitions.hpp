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

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>

#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Intersection.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>
#include <OpenSolid/Core/UnitVector.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct NumDimensions<Axis<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<Axis<iNumDimensions>, iNumResultDimensions>
    {
        typedef Axis<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<Axis<iNumDimensions>, iNumResultDimensions>
    {
        typedef Axis<iNumResultDimensions> Type;
    };

    template <>
    class Axis<2> :
        public Convertible<Axis<2>>,
        public Transformable<Axis<2>>
    {
    private:
        Point<2> _originPoint;
        UnitVector<2> _directionVector;
    public:
        Axis();

        Axis(const Point<2>& originPoint, const UnitVector<2>& directionVector);

        const Point<2>&
        originPoint() const;
        
        const UnitVector<2>&
        directionVector() const;

        const UnitVector<2>
        normalVector() const;

        const Axis<2>
        flipped() const;

        const Axis<2>
        normalAxis() const;

        const CoordinateSystem<2, 1>
        coordinateSystem() const;

        static const Axis<2>
        x();    

        static const Axis<2>
        y();
        
        bool
        contains(const Point<2>& point, double precision = 1e-12) const;
    };

    typedef Axis<2> Axis2d;

    template <>
    class Axis<3> :
        public Convertible<Axis<3>>,
        public Transformable<Axis<3>>
    {
    private:
        Point<3> _originPoint;
        UnitVector<3> _directionVector;
    public:
        Axis();

        Axis(const Point<3>& originPoint, const UnitVector<3>& directionVector);

        const Point<3>&
        originPoint() const;
        
        const UnitVector<3>&
        directionVector() const;

        const Axis<3>
        flipped() const;

        const Plane3d
        normalPlane() const;

        const CoordinateSystem<3, 1>
        coordinateSystem() const;

        const Intersection<Axis<3>, Plane3d>
        intersection(const Plane3d& plane, double precision = 1e-12) const;

        const Intersection<Axis<3>, Triangle<3>>
        intersection(const Triangle<3>& triangle, double precision = 1e-12) const;

        static const Axis<3>
        x();

        static const Axis<3>
        y();

        static const Axis<3>
        z();
        
        bool
        contains(const Point<3>& point, double precision = 1e-12) const;
    };

    typedef Axis<3> Axis3d;
    
    template <int iNumDimensions>
    struct ScalingFunction<Axis<iNumDimensions>>
    {
        const Axis<iNumDimensions>
        operator()(const Axis<iNumDimensions>& axis, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<Axis<iNumDimensions>>
    {
        const Axis<iNumDimensions>
        operator()(
            const Axis<iNumDimensions>& axis,
            const Vector<double, iNumDimensions>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<Axis<iNumDimensions>, iNumResultDimensions>
    {
        const Axis<iNumResultDimensions>
        operator()(
            const Axis<iNumDimensions>& axis,
            const Matrix<double, iNumResultDimensions, iNumDimensions>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<Axis<iNumDimensions>, iNumResultDimensions>
    {
        const Axis<iNumResultDimensions>
        operator()(
            const Axis<iNumDimensions>& axis,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };
}
