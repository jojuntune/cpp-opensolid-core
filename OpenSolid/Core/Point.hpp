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
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Cartesian.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/LineSegment.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Triangle.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        PointCommon<iNumDimensions>::derived() const {
            return static_cast<const Point<iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        PointCommon<iNumDimensions>::PointCommon() {
        }

        template <int iNumDimensions>
        inline
        PointCommon<iNumDimensions>::PointCommon(double x, double y) :
            Cartesian<double, iNumDimensions>(x, y) {
        }

        template <int iNumDimensions>
        inline
        PointCommon<iNumDimensions>::PointCommon(double x, double y, double z) :
            Cartesian<double, iNumDimensions>(x, y, z) {
        }

        template <int iNumDimensions>
        inline
        PointCommon<iNumDimensions>::PointCommon(
            const Matrix<double, iNumDimensions, 1>& components
        ) : Cartesian<double, iNumDimensions>(components) {
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        PointCommon<iNumDimensions>::bounds() const {
            return Box<iNumDimensions>(
                this->components().map(
                    [] (double component) -> Interval {
                        return Interval(component);
                    }
                )
            );
        }

        template <int iNumDimensions>
        inline
        double
        PointCommon<iNumDimensions>::squaredDistanceTo(const Point<iNumDimensions>& other) const {
            return (derived() - other).squaredNorm();
        }

        template <int iNumDimensions>
        inline
        double
        PointCommon<iNumDimensions>::distanceTo(const Point<iNumDimensions>& other) const {
            return (derived() - other).norm();
        }

        template <int iNumDimensions>
        inline
        bool
        PointCommon<iNumDimensions>::equals(
            const Point<iNumDimensions>& other,
            double precision
        ) const {
            return (derived() - other).isZero(precision);
        }

        template <int iNumDimensions>
        inline
        bool
        PointCommon<iNumDimensions>::isOrigin(double precision) const {
            return this->components().cwiseSquared().sum() == Zero(precision * precision);
        }

        template <int iNumDimensions>
        inline
        double
        PointCommon<iNumDimensions>::distanceAlong(const Axis<iNumDimensions>& axis) const {
            return (derived() - axis.originPoint()).dot(axis.directionVector());
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        PointCommon<iNumDimensions>::hull(const Point<iNumDimensions>& other) const {
            return Box<iNumDimensions>(
                this->components().binaryMap(
                    other.components(),
                    [] (double component, double otherComponent) -> Interval {
                        return Interval::hull(component, otherComponent);
                    }
                )
            );
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        PointCommon<iNumDimensions>::hull(const Box<iNumDimensions>& box) const {
            return Box<iNumDimensions>(
                this->components().binaryMap(
                    box.components(),
                    [] (double component, Interval boxComponent) -> Interval {
                        return boxComponent.hull(component);
                    }
                )
            );
        }

        template <int iNumDimensions> template <class TTransformation>
        inline
        Point<iNumDimensions>
        PointCommon<iNumDimensions>::transformedBy(const TTransformation& transformation) const {
            return transformation.transform(derived());
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointCommon<iNumDimensions>::projectedOnto(const Axis<iNumDimensions>& axis) const {
            return axis.originPoint() + distanceAlong(axis) * axis.directionVector();
        }

        template <int iNumDimensions>
        inline
        bool
        PointCommon<iNumDimensions>::operator==(const Point<iNumDimensions>& other) const {
            return this->components() == other.components();
        }

        template <int iNumDimensions>
        inline
        bool
        PointCommon<iNumDimensions>::operator!=(const Point<iNumDimensions>& other) const {
            return this->components() != other.components();
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointCommon<iNumDimensions>::ORIGIN() {
            return Point<iNumDimensions>(Matrix<double, iNumDimensions, 1>::ZERO());
        }
    }

    inline
    Point2d::Point() {
    }

    inline
    Point2d::Point(double x, double y) :
        detail::PointCommon<2>(x, y) {
    }

    inline
    Point2d::Point(const ColumnMatrix2d& components) :
        detail::PointCommon<2>(components) {
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
    Point2d::placedOnto(const Plane3d& plane) const {
        return plane.originPoint() + Vector2d(components()).placedOnto(plane);
    }

    inline
    Point3d::Point() {
    }

    inline
    Point3d::Point(double x, double y, double z) :
        detail::PointCommon<3>(x, y, z) {
    }

    inline
    Point3d::Point(const ColumnMatrix3d& components) :
        detail::PointCommon<3>(components) {
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
    Point3d::projectedInto(const Plane3d& plane) const {
        return Point2d((*this - plane.originPoint()).projectedInto(plane).components());
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
}
