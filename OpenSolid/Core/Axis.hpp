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

#include <OpenSolid/Core/Axis.definitions.hpp>

#include <OpenSolid/Core/AxisPlaneIntersection3d.hpp>
#include <OpenSolid/Core/AxisTriangleIntersection3d.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/FrameBase.hpp>
#include <OpenSolid/Core/Handedness.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.definitions.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Zero.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        AxisBase<iNumDimensions>::AxisBase() :
            FrameBase<iNumDimensions, 1>(
                Point<iNumDimensions>::origin(),
                Matrix<double, iNumDimensions, 1>::zero()
            ) {
        }

        template <int iNumDimensions>
        inline
        AxisBase<iNumDimensions>::AxisBase(
            const Point<iNumDimensions>& originPoint,
            const UnitVector<iNumDimensions>& directionVector
        ) : FrameBase<iNumDimensions, 1>(originPoint, directionVector.components()) {
        }
    
        template <int iNumDimensions>
        inline
        UnitVector<iNumDimensions>
        AxisBase<iNumDimensions>::directionVector() const {
            return UnitVector<iNumDimensions>(basisMatrix());
        }
    
        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        AxisBase<iNumDimensions>::pointAt(double distance) const {
            return originPoint() + distance * directionVector();
        }
    }

    inline
    Axis2d::Axis() :
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    Axis2d::Axis(
        const Point2d& originPoint,
        const UnitVector2d& directionVector
    ) : detail::AxisBase<2>(originPoint, directionVector),
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    Axis2d::Axis(
        const Point2d& originPoint,
        const UnitVector2d& directionVector,
        Handedness handedness
    ) : detail::AxisBase<2>(originPoint, directionVector),
        _handedness(handedness) {
    }

    inline
    Handedness
    Axis2d::handedness() const {
        return _handedness;
    }

    inline
    UnitVector2d
    Axis2d::normalVector() const {
        return handedness().sign() * directionVector().unitOrthogonal();
    }

    inline
    Axis2d
    Axis2d::reversed() const {
        return Axis2d(originPoint(), -directionVector(), -handedness());
    }

    inline
    Axis2d
    Axis2d::normalAxis() const {
        return Axis2d(originPoint(), normalVector(), handedness());
    }

    template <class TTransformation>
    inline
    Axis2d
    Axis2d::transformedBy(const TTransformation& transformation) const {
        return Axis2d(
            originPoint().transformedBy(transformation),
            directionVector().transformedBy(transformation),
            handedness().transformedBy(transformation)
        );
    }

    inline
    Axis2d
    Axis2d::projectedOnto(const Axis2d& other) const {
        return Axis2d(
            originPoint().projectedOnto(other),
            directionVector().projectedOnto(other).normalized(),
            handedness()
        );
    }

    inline
    Axis3d
    Axis2d::placedOnto(const Plane3d& plane) const {
        return Axis3d(originPoint().placedOnto(plane), directionVector().placedOnto(plane));
    }

    inline
    Axis2d
    Axis2d::x() {
        return Axis2d(Point2d::origin(), UnitVector2d::X());
    }

    inline
    Axis2d
    Axis2d::y() {
        return Axis2d(Point2d::origin(), UnitVector2d::Y());
    }

    inline
    Axis3d::Axis() {
    }

    inline
    Axis3d::Axis(
        const Point3d& originPoint,
        const UnitVector3d& directionVector
    ) : detail::AxisBase<3>(originPoint, directionVector) {
    }

    inline
    Axis3d
    Axis3d::reversed() const {
        return Axis3d(originPoint(), -directionVector());
    }

    inline
    Plane3d
    Axis3d::normalPlane() const {
        return Plane3d(originPoint(), directionVector());
    }

    inline
    Intersection<Axis3d, Plane3d>
    Axis3d::intersection(const Plane3d& plane, double precision) const {
        return Intersection<Axis3d, Plane3d>(*this, plane, precision);
    }

    inline
    Intersection<Axis3d, Triangle3d>
    Axis3d::intersection(const Triangle3d& triangle, double precision) const {
        return Intersection<Axis3d, Triangle3d>(*this, triangle, precision);
    }

    template <class TTransformation>
    inline
    Axis3d
    Axis3d::transformedBy(const TTransformation& transformation) const {
        return Axis3d(
            originPoint().transformedBy(transformation),
            directionVector().transformedBy(transformation)
        );
    }

    inline
    Axis3d
    Axis3d::projectedOnto(const Axis3d& other) const {
        return Axis3d(
            originPoint().projectedOnto(other),
            directionVector().projectedOnto(other).normalized()
        );
    }

    inline
    Axis3d
    Axis3d::projectedOnto(const Plane3d& plane) const {
        return Axis3d(
            originPoint().projectedOnto(plane),
            directionVector().projectedOnto(plane).normalized()
        );
    }

    inline
    Axis2d
    Axis3d::projectedInto(const Plane3d& plane) const {
        return Axis2d(
            originPoint().projectedInto(plane),
            directionVector().projectedInto(plane).normalized()
        );
    }

    inline
    Axis3d
    Axis3d::x() {
        return Axis3d(Point3d::origin(), UnitVector3d::X());
    }

    inline
    Axis3d
    Axis3d::y() {
        return Axis3d(Point3d::origin(), UnitVector3d::Y());
    }

    inline
    Axis3d
    Axis3d::z() {
        return Axis3d(Point3d::origin(), UnitVector3d::Z());
    }
}
