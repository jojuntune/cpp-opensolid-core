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

#include <OpenSolid/Core/Rotation.definitions.hpp>

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Quaternion.hpp>
#include <OpenSolid/Core/Transformation.hpp>

namespace opensolid
{
    inline
    Rotation2d::Rotation(const Point2d& point, double angle) :
        _point(point),
        _cosAngle(cos(angle)),
        _sinAngle(sin(angle)) {
    }
    
    inline
    Rotation2d::Rotation(const Point2d& point, const Quaternion2d& quaternion) :
        _point(point),
        _cosAngle(quaternion.cosAngle()),
        _sinAngle(quaternion.sinAngle()) {
    }

    inline
    Rotation2d::Rotation(const Point2d& point, const Matrix2d& rotationMatrix) :
        _point(point),
        _cosAngle((rotationMatrix(0) + rotationMatrix(3)) / 2.0),
        _sinAngle((rotationMatrix(1) - rotationMatrix(2)) / 2.0) {
    }

    inline
    const Point2d&
    Rotation2d::point() const {
        return _point;
    }

    inline
    double
    Rotation2d::cosAngle() const {
        return _cosAngle;
    }

    inline
    double
    Rotation2d::sinAngle() const {
        return _sinAngle;
    }

    inline
    double
    Rotation2d::scale() const {
        return 1.0;
    }

    inline
    Handedness
    Rotation2d::transform(Handedness handedness) const {
        return handedness;
    }

    inline
    Point2d
    Rotation2d::transform(const Point2d& point) const {
        return this->point() + transform(point - this->point());
    }

    template <class TParameter>
    inline
    ParametricExpression<Point2d, TParameter>
    Rotation2d::transform(const ParametricExpression<Point2d, TParameter>& expression) const {
        return point() + transform(expression - point());
    }

    inline
    Vector2d
    Rotation2d::transform(const Vector2d& vector) const {
        return Vector2d(
            cosAngle() * vector.x() - sinAngle() * vector.y(),
            sinAngle() * vector.x() + cosAngle() * vector.y()
        );
    }

    template <class TParameter>
    inline
    ParametricExpression<Vector2d, TParameter>
    Rotation2d::transform(const ParametricExpression<Vector2d, TParameter>& expression) const {
        Matrix2d rotationMatrix(cosAngle(), sinAngle(), -sinAngle(), cosAngle());
        return rotationMatrix * expression.implementation();
    }

    inline
    UnitVector2d
    Rotation2d::transform(const UnitVector2d& unitVector) const {
        return UnitVector2d(
            cosAngle() * unitVector.x() - sinAngle() * unitVector.y(),
            sinAngle() * unitVector.x() + cosAngle() * unitVector.y()
        );
    }

    template <class TParameter>
    inline
    ParametricExpression<UnitVector2d, TParameter>
    Rotation2d::transform(const ParametricExpression<UnitVector2d, TParameter>& expression) const {
        Matrix2d rotationMatrix(cosAngle(), sinAngle(), -sinAngle(), cosAngle());
        return rotationMatrix * expression.implementation();
    }

    inline
    Rotation3d::Rotation(const Point3d& point, const Matrix3d& rotationMatrix) :
        _point(point),
        _rotationMatrix(rotationMatrix) {
    }

    inline
    Rotation3d::Rotation(const Axis3d& axis, double angle) :
        _point(axis.originPoint()),
        _rotationMatrix(Quaternion3d(axis.directionVector(), angle).rotationMatrix()) {
    }

    inline    
    Rotation3d::Rotation(const Point3d& point, const Quaternion3d& quaternion) :
        _point(point),
        _rotationMatrix(quaternion.rotationMatrix()) {
    }

    inline
    const Point3d&
    Rotation3d::point() const {
        return _point;
    }

    inline
    const Matrix<double, 3, 3>&
    Rotation3d::rotationMatrix() const {
        return _rotationMatrix;
    }

    inline
    double
    Rotation3d::scale() const {
        return 1.0;
    }

    inline
    Handedness
    Rotation3d::transform(Handedness handedness) const {
        return handedness;
    }

    inline
    Point3d
    Rotation3d::transform(const Point3d& point) const {
        return this->point() + transform(point - this->point());
    }

    template <class TParameter>
    inline
    ParametricExpression<Point3d, TParameter>
    Rotation3d::transform(const ParametricExpression<Point3d, TParameter>& expression) const {
        return point() + transform(expression - point());
    }

    inline
    Vector<double, 3>
    Rotation3d::transform(const Vector3d& vector) const {
        return Vector3d(rotationMatrix() * vector.components());
    }

    template <class TParameter>
    inline
    ParametricExpression<Vector3d, TParameter>
    Rotation3d::transform(const ParametricExpression<Vector3d, TParameter>& expression) const {
        return rotationMatrix() * expression.implementation();
    }

    inline
    UnitVector3d
    Rotation3d::transform(const UnitVector3d& unitVector) const {
        return UnitVector3d(rotationMatrix() * unitVector.components());
    }

    template <class TParameter>
    inline
    ParametricExpression<UnitVector3d, TParameter>
    Rotation3d::transform(const ParametricExpression<UnitVector3d, TParameter>& expression) const {
        return rotationMatrix() * expression.implementation();
    }
}
