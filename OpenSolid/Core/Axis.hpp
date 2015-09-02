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
        AxisCommon<iNumDimensions>::AxisCommon() :
            FrameBase<iNumDimensions, 1>(
                Point<iNumDimensions>::ORIGIN(),
                Matrix<double, iNumDimensions, 1>::ZERO()
            ) {
        }

        template <int iNumDimensions>
        inline
        AxisCommon<iNumDimensions>::AxisCommon(
            const Point<iNumDimensions>& originPoint,
            const UnitVector<iNumDimensions>& directionVector
        ) : FrameBase<iNumDimensions, 1>(originPoint, directionVector.components()) {
        }
    
        template <int iNumDimensions>
        inline
        UnitVector<iNumDimensions>
        AxisCommon<iNumDimensions>::directionVector() const {
            return UnitVector<iNumDimensions>(this->basisMatrix());
        }
    
        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        AxisCommon<iNumDimensions>::pointAt(double distance) const {
            return this->originPoint() + distance * directionVector();
        }
    }

    inline
    Axis2d::Axis() {
    }

    inline
    Axis2d::Axis(
        const Point2d& originPoint,
        const UnitVector2d& directionVector
    ) : detail::AxisCommon<2>(originPoint, directionVector),
        _handedness(Handedness::RIGHT_HANDED()) {
    }

    inline
    Axis2d::Axis(
        const Point2d& originPoint,
        const UnitVector2d& directionVector,
        Handedness handedness
    ) : detail::AxisCommon<2>(originPoint, directionVector),
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
    Axis2d::X() {
        return Axis2d(Point2d::ORIGIN(), UnitVector2d::X());
    }

    inline
    Axis2d
    Axis2d::Y() {
        return Axis2d(Point2d::ORIGIN(), UnitVector2d::Y());
    }

    inline
    Axis3d::Axis() {
    }

    inline
    Axis3d::Axis(
        const Point3d& originPoint,
        const UnitVector3d& directionVector
    ) : detail::AxisCommon<3>(originPoint, directionVector) {
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
    Axis3d::X() {
        return Axis3d(Point3d::ORIGIN(), UnitVector3d::X());
    }

    inline
    Axis3d
    Axis3d::Y() {
        return Axis3d(Point3d::ORIGIN(), UnitVector3d::Y());
    }

    inline
    Axis3d
    Axis3d::Z() {
        return Axis3d(Point3d::ORIGIN(), UnitVector3d::Z());
    }
}
