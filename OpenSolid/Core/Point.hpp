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
#include <OpenSolid/Core/UnitVector.hpp>

namespace opensolid
{
    inline
    Point2d::Point() {
    }

    inline
    Point2d::Point(double x, double y) :
        detail::PointBase<2>(x, y) {
    }

    inline
    Point2d::Point(const ColumnMatrix2d& components) :
        detail::PointBase<2>(components) {
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
    Point3d
    Point2d::toGlobalFrom(const Plane3d& plane) const {
        return plane.originPoint() + Vector2d(components()).toGlobalFrom(plane);
    }

    inline
    Point3d::Point() {
    }

    inline
    Point3d::Point(double x, double y, double z) :
        detail::PointBase<3>(x, y, z) {
    }

    inline
    Point3d::Point(const ColumnMatrix3d& components) :
        detail::PointBase<3>(components) {
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
        return squaredDistanceTo(axis) <= precision * precision;
    }

    inline
    bool
    Point3d::isOn(const Plane3d& plane, double precision) const {
        return distanceTo(plane) == Zero(precision);
    }

    inline
    Point2d
    Point3d::toLocalIn(const Plane3d& plane) const {
        return Point2d((*this - plane.originPoint()).toLocalIn(plane).components());
    }

    inline
    Point3d
    Point3d::projectedOnto(const Plane3d& plane) const {
        Vector3d displacement = *this - plane.originPoint();
        return *this - displacement.dot(plane.normalVector()) * plane.normalVector();
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>
    operator+(const Point<iNumDimensions>& point, const Vector<double, iNumDimensions>& vector) {
        return Point<iNumDimensions>(point.components() + vector.components());
    }

    template <int iNumDimensions>
    inline
    Point<iNumDimensions>
    operator-(const Point<iNumDimensions>& point, const Vector<double, iNumDimensions>& vector) {
        return Point<iNumDimensions>(point.components() - vector.components());
    }

    template <int iNumDimensions>
    inline
    Vector<double, iNumDimensions>
    operator-(const Point<iNumDimensions>& firstPoint, const Point<iNumDimensions>& secondPoint) {
        return Vector<double, iNumDimensions>(firstPoint.components() - secondPoint.components());
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
    Box<iNumDimensions>
    BoundsFunction<Point<iNumDimensions>>::operator()(const Point<iNumDimensions>& point) const {
        return Box<iNumDimensions>(
            point.components().map(
                [] (double component) -> Interval {
                    return Interval(component);
                }
            )
        );
    }
}
