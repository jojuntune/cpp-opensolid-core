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

#include <OpenSolid/Core/Transformable.definitions.hpp>

#include <OpenSolid/Core/Axis.hpp>
#include <OpenSolid/Core/Globalization.hpp>
#include <OpenSolid/Core/Localization.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Mirror.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Quaternion.hpp>
#include <OpenSolid/Core/Rotation.hpp>
#include <OpenSolid/Core/Scaling.hpp>
#include <OpenSolid/Core/Translation.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{
    template <class TDerived>
    inline
    const TDerived&
    Transformable<TDerived, Vector2d>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector2d>::rotatedBy(double angle) const {
        return derived().transformedBy(Rotation2d(Point2d(), angle));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector2d>::rotatedBy(const Quaternion2d& quaternion) const {
        return derived().transformedBy(Rotation2d(Point2d(), quaternion));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector2d>::rotatedBy(const Matrix2d& rotationMatrix) const {
        return derived().transformedBy(Rotation2d(Point2d(), rotationMatrix));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector2d>::relativeTo(const Frame2d& frame) const {
        return derived().transformedBy(Localization2d(frame2d));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector2d>::placedIn(const Frame2d& frame) const {
        return derived().transformedBy(Globalization2d(frame));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector2d>::mirroredAlong(const UnitVector2d& mirrorDirection) const {
        return derived().transformedBy(Mirror2d(Point2d(), mirrorDirection));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector2d>::mirroredAbout(const Axis2d& axis) const {
        return derived().transformedBy(Mirror2d(axis));
    }

    template <class TDerived>
    inline
    const TDerived&
    Transformable<TDerived, Vector3d>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector3d>::rotatedBy(const Quaternion3d& quaternion) const {
        return derived().transformedBy(Rotation3d(Point3d(), quaternion));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector3d>::rotatedBy(const Matrix3d& rotationMatrix) const {
        return derived().transformedBy(Rotation3d(Point3d(), rotationMatrix)); 
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector3d>::rotatedAbout(
        const UnitVector3d& axisDirection,
        double angle
    ) const {
        return derived().transformedBy(Rotation3d(Axis3d(Point3d(), axisDirection), angle)); 
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector3d>::rotatedAbout(const Axis3d& axis, double angle) const {
        return derived().transformedBy(Rotation3d(axis, angle)); 
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector3d>::relativeTo(const Frame3d& frame) const {
        return derived().transformedBy(Localization3d(frame)); 
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector3d>::placedIn(const Frame3d& frame) const {
        return derived().transformedBy(Globalization3d(frame)); 
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector3d>::mirroredAlong(const UnitVector3d& mirrorDirection) const {
        return derived().transformedBy(Mirror3d(Point3d(), mirrorDirection)); 
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Vector3d>::mirroredAbout(const Plane3d& plane) const {
        return derived().transformedBy(Mirror3d(plane)); 
    }

    template <class TDerived>
    inline
    const TDerived&
    Transformable<TDerived, Point2d>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point2d>::scaledAbout(const Point2d& point, double scale) const {
        return derived().transformedBy(Scaling2d(point, scale));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point2d>::rotatedAbout(const Point2d& point, double angle) const {
        return derived().transformedBy(Rotation2d(point, angle));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point2d>::rotatedAbout(
        const Point2d& point,
        const Quaternion2d& quaternion
    ) const {
        return derived().transformedBy(Rotation2d(point, quaternion));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point2d>::rotatedAbout(
        const Point2d& point,
        const Matrix2d& rotationMatrix
    ) const {
        return derived().transformedBy(Rotation2d(point, rotationMatrix));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point2d>::translatedBy(const Vector2d& vector) const {
        return derived().transformedBy(Translation2d(vector));
    }
    
    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point2d>::translatedAlong(const Axis2d& axis, double distance) const {
        return derived().transformedBy(Translation2d(distance * axis.directionVector()));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point2d>::relativeTo(const Frame2d& frame) const {
        return derived().transformedBy(Localization2d(frame));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point2d>::placedIn(const Frame2d& frame) const {
        return derived().transformedBy(Globalization2d(frame));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point2d>::mirroredAbout(
        const Point2d& point,
        const UnitVector2d& mirrorDirection
    ) const {
        return derived().transformedBy(Mirror2d(point, mirrorDirection));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point2d>::mirroredAbout(const Axis2d& axis) const {
        return derived().transformedBy(Mirror2d(axis));
    }

    template <class TDerived>
    inline
    const TDerived&
    Transformable<TDerived, Point3d>::derived() const {
        return static_cast<const TDerived&>(*this);
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point3d>::scaledAbout(const Point3d& point, double scale) const {
        return derived().transformedBy(Scaling3d(point, scale));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point3d>::rotatedAbout(const Axis3d& axis, double angle) const {
        return derived().transformedBy(Rotation3d(axis, angle));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point3d>::rotatedAbout(
        const Point3d& point,
        const Quaternion3d& quaternion
    ) const {
        return derived().transformedBy(Rotation3d(point, quaternion));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point3d>::rotatedAbout(
        const Point3d& point,
        const Matrix3d& rotationMatrix
    ) const {
        return derived().transformedBy(Rotation3d(point, rotationMatrix));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point3d>::translatedBy(const Vector3d& vector) const {
        return derived().transformedBy(Translation3d(vector));
    }
    
    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point3d>::translatedAlong(const Axis3d& axis, double distance) const {
        return derived().transformedBy(Translation3d(distance * axis.directionVector()));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point3d>::relativeTo(const Frame3d& frame) const {
        return derived().transformedBy(Localization3d(frame));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point3d>::placedIn(const Frame3d& frame) const {
        return derived().transformedBy(Globalization3d(frame));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point3d>::mirroredAbout(
        const Point3d& point,
        const UnitVector3d& mirrorDirection
    ) const {
        return derived().transformedBy(Mirror3d(point, mirrorDirection));
    }

    template <class TDerived>
    inline
    TDerived
    Transformable<TDerived, Point3d>::mirroredAbout(const Plane3d& plane) const {
        return derived().transformedBy(Mirror3d(plane));
    }
}
