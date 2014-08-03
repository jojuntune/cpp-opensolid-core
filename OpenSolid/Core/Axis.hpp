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
#include <OpenSolid/Core/CoordinateSystem.definitions.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.definitions.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/UnitVector.hpp>
#include <OpenSolid/Core/Zero.hpp>

namespace opensolid
{
    inline
    Axis2d::Axis() :
        _originPoint(Point2d::origin()),
        _directionVector(UnitVector2d()) {
    }

    inline
    Axis2d::Axis(
        const Point2d& originPoint,
        const UnitVector2d& directionVector
    ) : _originPoint(originPoint),
        _directionVector(directionVector) {
    }

    inline
    const Point2d&
    Axis2d::originPoint() const {
        return _originPoint;
    }
    
    inline
    const UnitVector2d&
    Axis2d::directionVector() const {
        return _directionVector;
    }

    inline
    const UnitVector2d
    Axis2d::normalVector() const {
        return directionVector().unitOrthogonal();
    }

    inline
    const Axis2d
    Axis2d::flipped() const {
        return Axis2d(originPoint(), -directionVector());
    }

    inline
    const Axis2d
    Axis2d::normalAxis() const {
        return Axis2d(originPoint(), normalVector());
    }

    inline
    const AxialCoordinateSystem2d
    Axis2d::coordinateSystem() const {
        return AxialCoordinateSystem2d(originPoint(), directionVector());
    }

    inline
    const Axis2d
    Axis2d::x() {
        return Axis2d(Point2d::origin(), Vector2d::unitX());
    }

    inline
    const Axis2d
    Axis2d::y() {
        return Axis2d(Point2d::origin(), Vector2d::unitY());
    }
    
    inline
    bool
    Axis2d::contains(const Point2d& point, double precision) const {
        return (point - originPoint()).dot(normalVector()) == Zero(precision);
    }

    inline
    Axis3d::Axis() :
        _originPoint(Point3d::origin()),
        _directionVector(UnitVector3d()) {
    }

    inline
    Axis3d::Axis(
        const Point3d& originPoint,
        const UnitVector3d& directionVector
    ) : _originPoint(originPoint),
        _directionVector(directionVector) {
    }

    inline
    const Point3d&
    Axis3d::originPoint() const {
        return _originPoint;
    }
    
    inline
    const UnitVector3d&
    Axis3d::directionVector() const {
        return _directionVector;
    }

    inline
    const Axis3d
    Axis3d::flipped() const {
        return Axis3d(originPoint(), -directionVector());
    }

    inline
    const Plane3d
    Axis3d::normalPlane() const {
        return Plane3d(originPoint(), directionVector());
    }

    inline
    const AxialCoordinateSystem3d
    Axis3d::coordinateSystem() const {
        return AxialCoordinateSystem3d(originPoint(), directionVector());
    }

    inline
    const Intersection<Axis3d, Plane3d>
    Axis3d::intersection(const Plane3d& plane, double precision) const {
        return Intersection<Axis3d, Plane3d>(*this, plane, precision);
    }

    inline
    const Intersection<Axis3d, Triangle<3>>
    Axis3d::intersection(const Triangle<3>& triangle, double precision) const {
        return Intersection<Axis3d, Triangle<3>>(*this, triangle, precision);
    }

    inline
    const Axis3d
    Axis3d::x() {
        return Axis3d(Point3d::origin(), Vector3d::unitX());
    }

    inline
    const Axis3d
    Axis3d::y() {
        return Axis3d(Point3d::origin(), Vector3d::unitY());
    }

    inline
    const Axis3d
    Axis3d::z() {
        return Axis3d(Point3d::origin(), Vector3d::unitZ());
    }
    
    inline
    bool
    Axis3d::contains(const Point3d& point, double precision) const {
        return point.squaredDistanceTo(*this) == Zero(precision * precision);
    }

    template <int iNumDimensions>
    inline
    const Axis<iNumDimensions>
    ScalingFunction<Axis<iNumDimensions>>::operator()(
        const Axis<iNumDimensions>& axis,
        const Point<iNumDimensions>& originPoint,
        double scale
    ) const {
        return Axis<iNumDimensions>(
            scaled(axis.originPoint(), originPoint, scale),
            scale >= 0.0 ? axis.directionVector() : -axis.directionVector()
        );
    }

    template <int iNumDimensions>
    inline
    const Axis<iNumDimensions>
    TranslationFunction<Axis<iNumDimensions>>::operator()(
        const Axis<iNumDimensions>& axis,
        const Vector<double, iNumDimensions>& vector
    ) const {
        return Axis<iNumDimensions>(
            translated(axis.originPoint(), vector),
            axis.directionVector()
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    const Axis<iNumResultDimensions>
    TransformationFunction<Axis<iNumDimensions>, iNumResultDimensions>::operator()(
        const Axis<iNumDimensions>& axis,
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumResultDimensions, iNumDimensions>& transformationMatrix,
        const Point<iNumResultDimensions>& destinationPoint
    ) const {
        Vector<double, iNumResultDimensions> transformedDirection = transformed(
            axis.directionVector(),
            originPoint,
            transformationMatrix,
            destinationPoint
        );
        double transformedNorm = transformedDirection.norm();
        if (transformedNorm == Zero()) {
            throw PlaceholderError();
        }
        transformedDirection *= (1.0 / transformedNorm);
        return Axis<iNumResultDimensions>(
            transformed(axis.originPoint(), originPoint, transformationMatrix, destinationPoint),
            UnitVector<iNumResultDimensions>(transformedDirection)
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    const Axis<iNumResultDimensions>
    MorphingFunction<
        Axis<iNumDimensions>,
        ParametricExpression<Point<iNumResultDimensions>, Point<iNumDimensions>>
    >::operator()(
        const Axis<iNumDimensions>& axis,
        const ParametricExpression<
            Point<iNumResultDimensions>,
            Point<iNumDimensions>
        >& morphingExpression
    ) const {
        Vector<double, iNumResultDimensions> morphedDirection(
            morphingExpression.jacobian(axis.originPoint()) * axis.directionVector().components()
        );
        double morphedNorm = morphedDirection.norm();
        if (morphedNorm == Zero()) {
            throw PlaceholderError();
        }
        morphedDirection *= (1.0 / morphedNorm);
        return Axis<iNumResultDimensions>(
            morphingExpression.evaluate(axis.originPoint()),
            UnitVector<iNumResultDimensions>(morphedDirection)
        );
    }
}
