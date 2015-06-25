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

#include <OpenSolid/Core/ParametricCurve.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricCurve/ParametricCurveBase.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/WindingDirection.definitions.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<ParametricCurve<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<ParametricCurve<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <>
    class ParametricCurve<2> :
        public detail::ParametricCurveBase<2>
    {
    private:
        ParametricExpression<Point<2>, double> _expression;
        Interval _domain;
        Box<2> _bounds;
    public:
        ParametricCurve();

        ParametricCurve(const ParametricCurve<2>& other);

        ParametricCurve(ParametricCurve<2>&& other);

        ParametricCurve(const ParametricExpression<Point<2>, double>& expression, Interval domain);

        OPENSOLID_CORE_EXPORT
        ParametricCurve<3>
        toGlobalFrom(const Plane3d& plane) const;

        using detail::ParametricCurveBase<2>::toGlobalFrom;

        ///// Arcs /////
        //
        // Argument order:
        //   centerPoint
        //   radius
        //   windingDirection
        //   startPoint
        //   startAngle
        //   innerPoint
        //   endAngle
        //   endPoint

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        arc(
            const Point<2>& centerPoint,
            double radius,
            double startAngle,
            double endAngle
        );
        
        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        arc(
            const Point<2>& centerPoint,
            WindingDirection windingDirection,
            const Point<2>& startPoint,
            const Point<2>& endPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        arc(
            double radius,
            WindingDirection windingDirection,
            const Point<2>& startPoint,
            const Point<2>& endPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        arc(
            const Point<2>& startPoint,
            const Point<2>& innerPoint,
            const Point<2>& endPoint
        );

        ///// Circles /////
        //
        // Argument order:
        //   centerPoint
        //   radius
        //   windingDirection
        //   startAngle
        //   startPoint
        //   secondPoint
        //   thirdPoint

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        circle(const Point<2>& centerPoint, double radius);

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        circle(
            const Point<2>& centerPoint,
            double radius,
            WindingDirection windingDirection,
            double startAngle
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        circle(
            const Point<2>& centerPoint,
            WindingDirection windingDirection,
            const Point<2>& startPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        circle(
            double radius,
            WindingDirection windingDirection,
            const Point<2>& startPoint,
            const Point<2>& secondPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        circle(
            const Point<2>& startPoint,
            const Point<2>& secondPoint,
            const Point<2>& thirdPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        circumcircle(const Triangle<2>& triangle);
    };

    typedef ParametricCurve<2> ParametricCurve2d;

    template <>
    class ParametricCurve<3> :
        public detail::ParametricCurveBase<3>
    {
    private:
        ParametricExpression<Point<3>, double> _expression;
        Interval _domain;
        Box<3> _bounds;
    public:
        ParametricCurve();

        ParametricCurve(const ParametricCurve<3>& other);

        ParametricCurve(ParametricCurve<3>&& other);

        ParametricCurve(
            const ParametricExpression<Point<3>, double>& expression,
            Interval domain
        );

        OPENSOLID_CORE_EXPORT
        ParametricCurve<2>
        toLocalIn(const Plane3d& plane) const;

        using detail::ParametricCurveBase<3>::toLocalIn;

        OPENSOLID_CORE_EXPORT
        ParametricCurve<3>
        projectedOnto(const Plane3d& plane) const;

        ///// Arcs /////
        //
        // Argument order:
        //   centerPoint
        //   normalVector
        //   plane
        //   axis
        //   radius
        //   startPoint
        //   innerPoint
        //   endPoint

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        arc(
            const Point<3>& centerPoint,
            const UnitVector<3>& normalVector,
            const Point<3>& startPoint,
            const Point<3>& endPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        arc(
            const Plane3d& plane,
            const Point<3>& startPoint,
            const Point<3>& endPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        arc(
            const Axis<3>& axis,
            const Point<3>& startPoint,
            const Point<3>& endPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        arc(
            const UnitVector<3>& normalVector,
            double radius,
            const Point<3>& startPoint,
            const Point<3>& endPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        arc(
            const Point<3>& startPoint,
            const Point<3>& innerPoint,
            const Point<3>& endPoint
        );

        ///// Circles /////
        //
        // Argument order:
        //   centerPoint
        //   normalVector
        //   plane
        //   axis
        //   radius
        //   startPoint
        //   innerPoint
        //   endPoint

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        circle(const Point<3>& centerPoint, const UnitVector<3>& normalVector, double radius);

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        circle(
            const Point<3>& centerPoint,
            const UnitVector<3>& normalVector,
            const Point<3>& startPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        circle(
            const Plane3d& plane,
            const Point<3>& startPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        circle(
            const Axis<3>& axis,
            const Point<3>& startPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        circle(
            double radius,
            const UnitVector<3>& normalVector,
            const Point<3>& startPoint,
            const Point<3>& secondPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        circle(
            const Point<3>& startPoint,
            const Point<3>& secondPoint,
            const Point<3>& thirdPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        circumcircle(const Triangle<3>& triangle);

        ///// Helices /////
        //
        // Argument order:
        //   startCenterPoint
        //   endCenterPoint
        //   axis
        //   axisDirection
        //   radius
        //   windingDirection
        //   startPoint
        //   endPoint
        //   pitch (if <= 0: determine from numTurns/length)
        //   numTurns (if <= 0: determine from pitch/length)
        //   length (if <= 0: determine from pitch/numTurns)

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        helix(
            const Point<3>& startCenterPoint,
            const Point<3>& endCenterPoint,
            double radius,
            WindingDirection windingDirection,
            double pitch, // if <= 0: determine from numTurns
            double numTurns // if <= 0: determine from pitch
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        helix(
            const Point<3>& startCenterPoint,
            const Point<3>& endCenterPoint,
            WindingDirection windingDirection,
            const Point<3>& startPoint,
            double pitch, // if <= 0: determine from numTurns
            double numTurns // if <= 0: determine from pitch
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        helix(
            const Point<3>& startCenterPoint,
            const UnitVector<3>& axisDirection,
            double radius,
            WindingDirection windingDirection,
            double pitch, // if <= 0: determine from numTurns/length
            double numTurns, // if <= 0: determine from pitch/length
            double length // if <= 0: determine from pitch/numTurns
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        helix(
            const Point<3>& startCenterPoint,
            const UnitVector<3>& axisDirection,
            WindingDirection windingDirection,
            const Point<3>& startPoint,
            double pitch, // if <= 0: determine from numTurns/length
            double numTurns, // if <= 0: determine from pitch/length
            double length // if <= 0: determine from pitch/numTurns
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        helix(
            const Axis<3>& axis,
            WindingDirection windingDirection,
            const Point<3>& startPoint,
            double pitch, // if <= 0: determine from numTurns/length
            double numTurns, // if <= 0: determine from pitch/length
            double length // if <= 0: determine from pitch/numTurns
        );
    };

    typedef ParametricCurve<3> ParametricCurve3d;
}
