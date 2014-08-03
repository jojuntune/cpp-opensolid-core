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

#include <OpenSolid/Core/LineSegment.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/BoundsFunction.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/CoordinateSystem.hpp>
#include <OpenSolid/Core/EqualityFunction.hpp>
#include <OpenSolid/Core/LineSegmentPlaneIntersection3d.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    inline
    LineSegment<iNumDimensions>::LineSegment() {
    }

    template <int iNumDimensions>
    inline
    LineSegment<iNumDimensions>::LineSegment(
        const Point<iNumDimensions>& startVertex,
        const Point<iNumDimensions>& endVertex
    ) {
        _vertices[0] = startVertex;
        _vertices[1] = endVertex;
    }

    template <int iNumDimensions>
    inline
    const Point<iNumDimensions>&
    LineSegment<iNumDimensions>::startVertex() const {
        return _vertices[0];
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>&
    LineSegment<iNumDimensions>::startVertex() {
        return _vertices[0];
    }

    template <int iNumDimensions>
    inline
    const Point<iNumDimensions>&
    LineSegment<iNumDimensions>::endVertex() const {
        return _vertices[1];
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>&
    LineSegment<iNumDimensions>::endVertex() {
        return _vertices[1];
    }

    template <int iNumDimensions>
    inline
    const Point<iNumDimensions>&
    LineSegment<iNumDimensions>::vertex(int index) const {
        assert(index == 0 || index == 1);
        return _vertices[index];
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>&
    LineSegment<iNumDimensions>::vertex(int index) {
        assert(index == 0 || index == 1);
        return _vertices[index];
    }

    template <int iNumDimensions>
    inline
    detail::SimplexVertices<LineSegment<iNumDimensions>, 2>
    LineSegment<iNumDimensions>::vertices() const {
        return detail::SimplexVertices<LineSegment<iNumDimensions>, 2>(*this);
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>
    LineSegment<iNumDimensions>::centroid() const {
        return startVertex() + 0.5 * vector();
    }

    template <int iNumDimensions>
    inline
    double
    LineSegment<iNumDimensions>::length() const {
        return vector().norm();
    }

    template <int iNumDimensions>
    inline
    double
    LineSegment<iNumDimensions>::squaredLength() const {
        return vector().squaredNorm();
    }

    template<int iNumDimensions>
    inline
    Vector<double, iNumDimensions>
    LineSegment<iNumDimensions>::vector() const {
        return endVertex() - startVertex();
    }

    template<int iNumDimensions>
    inline
    UnitVector<iNumDimensions>
    LineSegment<iNumDimensions>::normalVector() const {
        return vector().unitOrthogonal();
    }

    template <int iNumDimensions>
    inline
    CoordinateSystem<iNumDimensions, 1>
    LineSegment<iNumDimensions>::coordinateSystem() const {
        return CoordinateSystem<iNumDimensions, 1>(startVertex(), vector());
    }

    template <int iNumDimensions>
    inline
    Axis<iNumDimensions>
    LineSegment<iNumDimensions>::axis() const {
        return Axis<iNumDimensions>(startVertex(), vector().normalized());
    }

    template <int iNumDimensions>
    inline
    Box<iNumDimensions>
    LineSegment<iNumDimensions>::bounds() const {
        return startVertex().hull(endVertex());
    }

    template <int iNumDimensions>
    inline
    bool
    LineSegment<iNumDimensions>::operator==(const LineSegment<iNumDimensions>& other) const {
        return startVertex() == other.startVertex() && endVertex() == other.endVertex();
    }

    template <int iNumDimensions>
    inline
    Intersection<LineSegment3d, Plane3d>
    LineSegment<iNumDimensions>::intersection(const Plane3d& plane, double precision) const {
        return Intersection<LineSegment3d, Plane3d>(*this, plane, precision);
    }
    
    template <int iNumDimensions>
    inline
    bool
    LineSegment<iNumDimensions>::contains(const Point2d& point, double precision) const {
        Vector2d parallelVector = vector();
        Vector2d perpendicularVector(parallelVector.x(), -parallelVector.y());
        double squaredLength = parallelVector.squaredNorm();
        Vector2d startVector = point - startVertex();
        Zero zero(precision * precision * squaredLength);

        // Check whether the point is on the axis defined by the segment
        double perpendicularMetric = startVector.dot(perpendicularVector);
        if (perpendicularMetric * perpendicularMetric > zero) {
            return false;
        }

        // Check whether point is located within the segment
        Point1d localCoordinates = point / coordinateSystem();
        if (!Interval::unit().contains(localCoordinates.value())) {
            return false;
        }

        // Passed all checks
        return true;
    }
    
    template <int iNumDimensions>
    inline
    bool
    LineSegment<iNumDimensions>::contains(const Point3d& point, double precision) const {
        Vector3d parallelVector = vector();
        double squaredLength = parallelVector.squaredNorm();
        Vector3d startVector = point - startVertex();
        Zero zero(precision * precision * squaredLength);

        // Check whether the point is on the axis defined by the segment
        double perpendicularMetric = startVector.cross(parallelVector).squaredNorm();
        if (perpendicularMetric > zero) {
            return false;
        }

        // Check whether point is located within the segment
        Point1d localCoordinates = point / coordinateSystem();
        if (!Interval::unit().contains(localCoordinates.value())) {
            return false;
        }

        // Passed all checks
        return true;
    }

    template <int iNumDimensions>
    inline
    bool
    EqualityFunction<LineSegment<iNumDimensions>>::operator()(
        const LineSegment<iNumDimensions>& firstLineSegment,
        const LineSegment<iNumDimensions>& secondLineSegment,
        double precision
    ) const {
        return equalityFunction(
            firstLineSegment.startVertex(),
            secondLineSegment.startVertex(),
            precision
        ) && equalityFunction(
            firstLineSegment.endVertex(),
            secondLineSegment.endVertex(),
            precision
        );
    }

    template <int iNumDimensions>
    inline
    LineSegment<iNumDimensions>
    ScalingFunction<LineSegment<iNumDimensions>>::operator()(
        const LineSegment<iNumDimensions>& lineSegment,
        const Point<iNumDimensions>& originPoint,
        double scale
    ) const {
        return LineSegment<iNumDimensions>(
            scaled(lineSegment.startVertex(), originPoint, scale),
            scaled(lineSegment.endVertex(), originPoint, scale)
        );
    }

    template <int iNumDimensions>
    inline
    LineSegment<iNumDimensions>
    TranslationFunction<LineSegment<iNumDimensions>>::operator()(
        const LineSegment<iNumDimensions>& lineSegment,
        const Vector<double, iNumDimensions>& vector
    ) const {
        return LineSegment<iNumDimensions>(
            translated(lineSegment.startVertex(), vector),
            translated(lineSegment.endVertex(), vector)
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    inline
    LineSegment<iNumResultDimensions>
    TransformationFunction<LineSegment<iNumDimensions>, iNumResultDimensions>::operator()(
        const LineSegment<iNumDimensions>& lineSegment,
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumResultDimensions, iNumDimensions>& transformationMatrix,
        const Point<iNumResultDimensions>& destinationPoint
    ) const {
        return LineSegment<iNumResultDimensions>(
            transformed(
                lineSegment.startVertex(),
                originPoint,
                transformationMatrix,
                destinationPoint
            ),
            transformed(
                lineSegment.endVertex(),
                originPoint,
                transformationMatrix,
                destinationPoint
            )
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    inline
    LineSegment<iNumResultDimensions>
    MorphingFunction<LineSegment<iNumDimensions>, iNumResultDimensions>::operator()(
        const LineSegment<iNumDimensions>& lineSegment,
        const ParametricExpression<
            Point<iNumResultDimensions>,
            Point<iNumDimensions>
        >& morphingExpression
    ) const {
        return LineSegment<iNumResultDimensions>(
            morphingExpression.evaluate(lineSegment.startVertex()),
            morphingExpression.evaluate(lineSegment.endVertex())
        );
    }
}
