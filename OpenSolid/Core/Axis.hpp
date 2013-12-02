/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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

#include <OpenSolid/Core/CoordinateSystem.definitions.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.hpp>
#include <OpenSolid/Core/Point.hpp>

namespace opensolid
{
    inline
    Axis2d::Axis() :
        _originPoint(Point2d::Origin()),
        _directionVector(Vector2d::Zero()) {
    }

    inline
    Axis2d::Axis(
        const Point2d& originPoint,
        const Vector2d& directionVector
    ) : _originPoint(originPoint),
        _directionVector(directionVector) {

        assert(directionVector.squaredNorm() - 1.0 == Zero());
    }

    inline
    const Point2d&
    Axis2d::originPoint() const {
        return _originPoint;
    }
    
    inline
    const Vector2d&
    Axis2d::directionVector() const {
        return _directionVector;
    }

    inline
    Axis2d
    Axis2d::flipped() const {
        return Axis2d(originPoint(), -directionVector());
    }

    inline
    Axis2d
    Axis2d::normalAxis() const {
        return Axis2d(originPoint(), directionVector().unitOrthogonal());
    }

    inline
    AxialCoordinateSystem2d
    Axis2d::coordinateSystem() const {
        return AxialCoordinateSystem2d(originPoint(), directionVector());
    }

    inline
    Axis2d
    Axis2d::X() {
        return Axis2d(Point2d::Origin(), Vector2d::UnitX());
    }

    inline
    Axis2d
    Axis2d::Y() {
        return Axis2d(Point2d::Origin(), Vector2d::UnitY());
    }

    inline
    Axis3d::Axis() :
        _originPoint(Point3d::Origin()),
        _directionVector(Vector3d::Zero()) {
    }

    inline
    Axis3d::Axis(
        const Point3d& originPoint,
        const Vector3d& directionVector
    ) : _originPoint(originPoint),
        _directionVector(directionVector) {

        assert(directionVector.squaredNorm() - 1.0 == Zero());
    }

    inline
    const Point3d&
    Axis3d::originPoint() const {
        return _originPoint;
    }
    
    inline
    const Vector3d&
    Axis3d::directionVector() const {
        return _directionVector;
    }

    inline
    Axis3d
    Axis3d::flipped() const {
        return Axis3d(originPoint(), -directionVector());
    }

    inline
    Plane3d
    Axis3d::normalPlane() const {
        return Plane3d(originPoint(), directionVector());
    }

    inline
    AxialCoordinateSystem3d
    Axis3d::coordinateSystem() const {
        return AxialCoordinateSystem3d(originPoint(), directionVector());
    }

    inline
    Axis3d
    Axis3d::X() {
        return Axis3d(Point3d::Origin(), Vector3d::UnitX());
    }

    inline
    Axis3d
    Axis3d::Y() {
        return Axis3d(Point3d::Origin(), Vector3d::UnitY());
    }

    inline
    Axis3d
    Axis3d::Z() {
        return Axis3d(Point3d::Origin(), Vector3d::UnitZ());
    }

    template <int iNumDimensions>
    Axis<iNumDimensions>
    ScalingFunction<Axis<iNumDimensions>>::operator()(
        const Axis<iNumDimensions>& axis,
        double scale
    ) const {
        double directionScale = scale >= 0.0 ? 1.0 : -1.0;
        return Axis<iNumDimensions>(
            detail::scaled(axis.originPoint(), scale),
            directionScale * axis.directionVector()
        );
    }

    template <int iNumDimensions> template <class TVector>
    Axis<iNumDimensions>
    TranslationFunction<Axis<iNumDimensions>>::operator()(
        const Axis<iNumDimensions>& axis,
        const EigenBase<TVector>& vector
    ) const {
        return Axis<iNumDimensions>(axis.originPoint() + vector.derived(), axis.directionVector());
    }

    template <int iNumDimensions, int iNumResultDimensions> template <class TMatrix>
    Axis<iNumResultDimensions>
    TransformationFunction<Axis<iNumDimensions>, iNumResultDimensions>::operator()(
        const Axis<iNumDimensions>& axis,
        const EigenBase<TMatrix>& matrix
    ) const {
        Matrix<double, iNumResultDimensions, 1> transformedDirection =
            matrix.derived() * axis.directionVector();
        double transformedNorm = transformedDirection.norm();
        if (transformedNorm == Zero()) {
            throw PlaceholderError();
        }
        transformedDirection *= (1.0 / transformedNorm);
        return Axis<iNumResultDimensions>(
            detail::transformed(axis.originPoint(), matrix.derived()),
            transformedDirection
        );
    }

    template <int iNumDimensions, int iNumResultDimensions>
    Axis<iNumResultDimensions>
    MorphingFunction<Axis<iNumDimensions>, iNumResultDimensions>::operator()(
        const Axis<iNumDimensions>& axis,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        Matrix<double, iNumResultDimensions, 1> morphedDirection =
            morphingExpression.jacobian(axis.originPoint().vector()) * axis.directionVector();
        double morphedNorm = morphedDirection.norm();
        if (morphedNorm == Zero()) {
            throw PlaceholderError();
        }
        morphedDirection *= (1.0 / morphedNorm);
        return Axis<iNumResultDimensions>(
            detail::morphed(axis.originPoint(), morphingExpression),
            morphedDirection
        );
    }
}
