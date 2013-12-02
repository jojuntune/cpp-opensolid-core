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

#include <OpenSolid/Core/LineSegment.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    LineSegment<iNumDimensions>::LineSegment() {
    }

    template <int iNumDimensions>
    LineSegment<iNumDimensions>::LineSegment(
        const Point<iNumDimensions>& startPoint,
        const Point<iNumDimensions>& endPoint
    ) : _startPoint(startPoint),
        _endPoint(endPoint) {
    }

    template <int iNumDimensions>
    const Point<iNumDimensions>&
    LineSegment<iNumDimensions>::startPoint() const {
        return _startPoint;
    }

    template <int iNumDimensions>
    Point<iNumDimensions>&
    LineSegment<iNumDimensions>::startPoint() {
        return _startPoint;
    }

    template <int iNumDimensions>
    const Point<iNumDimensions>&
    LineSegment<iNumDimensions>::endPoint() const {
        return _endPoint;
    }

    template <int iNumDimensions>
    Point<iNumDimensions>&
    LineSegment<iNumDimensions>::endPoint() {
        return _endPoint;
    }

    template <int iNumDimensions>
    double
    LineSegment<iNumDimensions>::length() const {
        return (startPoint() - endPoint()).norm();
    }

    template <int iNumDimensions>
    double
    LineSegment<iNumDimensions>::squaredLength() const {
        return (startPoint() - endPoint()).squaredNorm();
    }

    template<int iNumDimensions>
    Matrix<double, iNumDimensions, 1>
    LineSegment<iNumDimensions>::vector() const {
        return endPoint() - startPoint();
    }

    template<int iNumDimensions>
    Matrix<double, iNumDimensions, 1>
    LineSegment<iNumDimensions>::normalVector() const {
        return (endPoint() - startPoint()).unitOrthogonal();
    }

    template <int iNumDimensions>
    CoordinateSystem<iNumDimensions, 1>
    LineSegment<iNumDimensions>::coordinateSystem() const {
        return CoordinateSystem<iNumDimensions, 1>(
            startPoint(),
            endPoint() - startPoint()
        );
    }

    template <int iNumDimensions>
    Axis<iNumDimensions>
    LineSegment<iNumDimensions>::axis() const {
        return Axis<iNumDimensions>(startPoint(), (endPoint() - startPoint()).normalized());
    }

    template <int iNumDimensions>
    Box<iNumDimensions>
    LineSegment<iNumDimensions>::bounds() const {
        return startPoint().hull(endPoint());
    }

    template <int iNumDimensions>
    bool
    LineSegment<iNumDimensions>::operator==(const LineSegment<iNumDimensions>& other) const {
        return startPoint() == other.startPoint() && endPoint() == other.endPoint();
    }

    template <int iNumDimensions>
    LineSegment<iNumDimensions>
    ScalingFunction<LineSegment<iNumDimensions>>::operator()(
        const LineSegment<iNumDimensions>& lineSegment,
        double scale
    ) const {
        return LineSegment<iNumDimensions>(
            detail::scaled(lineSegment.startPoint(), scale),
            detail::scaled(lineSegment.endPoint(), scale)
        );
    }

    template <int iNumDimensions> template <class TVector>
    LineSegment<iNumDimensions>
    TranslationFunction<LineSegment<iNumDimensions>>::operator()(
        const LineSegment<iNumDimensions>& lineSegment,
        const EigenBase<TVector>& vector
    ) const {
        return LineSegment<iNumDimensions>(
            detail::translated(lineSegment.startPoint(), vector.derived()),
            detail::translated(lineSegment.endPoint(), vector.derived())
        );
    }

    template <int iNumDimensions, int iNumResultDimensions> template <class TMatrix>
    LineSegment<iNumResultDimensions>
    TransformationFunction<LineSegment<iNumDimensions>, iNumResultDimensions>::operator()(
        const LineSegment<iNumDimensions>& lineSegment,
        const EigenBase<TMatrix>& matrix
    ) const {
        return LineSegment<iNumResultDimensions>(
            detail::transformed(lineSegment.startPoint(), matrix.derived()),
            detail::transformed(lineSegment.endPoint(), matrix.derived())
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    LineSegment<iNumResultDimensions>
    MorphingFunction<LineSegment<iNumDimensions>, iNumResultDimensions>::operator()(
        const LineSegment<iNumDimensions>& lineSegment,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return LineSegment<iNumResultDimensions>(
            detail::morphed(lineSegment.startPoint(), morphingExpression),
            detail::morphed(lineSegment.endPoint(), morphingExpression)
        );
    }

    template <int iNumDimensions>
    bool
    EqualityFunction<LineSegment<iNumDimensions>>::operator()(
        const LineSegment<iNumDimensions>& firstLineSegment,
        const LineSegment<iNumDimensions>& secondLineSegment,
        double precision
    ) const {
        return detail::equals(
            firstLineSegment.startPoint(),
            secondLineSegment.startPoint(),
            precision
        ) && detail::equals(
            firstLineSegment.endPoint(),
            secondLineSegment.endPoint(),
            precision
        );
    }
}
