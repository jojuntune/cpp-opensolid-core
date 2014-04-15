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

#include <OpenSolid/Core/Point.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Interval.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Position/PointBase.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Triangle.hpp>

namespace opensolid
{
    inline
    Point1d::Point() {
    }

    inline
    Point1d::Point(double value) :
        detail::PointBase<1>(value) {
    }

    inline
    Point1d::Point(const Vector1d& vector) :
        detail::PointBase<1>(vector.components()) {
    }

    inline
    Point1d::Point(const Matrix1x1& matrix) :
        detail::PointBase<1>(matrix) {
    }

    inline
    Point1d::Point(const double* sourcePtr) :
        detail::PointBase<1>(sourcePtr) {
    }

    inline
    Point2d::Point() {
    }

    inline
    Point2d::Point(double x, double y) :
        detail::PointBase<2>(x, y) {
    }

    inline
    Point2d::Point(const Vector2d& vector) :
        detail::PointBase<2>(vector.components()) {
    }

    inline
    Point2d::Point(const ColMatrix2x1& components) :
        detail::PointBase<2>(components) {
    }

    inline
    Point2d::Point(const double* sourcePtr) :
        detail::PointBase<2>(sourcePtr) {
    }

    inline
    double
    Point2d::distanceTo(const Axis2d& axis) const {
        return (*this - axis.originPoint()).dot(axis.normalVector());
    }

    inline
    bool
    Point2d::isOn(const Axis2d& axis, double precision) const {
        return distanceTo(axis) == Zero(precision);
    }

    inline
    bool
    Point2d::isOn(const LineSegment2d& lineSegment, double precision) const {
        Vector2d parallelVector = lineSegment.vector();
        Vector2d perpendicularVector(parallelVector.x(), -parallelVector.y());
        double squaredLength = parallelVector.squaredNorm();
        Vector2d startVector = *this - lineSegment.startVertex();
        Zero zero(precision * precision * squaredLength);

        // Check whether the point is on the axis defined by the segment
        double perpendicularMetric = startVector.dot(perpendicularVector);
        if (perpendicularMetric * perpendicularMetric > zero) {
            return false;
        }

        // Check whether point is located within the segment
        Point1d localCoordinates = *this / lineSegment.coordinateSystem();
        if (!Interval::Unit().contains(localCoordinates.value())) {
            return false;
        }

        // Passed all checks
        return true;
    }

    inline
    const Point2d
    Point2d::Polar(double radius, double angle) {
        return Point2d(radius * cos(angle), radius * sin(angle));
    }

    inline
    Point3d::Point() {
    }

    inline
    Point3d::Point(double x, double y, double z) :
        detail::PointBase<3>(x, y, z) {
    }

    inline
    Point3d::Point(const Vector3d& vector) :
        detail::PointBase<3>(vector.components()) {
    }

    inline
    Point3d::Point(const ColMatrix3x1& components) :
        detail::PointBase<3>(components) {
    }

    inline
    Point3d::Point(const double* sourcePtr) :
        detail::PointBase<3>(sourcePtr) {
    }

    inline
    double
    Point3d::squaredDistanceTo(const Axis3d& axis) const {
        return (*this - this->projectedOnto(axis)).squaredNorm();
    }

    inline
    double
    Point3d::distanceTo(const Axis3d& axis) const {
        return sqrt(squaredDistanceTo(axis));
    }

    inline
    double
    Point3d::distanceTo(const Plane3d& plane) const {
        return (*this - plane.originPoint()).dot(plane.normalVector());
    }

    inline
    bool
    Point3d::isOn(const Axis3d& axis, double precision) const {
        return squaredDistanceTo(axis) == Zero(precision * precision);
    }

    inline
    bool
    Point3d::isOn(const Plane3d& plane, double precision) const {
        return distanceTo(plane) == Zero(precision);
    }

    inline
    bool
    Point3d::isOn(const LineSegment3d& lineSegment, double precision) const {
        Vector3d parallelVector = lineSegment.vector();
        double squaredLength = parallelVector.squaredNorm();
        Vector3d startVector = *this - lineSegment.startVertex();
        Zero zero(precision * precision * squaredLength);

        // Check whether the point is on the axis defined by the segment
        double perpendicularMetric = startVector.cross(parallelVector).squaredNorm();
        if (perpendicularMetric > zero) {
            return false;
        }

        // Check whether point is located within the segment
        Point1d localCoordinates = *this / lineSegment.coordinateSystem();
        if (!Interval::Unit().contains(localCoordinates.value())) {
            return false;
        }

        // Passed all checks
        return true;
    }

