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
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<Vector2d, TParameter>::rotatedBy(double angle) const {
            return rotatedBy(Quaternion2d(angle).rotationMatrix());
        }

        template <class TParameter>
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<Vector2d, TParameter>::rotatedBy(
            const Matrix2d& rotationMatrix
        ) const {
            return rotationMatrix * derived().implementation();
        }

        template <class TParameter>
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<Vector2d, TParameter>::toLocalIn(const Frame2d& frame) const {
            return frame.basisMatrix().transpose() * derived().implementation();
        }

        template <class TParameter>
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<Vector2d, TParameter>::toGlobalFrom(const Frame2d& frame) const {
            return frame.basisMatrix() * derived().implementation();
        }

        template <class TParameter>
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<Vector2d, TParameter>::toGlobalFrom(const Plane3d& plane) const {
            return plane.basisMatrix() * derived().implementation();
        }

        template <class TParameter>
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<Vector2d, TParameter>::projectedOnto(const Axis2d& axis) const {
            return derived().dot(axis.directionVector()) * axis.directionVector();
        }

        template <class TParameter>
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<Vector2d, TParameter>::mirroredAlong(
            const UnitVector2d& mirrorDirection
        ) const {
            return derived() - 2.0 * derived().dot(mirrorDirection) * mirrorDirection;
        }

        template <class TParameter>
        inline
        const ParametricExpression<Vector3d, TParameter>&
        TransformableExpression<Vector3d, TParameter>::derived() const {
            return static_cast<const ParametricExpression<Vector3d, TParameter>&>(*this);
        }

        template <class TParameter>
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<Vector3d, TParameter>::rotatedBy(
            const Matrix3d& rotationMatrix
        ) const {
            return rotationMatrix * derived().implementation();
        }

        template <class TParameter>
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<Vector3d, TParameter>::rotatedAbout(
            const UnitVector3d& directionVector,
            double angle
        ) const {
            return rotatedBy(Quaternion3d(directionVector, angle).rotationMatrix());
        }

        template <class TParameter>
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<Vector3d, TParameter>::toLocalIn(const Frame3d& frame) const {
            return frame.basisMatrix().transpose() * derived().implementation();
        }

        template <class TParameter>
        ParametricExpression<Vector2d, TParameter>
        TransformableExpression<Vector3d, TParameter>::toLocalIn(const Plane3d& plane) const {
            return plane.basisMatrix().transpose() * derived().implementation();
        }

        template <class TParameter>
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<Vector3d, TParameter>::toGlobalFrom(const Frame3d& frame) const {
            return frame.basisMatrix() * derived().implementation();
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
        ParametricExpression<Vector3d, TParameter>
        TransformableExpression<Vector3d, TParameter>::mirroredAlong(
            const UnitVector3d& mirrorDirection
        ) const {
            return derived() - 2.0 * derived().dot(mirrorDirection) * mirrorDirection;
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

        template <class TParameter>
        ParametricExpression<Point2d, TParameter>
        TransformableExpression<Point2d, TParameter>::scaledAbout(
            const Point2d& point,
            double scale
        ) const {
            return point + scale * (derived() - point);
        }

        template <class TParameter>
        ParametricExpression<Point2d, TParameter>
        TransformableExpression<Point2d, TParameter>::rotatedAbout(
            const Point2d& point,
            const Matrix2d& rotationMatrix
        ) const {
            return point + (derived() - point).rotatedBy(rotationMatrix);
        }

        template <class TParameter>
        ParametricExpression<Point2d, TParameter>
        TransformableExpression<Point2d, TParameter>::translatedBy(const Vector2d& vector) const {
            return derived() + vector;
        }

        template <class TParameter>
        ParametricExpression<Point2d, TParameter>
        TransformableExpression<Point2d, TParameter>::toLocalIn(const Frame2d& frame) const {
            return Point2d::origin() + (derived() - frame.originPoint()).toLocalIn(frame);
        }

        template <class TParameter>
        ParametricExpression<Point2d, TParameter>
        TransformableExpression<Point2d, TParameter>::toGlobalFrom(const Frame2d& frame) const {
            return frame.originPoint() + (derived() - Point2d::origin()).toGlobalFrom(frame);
        }

        template <class TParameter>
        ParametricExpression<Point3d, TParameter>
        TransformableExpression<Point2d, TParameter>::toGlobalFrom(const Plane3d& plane) const {
            return plane.originPoint() + (derived() - Point2d::origin()).toGlobalFrom(plane);
        }

        template <class TParameter>
        ParametricExpression<Point2d, TParameter>
        TransformableExpression<Point2d, TParameter>::projectedOnto(const Axis2d& axis) const {
            return axis.originPoint() + distanceAlong(axis) * axis.directionVector();
        }

        template <class TParameter>
        ParametricExpression<Point2d, TParameter>
        TransformableExpression<Point2d, TParameter>::mirroredAbout(
            const Point2d& point,
            const UnitVector2d& mirrorDirection
        ) const {
            return derived() - 2.0 * (derived() - point).dot(mirrorDirection) * mirrorDirection;
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

        template <class TParameter>
        ParametricExpression<Point3d, TParameter>
        TransformableExpression<Point3d, TParameter>::scaledAbout(
            const Point3d& point,
            double scale
        ) const {
            return point + scale * (derived() - point);
        }

        template <class TParameter>
        ParametricExpression<Point3d, TParameter>
        TransformableExpression<Point3d, TParameter>::rotatedAbout(
            const Point3d& point,
            const Matrix3d& rotationMatrix
        ) const {
            return point + (derived() - point).rotatedBy(rotationMatrix);
        }

        template <class TParameter>
        ParametricExpression<Point3d, TParameter>
        TransformableExpression<Point3d, TParameter>::translatedBy(const Vector3d& vector) const {
            return derived() + vector;
        }

        template <class TParameter>
        ParametricExpression<Point3d, TParameter>
        TransformableExpression<Point3d, TParameter>::toLocalIn(const Frame3d& frame) const {
            return Point3d::origin() + (derived() - frame.originPoint()).toLocalIn(frame);
        }

        template <class TParameter>
        ParametricExpression<Point3d, TParameter>
        TransformableExpression<Point3d, TParameter>::toGlobalFrom(const Frame3d& frame) const {
            return frame.originPoint() + (derived() - Point3d::origin()).toGlobalFrom(frame);
        }

        template <class TParameter>
        ParametricExpression<Point2d, TParameter>
        TransformableExpression<Point3d, TParameter>::toLocalIn(const Plane3d& plane) const {
            return Point2d::origin() + (derived() - plane.originPoint()).toLocalIn(plane);
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

        template <class TParameter>
        ParametricExpression<Point3d, TParameter>
        TransformableExpression<Point3d, TParameter>::mirroredAbout(
            const Point3d& point,
            const UnitVector3d& mirrorDirection
        ) const {
            return derived() - 2.0 * (derived() - point).dot(mirrorDirection) * mirrorDirection;
        }
    }
}
