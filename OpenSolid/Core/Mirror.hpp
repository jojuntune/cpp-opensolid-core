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

#include <OpenSolid/Core/Mirror.definitions.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Transformation.definitions.hpp>
#include <OpenSolid/Core/UnitVector.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        inline
        MirrorBase<iNumDimensions>::MirrorBase(
            const Point<iNumDimensions>& point,
            const UnitVector<iNumDimensions>& mirrorDirection
        ) : _point(point),
            _mirrorDirection(mirrorDirection) {
        }

        template <int iNumDimensions>
        inline
        const Point<iNumDimensions>&
        MirrorBase<iNumDimensions>::point() const {
            return _point;
        }

        template <int iNumDimensions>
        inline
        const UnitVector<iNumDimensions>&
        MirrorBase<iNumDimensions>::mirrorDirection() const {
            return _mirrorDirection;
        }

        template <int iNumDimensions>
        inline
        double
        MirrorBase<iNumDimensions>::scale() const {
            return 1.0;
        }

        template <int iNumDimensions>
        inline
        Handedness
        MirrorBase<iNumDimensions>::transform(Handedness handedness) const {
            return -handedness;
        }

        template <int iNumDimensions>
        inline
        Point<iNumDimensions>
        MirrorBase<iNumDimensions>::transform(const Point<iNumDimensions>& point) const {
            return point - 2.0 * (point - this->point()).dot(mirrorDirection()) * mirrorDirection();
        }

        template <int iNumDimensions> template <class TParameter>
        inline
        ParametricExpression<Point<iNumDimensions>, TParameter>
        MirrorBase<iNumDimensions>::transform(
            const ParametricExpression<Point<iNumDimensions>, TParameter>& expression
        ) const {
            return (
                expression - 2.0 *
                (expression - this->point()).dot(mirrorDirection()) * mirrorDirection()
            );
        }

        template <int iNumDimensions>
        inline
        Vector<double, iNumDimensions>
        MirrorBase<iNumDimensions>::transform(const Vector<double, iNumDimensions>& vector) const {
            return vector - 2.0 * vector.dot(mirrorDirection()) * mirrorDirection();
        }

        template <int iNumDimensions> template <class TParameter>
        inline
        ParametricExpression<Vector<double, iNumDimensions>, TParameter>
        MirrorBase<iNumDimensions>::transform(
            const ParametricExpression<Vector<double, iNumDimensions>, TParameter>& expression
        ) const {
            return expression - 2.0 * expression.dot(mirrorDirection()) * mirrorDirection();
        }

        template <int iNumDimensions>
        inline
        UnitVector<iNumDimensions>
        MirrorBase<iNumDimensions>::transform(const UnitVector<iNumDimensions>& unitVector) const {
            double dotProduct = unitVector.dot(mirrorDirection());
            return UnitVector<iNumDimensions>(
                unitVector.components() - 2.0 * dotProduct * mirrorDirection().components()
            );
        }

        template <int iNumDimensions> template <class TParameter>
        inline
        ParametricExpression<UnitVector<iNumDimensions>, TParameter>
        MirrorBase<iNumDimensions>::transform(
            const ParametricExpression<UnitVector<iNumDimensions>, TParameter>& expression
        ) const {
            return (
                expression - 2.0 * expression.dot(mirrorDirection()) * mirrorDirection()
            ).implementation();
        }
    }

    inline
    Mirror2d::Mirror(const Point2d& point, const UnitVector2d& mirrorDirection) :
        detail::MirrorBase<2>(point, mirrorDirection) {
    }

    inline
    Mirror2d::Mirror(const Axis2d& axis) :
        detail::MirrorBase<2>(axis.originPoint(), axis.directionVector().unitOrthogonal()) {
    }

    inline
    Mirror3d::Mirror(const Point3d& point, const UnitVector3d& mirrorDirection) :
        detail::MirrorBase<3>(point, mirrorDirection) {
    }

    inline
    Mirror3d::Mirror(const Plane3d& plane) :
        detail::MirrorBase<3>(plane.originPoint(), plane.normalVector()) {
    }
}