    inline
    bool
    Point3d::isOn(const Triangle3d& triangle, double precision) const {
        Point3d firstVertex = triangle.vertex(0);
        Vector3d firstEdgeVector = triangle.vertex(1) - firstVertex;
        Vector3d secondEdgeVector = triangle.vertex(2) - firstVertex;
        
        // Check whether the point is on the plane defined by the triangle
        Vector3d perpendicularVector = firstEdgeVector.cross(secondEdgeVector);
        double perpendicularSquaredLength = perpendicularVector.squaredNorm();
        Vector3d displacement = *this - firstVertex;
        double perpendicularDotProduct = displacement.dot(perpendicularVector);
        double perpendicularMetric = perpendicularDotProduct * perpendicularDotProduct;
        Zero perpendicularZero(perpendicularSquaredLength * precision * precision);
        if (perpendicularMetric > perpendicularZero) {
            return false;
        }

        // Check whether the point is within the triangle
        PlanarCoordinateSystem3d triangleCoordinateSystem(
            firstVertex,
            firstEdgeVector,
            secondEdgeVector
        );
        Point2d triangleCoordinates = *this / triangleCoordinateSystem;
        double a = triangleCoordinates.x();
        double b = triangleCoordinates.y();
        Zero coordinateZero(precision);
        if (a < coordinateZero || b < coordinateZero || 1 - a - b < coordinateZero) {
            return false;
        }
        
        // Passed both checks
        return true;
    }

    inline
    const Point3d
    Point3d::Cylindrical(double radius, double angle, double height) {
        return Point3d(radius * cos(angle), radius * sin(angle), height);
    }

    inline
    const Point3d
    Point3d::Spherical(double radius, double polarAngle, double elevationAngle) {
        double sinElevation = sin(elevationAngle);
        double cosElevation = cos(elevationAngle);
        double sinPolar = sin(polarAngle);
        double cosPolar = cos(polarAngle);
        return Point3d(
            radius * cosElevation * cosPolar,
            radius * cosElevation * sinPolar,
            radius * sinElevation
        );
    }

    template <int iNumDimensions>
    inline
    const Point<iNumDimensions>
    operator+(const Point<iNumDimensions>& point, const Vector<double, iNumDimensions>& vector) {
        return Point<iNumDimensions>(point.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    const Point<iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Vector<double, iNumDimensions>& vector) {
        return Point<iNumDimensions>(point.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    const Vector<double, iNumDimensions>
    operator-(const Point<iNumDimensions>& firstPoint, const Point<iNumDimensions>& secondPoint) {
        return Vector<double, iNumDimensions>(firstPoint.components() - secondPoint.components());
    }

    template <int iNumDimensions>
    std::ostream&
    operator<<(std::ostream& stream, const Point<iNumDimensions>& point) {
        stream << "Point" << iNumDimensions << "d";
        stream << "(";
        for (int index = 0; index < iNumDimensions; ++index) {
            stream << point.component(index);
            if (index < iNumDimensions - 1) {
                stream << ",";
            }
        }
        stream << ")";
        return stream;
    }

    template <int iNumDimensions>
    inline
    bool
    EqualityFunction<Point<iNumDimensions>>::operator()(
        const Point<iNumDimensions>& firstPoint,
        const Point<iNumDimensions>& secondPoint,
        double precision
    ) const {
        return (firstPoint - secondPoint).isZero(precision);
    }

    template <int iNumDimensions>
    inline
    const Box<iNumDimensions>
    BoundsFunction<Point<iNumDimensions>>::operator()(const Point<iNumDimensions>& point) const {
        return Box<iNumDimensions>(
            point.components().map(
                [] (double component) -> Interval {
                    return Interval(component);
                }
            )
        );
    }

    template <int iNumDimensions>
    inline
    const Point<iNumDimensions>
    ScalingFunction<Point<iNumDimensions>>::operator()(
        const Point<iNumDimensions>& point,
        double scale
    ) const {
        return Point<iNumDimensions>(scale * point.components());
    }

    template <int iNumDimensions>
    inline
    const Point<iNumDimensions>
    TranslationFunction<Point<iNumDimensions>>::operator()(
        const Point<iNumDimensions>& point,
        const Vector<double, iNumDimensions>& vector
    ) const {
        return Point<iNumDimensions>(point.components() + vector.components());
    }

    template <int iNumDimensions, int iNumResultDimensions>
    inline
    const Point<iNumResultDimensions>
    TransformationFunction<Point<iNumDimensions>, iNumResultDimensions>::operator()(
        const Point<iNumDimensions>& point,
        const Matrix<double, iNumResultDimensions, iNumDimensions>& matrix
    ) const {
        return Point<iNumResultDimensions>(matrix * point.components());
    }

    template <int iNumDimensions, int iNumResultDimensions>
    inline
    const Point<iNumResultDimensions>
    MorphingFunction<Point<iNumDimensions>, iNumResultDimensions>::operator()(
        const Point<iNumDimensions>& point,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return Point<iNumResultDimensions>(morphingExpression.evaluate(point.components()));
    }
}
