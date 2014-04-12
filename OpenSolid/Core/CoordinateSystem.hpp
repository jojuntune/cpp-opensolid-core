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

#include <OpenSolid/Core/CoordinateSystem.definitions.hpp>

#include <OpenSolid/Core/Axis.definitions.hpp>
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Plane.definitions.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>

#include <iostream>

namespace opensolid
{
    namespace detail
    {
        template <int iNumAxes, int iNumDimensions>
        Matrix<double, iNumAxes, iNumDimensions>
        computeInverseMatrix(const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix) {
            Matrix<double, iNumAxes, iNumDimensions> transpose = basisMatrix.transpose();
            return (transpose * basisMatrix).inverse() * transpose;
        }
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    CoordinateSystem<iNumDimensions, iNumAxes>::CoordinateSystem() :
        _originPoint(Point<iNumDimensions>::Origin()) {

        _basisMatrix.setIdentity();
        _inverseMatrix.setIdentity();
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    CoordinateSystem<iNumDimensions, iNumAxes>::CoordinateSystem(
        const Point<iNumDimensions>& originPoint
    ) : _originPoint(originPoint) {

        _basisMatrix.setIdentity();
        _inverseMatrix.setIdentity();
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    CoordinateSystem<iNumDimensions, iNumAxes>::CoordinateSystem(
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
    ) : _originPoint(originPoint),
        _basisMatrix(basisMatrix),
        _inverseMatrix(detail::computeInverseMatrix(basisMatrix)) {
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    CoordinateSystem<iNumDimensions, iNumAxes>::CoordinateSystem(
        const Point<iNumDimensions>& originPoint,
        const Vector<double, iNumDimensions>& basisVector
    ) : _originPoint(originPoint),
        _basisMatrix(basisVector.components()),
        _inverseMatrix(detail::computeInverseMatrix(basisVector.components())) {
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    CoordinateSystem<iNumDimensions, iNumAxes>::CoordinateSystem(
        const Point<iNumDimensions>& originPoint,
        const Vector<double, iNumDimensions>& xBasisVector,
        const Vector<double, iNumDimensions>& yBasisVector
    ) : _originPoint(originPoint) {

        static_assert(
            iNumAxes == 2,
            "2 basis vectors supplied but number of axes does not equal 2"
        );

        _basisMatrix.col(0) = xBasisVector.components();
        _basisMatrix.col(1) = yBasisVector.components();
        _inverseMatrix = detail::computeInverseMatrix(_basisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    CoordinateSystem<iNumDimensions, iNumAxes>::CoordinateSystem(
        const Point<iNumDimensions>& originPoint,
        const Vector<double, iNumDimensions>& xBasisVector,
        const Vector<double, iNumDimensions>& yBasisVector,
        const Vector<double, iNumDimensions>& zBasisVector
    ) : _originPoint(originPoint) {

        static_assert(
            iNumAxes == 3,
            "3 basis vectors supplied but number of axes does not equal 3"
        );

        _basisMatrix.col(0) = xBasisVector.components();
        _basisMatrix.col(1) = yBasisVector.components();
        _basisMatrix.col(2) = zBasisVector.components();
        _inverseMatrix = detail::computeInverseMatrix(_basisMatrix);
    }
        
    template <int iNumDimensions, int iNumAxes>
    inline
    const Point<iNumDimensions>&
    CoordinateSystem<iNumDimensions, iNumAxes>::originPoint() const {
        return _originPoint;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Matrix<double, iNumDimensions, iNumAxes>&
    CoordinateSystem<iNumDimensions, iNumAxes>::basisMatrix() const {
        return _basisMatrix;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Vector<double, iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::basisVector() const {
        static_assert(
            iNumAxes == 1,
            "Only axial coordinate systems have a single basis vector"
        );

        return Vector<double, iNumDimensions>(basisMatrix());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Matrix<double, iNumAxes, iNumDimensions>&
    CoordinateSystem<iNumDimensions, iNumAxes>::inverseMatrix() const {
        return _inverseMatrix;
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Point<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::point(double value) const {
        static_assert(
            iNumAxes == 1,
            "1 point coordinate supplied but number of axes does not equal 1"
        );

        return (*this) * Point1d(value);
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Point<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::point(double x, double y) const {
        static_assert(
            iNumAxes == 2,
            "2 point coordinates supplied but number of axes does not equal 2"
        );

        return (*this) * Point2d(x, y);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Point<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::point(double x, double y, double z) const {
        static_assert(
            iNumAxes == 3,
            "3 point coordinates supplied but number of axes does not equal 3"
        );

        return (*this) * Point3d(x, y, z);
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Vector<double, iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::vector(double value) const {
        static_assert(
            iNumAxes == 1,
            "1 vector coordinate supplied but number of axes does not equal 1"
        );

        return (*this) * Vector1d(value);
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Vector<double, iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::vector(double x, double y) const {
        static_assert(
            iNumAxes == 2,
            "2 vector coordinates supplied but number of axes does not equal 2"
        );

        return (*this) * Vector2d(x, y);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Vector<double, iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::vector(double x, double y, double z) const {
        static_assert(
            iNumAxes == 3,
            "3 vector coordinates supplied but number of axes does not equal 3"
        );

        return (*this) * Vector3d(x, y, z);
    }

    template<int iNumDimensions, int iNumAxes>
    inline
    const Vector<double, iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::xBasisVector() const {
        return Vector<double, iNumDimensions>(basisMatrix().col(0));
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Vector<double, iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::yBasisVector() const {
        static_assert(
            iNumAxes >= 2,
            "Coordinate system must have at least two axes to have a Y basis vector"
        );

        return Vector<double, iNumDimensions>(basisMatrix().col(1));
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Vector<double, iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::zBasisVector() const {
        static_assert(
            iNumAxes >= 3,
            "Coordinate system must have at least three axes to have a Z basis vector"
        );

        return Vector<double, iNumDimensions>(basisMatrix().col(2));
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Vector<double, iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::basisVector(std::int64_t axisIndex ) const {
        if (axisIndex < 0 || axisIndex >= iNumAxes) {
            throw Error(new PlaceholderError());
        }

        return Vector<double, iNumDimensions>(basisMatrix().col(axisIndex));
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Axis<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::xAxis() const {
        return Axis<iNumDimensions>(originPoint(), xBasisVector().normalized());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Axis<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::yAxis() const {
        static_assert(
            iNumAxes >= 2,
            "Coordinate system must have at least two axes to have a Y axis"
        );

        return Axis<iNumDimensions>(originPoint(), yBasisVector().normalized());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Axis<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::zAxis() const {
        static_assert(
            iNumAxes >= 3,
            "Coordinate system must have at least three axes to have a Z axis"
        );

        return Axis<iNumDimensions>(originPoint(), zBasisVector().normalized());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline
    const Axis<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::axis(std::int64_t axisIndex) const {
        if (axisIndex < 0 || axisIndex >= iNumAxes) {
            throw Error(new PlaceholderError());
        }

        return Axis<iNumDimensions>(originPoint(), basisVector(axisIndex).normalized());
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::xyPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "XY plane requested for non-3D coordinate system"
        );

        return Plane3d(originPoint(), xBasisVector().cross(yBasisVector()).normalized());
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::xzPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "XZ plane requested for non-3D coordinate system"
        );

        return Plane3d(originPoint(), xBasisVector().cross(zBasisVector()).normalized());
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::yxPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "YX plane requested for non-3D coordinate system"
        );

        return Plane3d(originPoint(), yBasisVector().cross(xBasisVector()).normalized());
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::yzPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "YZ plane requested for non-3D coordinate system"
        );

        return Plane3d(originPoint(), yBasisVector().cross(zBasisVector()).normalized());
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::zxPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "ZX plane requested for non-3D coordinate system"
        );

        return Plane3d(originPoint(), zBasisVector().cross(xBasisVector()).normalized());
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::zyPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "ZY plane requested for non-3D coordinate system"
        );

        return Plane3d(originPoint(), zBasisVector().cross(yBasisVector()).normalized());
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::plane(
        std::int64_t firstAxisIndex,
        std::int64_t secondAxisIndex
    ) const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "Component plane requested for non-3D coordinate system"
        );

        if (firstAxisIndex < 0 || firstAxisIndex > 2) {
            throw Error(new PlaceholderError());
        }
        if (secondAxisIndex < 0 || secondAxisIndex > 2) {
            throw Error(new PlaceholderError());
        }
        if (firstAxisIndex == secondAxisIndex) {
            throw Error(new PlaceholderError());
        }

        Vector3d normalVector = basisVector(firstAxisIndex).cross(basisVector(secondAxisIndex));
        return Plane3d(originPoint(), normalVector.normalized());
    }

    template <int iNumDimensions, int iNumAxes>
    const CoordinateSystem<iNumDimensions, iNumAxes>
    CoordinateSystem<iNumDimensions, iNumAxes>::normalized() const {
        Matrix<double, iNumDimensions, iNumAxes> resultBasisMatrix = basisMatrix();
        for (std::int64_t columnIndex = 0; columnIndex < iNumAxes; ++columnIndex) {
            Vector<double, iNumDimensions> resultBasisVector(basisMatrix().col(columnIndex));
            for (
                std::int64_t normalizedColumnIndex = 0;
                normalizedColumnIndex < columnIndex;
                ++normalizedColumnIndex
            ) {
                Vector<double, iNumDimensions> normalizedBasisVector(
                    resultBasisMatrix.col(normalizedColumnIndex)
                );
                resultBasisVector = resultBasisVector -
                    resultBasisVector.dot(normalizedBasisVector) * normalizedBasisVector;
            }
            if (resultBasisVector.isZero()) {
                // Cannot normalize: basis matrix does not have full rank
                throw Error(new PlaceholderError());
            } else {
                resultBasisVector = resultBasisVector.normalized();
            }
            resultBasisMatrix.col(columnIndex) = resultBasisVector.components();
        }
        return CoordinateSystem<iNumDimensions, iNumAxes>(originPoint(), resultBasisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const CoordinateSystem<iNumDimensions, iNumAxes>
    CoordinateSystem<iNumDimensions, iNumAxes>::Global() {
        static_assert(
            iNumDimensions == iNumAxes,
            "Global coordinate system always has equal number of dimensions and axes"
        );
        
        return CoordinateSystem(
            Point<iNumDimensions>::Origin(),
            Matrix<double, iNumDimensions, iNumAxes>::Identity()
        );
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const CoordinateSystem<iNumDimensions, iNumAxes>
    ScalingFunction<CoordinateSystem<iNumDimensions, iNumAxes>>::operator()(
        const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
        double scale
    ) const {
        return CoordinateSystem<iNumDimensions, iNumAxes>(
            scalingFunction(coordinateSystem.originPoint(), scale),
            scale * coordinateSystem.basisMatrix()
        );
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    const CoordinateSystem<iNumDimensions, iNumAxes>
    TranslationFunction<CoordinateSystem<iNumDimensions, iNumAxes>>::operator()(
        const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
        const Vector<double, iNumDimensions>& vector
    ) const {
        return CoordinateSystem<iNumDimensions, iNumAxes>(
            translationFunction(coordinateSystem.originPoint(), vector),
            coordinateSystem.basisMatrix()
        );
    }

    template <int iNumDimensions, int iNumAxes, int iNumResultDimensions>
    const CoordinateSystem<iNumResultDimensions, iNumAxes>
    TransformationFunction<
        CoordinateSystem<iNumDimensions, iNumAxes>,
        iNumResultDimensions
    >::operator()(
        const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
        const Matrix<double, iNumResultDimensions, iNumDimensions>& matrix
    ) const {
        return CoordinateSystem<iNumResultDimensions, iNumAxes>(
            transformationFunction(coordinateSystem.originPoint(), matrix),
            matrix * coordinateSystem.basisMatrix()
        );
    }

    template <int iNumDimensions, int iNumAxes, int iNumResultDimensions>
    inline
    const CoordinateSystem<iNumResultDimensions, iNumAxes>
    MorphingFunction<CoordinateSystem<iNumDimensions, iNumAxes>, iNumResultDimensions>::operator()(
        const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
        const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
    ) const {
        return CoordinateSystem<iNumResultDimensions, iNumAxes>(
            morphingFunction(coordinateSystem.originPoint(), morphingExpression),
            morphingExpression.jacobian(coordinateSystem.originPoint().components()) *
                coordinateSystem.basisMatrix()
        );
    }
}
