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

#include <OpenSolid/Core/ParametricExpression/TransformableExpression.definitions.hpp>

#include <OpenSolid/Core/Axis.definitions.hpp>
#include <OpenSolid/Core/Frame.definitions.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/ParametricExpression.definitions.hpp>
#include <OpenSolid/Core/Plane.definitions.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Quaternion.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TParameter>
        inline
        const ParametricExpression<Vector2d, TParameter>&
        TransformableExpression<Vector2d, TParameter>::derived() const {
            return static_cast<const ParametricExpression<Vector2d, TParameter>&>(*this);
        }

        template <class TParameter>        
        ParametricExpression<UnitVector2d, TParameter>
        TransformableExpression<Vector2d, TParameter>::unitOrthogonal() const {
            return ParametricExpression<Vector2d, TParameter>::fromComponents(
                -derived().y(),
                derived().x()
            ).normalized();
        }

        template <class TParameter> template <class TTransformation>
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<Vector2d, TParameter>::transformedBy(
            const TTransformation& transformation
        ) const {
            return transformation.transform(derived());
        }

        template <class TParameter>
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<Vector2d, TParameter>::placedOnto(const Plane3d& plane) const {
            return plane.basisMatrix() * derived().implementation();
        }

        template <class TParameter>
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<Vector2d, TParameter>::projectedOnto(const Axis2d& axis) const {
            return derived().dot(axis.directionVector()) * axis.directionVector();
        }

        template <class TParameter>
        inline
        const ParametricExpression<Vector3d, TParameter>&
        TransformableExpression<Vector3d, TParameter>::derived() const {
            return static_cast<const ParametricExpression<Vector3d, TParameter>&>(*this);
        }

        template <class TParameter> template <class TTransformation>
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<Vector3d, TParameter>::transformedBy(
            const TTransformation& transformation
        ) const {
            return transformation.transform(derived());
        }

        template <class TParameter>
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<Vector3d, TParameter>::projectedInto(const Plane3d& plane) const {
            return plane.basisMatrix().transpose() * derived().implementation();
        }

        template <class TParameter>
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<Vector3d, TParameter>::projectedOnto(const Axis3d& axis) const {
            return derived().dot(axis.directionVector()) * axis.directionVector();
        }

        template <class TParameter>
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<Vector3d, TParameter>::projectedOnto(const Plane3d& plane) const {
            return derived() - derived().dot(plane.normalVector()) * plane.normalVector();
        }

        template <class TParameter>
        inline
        const ParametricExpression<UnitVector2d, TParameter>&
        TransformableExpression<UnitVector2d, TParameter>::derived() const {
            return static_cast<const ParametricExpression<UnitVector2d, TParameter>&>(*this);
        }

        template <class TParameter>        
        ParametricExpression<UnitVector2d, TParameter>
        TransformableExpression<UnitVector2d, TParameter>::unitOrthogonal() const {
            return ParametricExpression<UnitVector2d, TParameter>::fromComponents(
                -derived().y(),
                derived().x()
            );
        }

        template <class TParameter> template <class TTransformation>
        ParametricExpression<UnitVector2d, TParameter>
        TransformableExpression<UnitVector2d, TParameter>::transformedBy(
            const TTransformation& transformation
        ) const {
            return transformation.transform(derived());
        }

        template <class TParameter>
        ParametricExpression<UnitVector3d, TParameter>
        TransformableExpression<UnitVector2d, TParameter>::placedOnto(const Plane3d& plane) const {
            return plane.basisMatrix() * derived().implementation();
        }

        template <class TParameter>
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<UnitVector2d, TParameter>::projectedOnto(const Axis2d& axis) const {
            return derived().dot(axis.directionVector()) * axis.directionVector();
        }

        template <class TParameter>
        inline
        const ParametricExpression<UnitVector3d, TParameter>&
        TransformableExpression<UnitVector3d, TParameter>::derived() const {
            return static_cast<const ParametricExpression<UnitVector3d, TParameter>&>(*this);
        }

        template <class TParameter> template <class TTransformation>
        ParametricExpression<UnitVector3d, TParameter>
        TransformableExpression<UnitVector3d, TParameter>::transformedBy(
            const TTransformation& transformation
        ) const {
            return transformation.transform(derived());
        }

        template <class TParameter>
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<UnitVector3d, TParameter>::projectedInto(
            const Plane3d& plane
        ) const {
            return plane.basisMatrix().transpose() * derived().implementation();
        }

        template <class TParameter>
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<UnitVector3d, TParameter>::projectedOnto(const Axis3d& axis) const {
            return derived().dot(axis.directionVector()) * axis.directionVector();
        }

        template <class TParameter>
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<UnitVector3d, TParameter>::projectedOnto(
            const Plane3d& plane
        ) const {
            return derived() - derived().dot(plane.normalVector()) * plane.normalVector();
        }

        template <class TParameter>
        inline
        const ParametricExpression<Point2d, TParameter>&
        TransformableExpression<Point2d, TParameter>::derived() const {
            return static_cast<const ParametricExpression<Point2d, TParameter>&>(*this);
        }

        template <class TParameter>
        ParametricExpression<double, TParameter>
        TransformableExpression<Point2d, TParameter>::distanceTo(const Axis2d& axis) const {
            return (derived() - axis.originPoint()).dot(axis.normalVector());
        }

        template <class TParameter>
        ParametricExpression<double, TParameter>
        TransformableExpression<Point2d, TParameter>::distanceAlong(const Axis2d& axis) const {
            return (derived() - axis.originPoint()).dot(axis.directionVector());
        }

        template <class TParameter> template <class TTransformation>
        ParametricExpression<Point2d, TParameter>
        TransformableExpression<Point2d, TParameter>::transformedBy(
            const TTransformation& transformation
        ) const {
            return transformation.transform(derived());
        }

        template <class TParameter>
        ParametricExpression<Point3d, TParameter>
        TransformableExpression<Point2d, TParameter>::placedOnto(const Plane3d& plane) const {
            ParametricExpression<Vector3d, TParameter> displacement(
                plane.basisMatrix() * derived().implementation()
            );
            return plane.originPoint() + displacement;
        }

        template <class TParameter>
        ParametricExpression<Point2d, TParameter>
        TransformableExpression<Point2d, TParameter>::projectedOnto(const Axis2d& axis) const {
            return axis.originPoint() + distanceAlong(axis) * axis.directionVector();
        }

        template <class TParameter>
        inline
        const ParametricExpression<Point3d, TParameter>&
        TransformableExpression<Point3d, TParameter>::derived() const {
            return static_cast<const ParametricExpression<Point3d, TParameter>&>(*this);
        }

        template <class TParameter>
        ParametricExpression<double, TParameter>
        TransformableExpression<Point3d, TParameter>::squaredDistanceTo(const Axis3d& axis) const {
            return (derived() - derived().projectedOnto(axis)).squaredNorm();
        }

        template <class TParameter>
        ParametricExpression<double, TParameter>
        TransformableExpression<Point3d, TParameter>::distanceTo(const Axis3d& axis) const {
            return opensolid::sqrt(squaredDistanceTo(axis));
        }

        template <class TParameter>
        ParametricExpression<double, TParameter>
        TransformableExpression<Point3d, TParameter>::distanceAlong(const Axis3d& axis) const {
            return (derived() - axis.originPoint()).dot(axis.directionVector());
        }

        template <class TParameter>
        ParametricExpression<double, TParameter>
        TransformableExpression<Point3d, TParameter>::distanceTo(const Plane3d& plane) const {
            return (derived() - plane.originPoint()).dot(plane.normalVector());
        }

        template <class TParameter> template <class TTransformation>
        ParametricExpression<Point3d, TParameter>
        TransformableExpression<Point3d, TParameter>::transformedBy(
            const TTransformation& transformation
        ) const {
            return transformation.transform(derived());
        }

        template <class TParameter>
        ParametricExpression<Point2d, TParameter>
        TransformableExpression<Point3d, TParameter>::projectedInto(const Plane3d& plane) const {
            return (derived() - plane.originPoint()).projectedInto(plane).implementation();
        }

        template <class TParameter>
        ParametricExpression<Point3d, TParameter>
        TransformableExpression<Point3d, TParameter>::projectedOnto(const Axis3d& axis) const {
            return axis.originPoint() + distanceAlong(axis) * axis.directionVector();
        }

        template <class TParameter>
        ParametricExpression<Point3d, TParameter>
        TransformableExpression<Point3d, TParameter>::projectedOnto(const Plane3d& plane) const {
            return (
                derived() -
                (derived() - plane.originPoint()).dot(plane.normalVector()) *
                plane.normalVector()
            );
        }
    }
}
