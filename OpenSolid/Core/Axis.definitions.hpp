/************************************************************************************
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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>

#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Intersection.declarations.hpp>
#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

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
        public Transformable<Axis<2>>
    {
    private:
        Point<2> _originPoint;
        Vector2d _directionVector;
    public:
        Axis();

        Axis(const Point<2>& originPoint, const Vector2d& directionVector);

        const Point<2>&
        originPoint() const;
        
        const Vector2d&
        directionVector() const;

        Axis<2>
        flipped() const;

        Axis<2>
        normalAxis() const;

        CoordinateSystem<2, 1>
        coordinateSystem() const;

        static Axis<2>
        X();

        static Axis<2>
        Y();
    };

    typedef Axis<2> Axis2d;

    template <>
    class Axis<3> :
        public Transformable<Axis<3>>
    {
    private:
        Point<3> _originPoint;
        Vector3d _directionVector;
    public:
        Axis();

        Axis(const Point<3>& originPoint, const Vector3d& directionVector);

        const Point<3>&
        originPoint() const;
        
        const Vector3d&
        directionVector() const;

        Axis<3>
        flipped() const;

        Plane3d
        normalPlane() const;

        CoordinateSystem<3, 1>
        coordinateSystem() const;

        Intersection<Axis<3>, Plane3d>
        intersection(const Plane3d& plane, double precision = 1e-12) const;

        static Axis<3>
        X();

        static Axis<3>
        Y();

        static Axis<3>
        Z();
    };

    typedef Axis<3> Axis3d;
    
    template <int iNumDimensions>
    struct ScalingFunction<Axis<iNumDimensions>>
    {
        Axis<iNumDimensions>
        operator()(const Axis<iNumDimensions>& axis, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<Axis<iNumDimensions>>
    {
        template <class TVector>
        Axis<iNumDimensions>
        operator()(const Axis<iNumDimensions>& axis, const EigenBase<TVector>& vector) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<Axis<iNumDimensions>, iNumResultDimensions>
    {
        template <class TMatrix>
        Axis<iNumResultDimensions>
        operator()(const Axis<iNumDimensions>& axis, const EigenBase<TMatrix>& matrix) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<Axis<iNumDimensions>, iNumResultDimensions>
    {
        Axis<iNumResultDimensions>
        operator()(
            const Axis<iNumDimensions>& axis,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };
}
