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

#include <OpenSolid/Core/Position/PointBase.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Box.hpp>
#include <OpenSolid/Core/Cartesian/CartesianBase.hpp>
#include <OpenSolid/Core/Frame.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        PointBase<iNumDimensions>::derived() const {
            return static_cast<const Point<iNumDimensions>&>(*this);
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase() {
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase(double x, double y) :
            CartesianBase<double, iNumDimensions>(x, y) {
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase(double x, double y, double z) :
            CartesianBase<double, iNumDimensions>(x, y, z) {
        }

        template <int iNumDimensions>
        inline
        PointBase<iNumDimensions>::PointBase(const Matrix<double, iNumDimensions, 1>& components) :
            detail::CartesianBase<double, iNumDimensions>(components) {
        }

        template <int iNumDimensions>
        inline
        double
        PointBase<iNumDimensions>::squaredDistanceTo(const Point<iNumDimensions>& other) const {
            return (derived() - other).squaredNorm();
        }

        template <int iNumDimensions>
        inline
        double
        PointBase<iNumDimensions>::distanceTo(const Point<iNumDimensions>& other) const {
            return (derived() - other).norm();
        }

        template <int iNumDimensions>
        inline
        bool
        PointBase<iNumDimensions>::isEqualTo(
            const Point<iNumDimensions>& other,
            double precision
        ) const {
            return (derived() - other).isZero(precision);
        }

        template <int iNumDimensions>
        inline
        bool
        PointBase<iNumDimensions>::isOrigin(double precision) const {
            return this->components().cwiseSquared().sum() == Zero(precision * precision);
        }

        template <int iNumDimensions>
        inline
        double
        PointBase<iNumDimensions>::distanceAlong(const Axis<iNumDimensions>& axis) const {
            return (derived() - axis.originPoint()).dot(axis.directionVector());
        }

        template <int iNumDimensions>
        inline
        Box<iNumDimensions>
        PointBase<iNumDimensions>::hull(const Point<iNumDimensions>& other) const {
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
        PointBase<iNumDimensions>::hull(const Box<iNumDimensions>& box) const {
            return Box<iNumDimensions>(
                this->components().binaryMap(
                    box.components(),
                    [] (double component, Interval boxComponent) -> Interval {
                        return boxComponent.hull(component);
                    }
                )
            );
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointBase<iNumDimensions>::scaledAbout(
            const Point<iNumDimensions>& other,
            double scale
        ) const {
            return other + scale * (derived() - other);
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointBase<iNumDimensions>::rotatedAbout(
            const Point<iNumDimensions>& other,
            const Matrix<double, iNumDimensions, iNumDimensions>& rotationMatrix
        ) const {
            return other + (derived() - other).rotatedBy(rotationMatrix);
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointBase<iNumDimensions>::translatedBy(
            const Vector<double, iNumDimensions>& vector
        ) const {
            return derived() + vector;
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointBase<iNumDimensions>::toLocalIn(const Frame<iNumDimensions>& frame) const {
            return Point<iNumDimensions>(
                (derived() - frame.originPoint()).toLocalIn(frame).components()
            );
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointBase<iNumDimensions>::toGlobalFrom(const Frame<iNumDimensions>& frame) const {
            return (
                frame.originPoint() +
                Vector<double, iNumDimensions>(this->components()).toGlobalFrom(frame)
            );
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointBase<iNumDimensions>::mirroredAbout(
            const Point<iNumDimensions>& other,
            const UnitVector<iNumDimensions>& mirrorDirection
        ) const {
            return derived() - 2.0 * (derived() - other).dot(mirrorDirection) * mirrorDirection;
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointBase<iNumDimensions>::projectedOnto(const Axis<iNumDimensions>& axis) const {
            return axis.originPoint() + distanceAlong(axis) * axis.directionVector();
        }

        template <int iNumDimensions>
        inline
        bool
        PointBase<iNumDimensions>::operator==(const Point<iNumDimensions>& other) const {
            return this->components() == other.components();
        }

        template <int iNumDimensions>
        inline
        bool
        PointBase<iNumDimensions>::operator!=(const Point<iNumDimensions>& other) const {
            return this->components() != other.components();
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        PointBase<iNumDimensions>::origin() {
            return Point<iNumDimensions>(Matrix<double, iNumDimensions, 1>::zero());
        }
    }
}
