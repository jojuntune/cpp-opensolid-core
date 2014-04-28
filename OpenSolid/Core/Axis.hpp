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
        _originPoint(Point2d::Origin()),
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
    Axis2d::X() {
        return Axis2d(Point2d::Origin(), UnitVector2d::X());
    }

    inline
    const Axis2d
    Axis2d::Y() {
        return Axis2d(Point2d::Origin(), UnitVector2d::Y());
    }

    inline
    Axis3d::Axis() :
        _originPoint(Point3d::Origin()),
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
    Axis3d::X() {
        return Axis3d(Point3d::Origin(), UnitVector3d::X());
    }

    inline
    const Axis3d
    Axis3d::Y() {
        return Axis3d(Point3d::Origin(), UnitVector3d::Y());
    }

    inline
    const Axis3d
    Axis3d::Z() {
        return Axis3d(Point3d::Origin(), UnitVector3d::Z());
    }

    template <int iNumDimensions>
    inline
    const Axis<iNumDimensions>
    ScalingFunction<Axis<iNumDimensions>>::operator()(
        const Axis<iNumDimensions>& axis,
        double scale
    ) const {
        return Axis<iNumDimensions>(
            scalingFunction(axis.originPoint(), scale),
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
            translationFunction(axis.originPoint(), vector),
            axis.directionVector()
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    const Axis<iNumResultDimensions>
    TransformationFunction<Axis<iNumDimensions>, iNumResultDimensions>::operator()(
        const Axis<iNumDimensions>& axis,
        const Matrix<double, iNumResultDimensions, iNumDimensions>& matrix
    ) const {
        Vector<double, iNumResultDimensions> transformedDirection = transformationFunction(
            axis.directionVector(),
            matrix
        );
        double transformedNorm = transformedDirection.norm();
        if (transformedNorm == Zero()) {
            throw PlaceholderError();
        }
        transformedDirection *= (1.0 / transformedNorm);
        return Axis<iNumResultDimensions>(
            transformationFunction(axis.originPoint(), matrix),
            UnitVector<iNumResultDimensions>(transformedDirection)
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    const Axis<iNumResultDimensions>
    MorphingFunction<Axis<iNumDimensions>, iNumResultDimensions>::operator()(
        const Axis<iNumDimensions>& axis,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        Vector<double, iNumResultDimensions> morphedDirection = transformationFunction(
            axis.directionVector(),
            morphingExpression.jacobian(axis.originPoint().components())
        );
        double morphedNorm = morphedDirection.norm();
        if (morphedNorm == Zero()) {
            throw PlaceholderError();
        }
        morphedDirection *= (1.0 / morphedNorm);
        return Axis<iNumResultDimensions>(
            morphingFunction(axis.originPoint(), morphingExpression),
            UnitVector<iNumResultDimensions>(morphedDirection)
        );
    }
}
