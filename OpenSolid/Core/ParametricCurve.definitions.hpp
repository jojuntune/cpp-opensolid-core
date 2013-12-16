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

#include <OpenSolid/Core/ParametricCurve.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Interval.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/ParametricCurve/ParametricCurveBase.definitions.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>

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

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<ParametricCurve<iNumDimensions>, iNumResultDimensions>
    {
        typedef ParametricCurve<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<ParametricCurve<iNumDimensions>, iNumResultDimensions>
    {
        typedef ParametricCurve<iNumResultDimensions> Type;
    };

    template <>
    class ParametricCurve<2> :
        public detail::ParametricCurveBase<2>,
        public Transformable<ParametricCurve<2>>
    {
    private:
        ParametricExpression<2, 1> _expression;
        Interval _domain;
        Box<2> _bounds;
    public:
        enum WindingDirection
        {
            COUNTERCLOCKWISE,
            CLOCKWISE
        };

        ParametricCurve();

        ParametricCurve(const ParametricCurve<2>& other);

        ParametricCurve(ParametricCurve<2>&& other);

        ParametricCurve(
            const ParametricExpression<2, 1>& expression,
            Interval domain
        );

        ///// Arcs /////
        //
        // Argument order:
        //   centerPoint
        //   radius
        //   direction
        //   startPoint
        //   startAngle
        //   innerPoint
        //   endAngle
        //   endPoint

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        Arc(
            const Point<2>& centerPoint,
            double radius,
            double startAngle,
            double endAngle
        );
        
        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        Arc(
            const Point<2>& centerPoint,
            WindingDirection direction,
            const Point<2>& startPoint,
            const Point<2>& endPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        Arc(
            double radius,
            WindingDirection direction,
            const Point<2>& startPoint,
            const Point<2>& endPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        Arc(
            const Point<2>& startPoint,
            const Point<2>& innerPoint,
            const Point<2>& endPoint
        );

        ///// Circles /////
        //
        // Argument order:
        //   centerPoint
        //   radius
        //   direction
        //   startAngle
        //   startPoint
        //   secondPoint
        //   thirdPoint

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        Circle(
            const Point<2>& centerPoint,
            double radius
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        Circle(
            const Point<2>& centerPoint,
            double radius,
            WindingDirection direction,
            double startAngle
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        Circle(
            const Point<2>& centerPoint,
            WindingDirection direction,
            const Point<2>& startPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        Circle(
            double radius,
            WindingDirection direction,
            const Point<2>& startPoint,
            const Point<2>& secondPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        Circle(
            const Point<2>& startPoint,
            const Point<2>& secondPoint,
            const Point<2>& thirdPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<2>
        Circumcircle(
            const Triangle<2>& triangle
        );
    };

    typedef ParametricCurve<2> ParametricCurve2d;

    template <>
    class ParametricCurve<3> :
        public detail::ParametricCurveBase<3>,
        public Transformable<ParametricCurve<3>>
    {
    private:
        ParametricExpression<3, 1> _expression;
        Interval _domain;
        Box<3> _bounds;
    public:
        enum WindingDirection
        {
            COUNTERCLOCKWISE,
            CLOCKWISE
        };
        
        ParametricCurve();

        ParametricCurve(const ParametricCurve<3>& other);

        ParametricCurve(ParametricCurve<3>&& other);

        ParametricCurve(
            const ParametricExpression<3, 1>& expression,
            Interval domain
        );

        ///// Arcs /////
        //
        // Argument order:
        //   centerPoint
        //   axis
        //   axisDirection
        //   radius
        //   startPoint
        //   innerPoint
        //   endPoint

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Arc(
            const Point<3>& centerPoint,
            const Vector3d& axisDirection,
            const Point<3>& startPoint,
            const Point<3>& endPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Arc(
            const Axis<3>& axis,
            const Point<3>& startPoint,
            const Point<3>& endPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Arc(
            const Vector3d& axisDirection,
            double radius,
            const Point<3>& startPoint,
            const Point<3>& endPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Arc(
            const Point<3>& startPoint,
            const Point<3>& innerPoint,
            const Point<3>& endPoint
        );

        ///// Circles /////
        //
        // Argument order:
        //   centerPoint
        //   axis
        //   axisDirection
        //   radius
        //   startPoint
        //   innerPoint
        //   endPoint

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Circle(
            const Point<3>& centerPoint,
            const Vector3d& axisDirection,
            double radius
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Circle(
            const Point<3>& centerPoint,
            const Vector3d& axisDirection,
            const Point<3>& startPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Circle(
            const Axis<3>& axis,
            const Point<3>& startPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Circle(
            const Vector3d& axisDirection,
            double radius,
            const Point<3>& startPoint,
            const Point<3>& secondPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Circle(
            const Point<3>& startPoint,
            const Point<3>& secondPoint,
            const Point<3>& thirdPoint
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Circumcircle(
            const Triangle<3>& triangle
        );

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
        Helix(
            const Point<3>& startCenterPoint,
            const Point<3>& endCenterPoint,
            double radius,
            WindingDirection direction,
            double pitch, // if <= 0: determine from numTurns
            double numTurns // if <= 0: determine from pitch
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Helix(
            const Point<3>& startCenterPoint,
            const Point<3>& endCenterPoint,
            WindingDirection direction,
            const Point<3>& startPoint,
            double pitch, // if <= 0: determine from numTurns
            double numTurns // if <= 0: determine from pitch
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Helix(
            const Point<3>& startCenterPoint,
            const Vector3d& axisDirection,
            double radius,
            WindingDirection direction,
            double pitch, // if <= 0: determine from numTurns/length
            double numTurns, // if <= 0: determine from pitch/length
            double length // if <= 0: determine from pitch/numTurns
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Helix(
            const Point<3>& startCenterPoint,
            const Vector3d& axisDirection,
            WindingDirection direction,
            const Point<3>& startPoint,
            double pitch, // if <= 0: determine from numTurns/length
            double numTurns, // if <= 0: determine from pitch/length
            double length // if <= 0: determine from pitch/numTurns
        );

        OPENSOLID_CORE_EXPORT
        static ParametricCurve<3>
        Helix(
            const Axis<3>& axis,
            WindingDirection direction,
            const Point<3>& startPoint,
            double pitch, // if <= 0: determine from numTurns/length
            double numTurns, // if <= 0: determine from pitch/length
            double length // if <= 0: determine from pitch/numTurns
        );
    };
    typedef ParametricCurve<3> ParametricCurve3d;

    template <int iNumDimensions>
    struct ScalingFunction<ParametricCurve<iNumDimensions>>
    {
        ParametricCurve<iNumDimensions>
        operator()(const ParametricCurve<iNumDimensions>& curve, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<ParametricCurve<iNumDimensions>>
    {
        template <class TVector>
        ParametricCurve<iNumDimensions>
        operator()(
            const ParametricCurve<iNumDimensions>& curve,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<ParametricCurve<iNumDimensions>, iNumResultDimensions>
    {
        template <class TMatrix>
        ParametricCurve<iNumResultDimensions>
        operator()(
            const ParametricCurve<iNumDimensions>& curve,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<ParametricCurve<iNumDimensions>, iNumResultDimensions>
    {
        ParametricCurve<iNumResultDimensions>
        operator()(
            const ParametricCurve<iNumDimensions>& curve,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };
}
