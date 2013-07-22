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
*************************************************************************************/

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

namespace opensolid
{
    namespace detail
    {
        template <class TDerived>
        Matrix<double, TDerived::ColsAtCompileTime, TDerived::RowsAtCompileTime>
        computeInverseMatrix(const EigenBase<TDerived>& basisMatrix) {
            return (basisMatrix.derived().transpose() * basisMatrix.derived()).inverse() *
                basisMatrix.derived().transpose();
        }
    }

    template <int iNumDimensions, int iNumAxes>
    inline
    CoordinateSystem<iNumDimensions, iNumAxes>::CoordinateSystem() :
        _originPoint( Point<iNumDimensions>::Origin() ) {

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
    inline CoordinateSystem<iNumDimensions, iNumAxes>::CoordinateSystem(
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
    ) : _originPoint(originPoint),
        _basisMatrix(basisMatrix),
        _inverseMatrix(detail::computeInverseMatrix(basisMatrix)) {
    }

    template <int iNumDimensions, int iNumAxes>
    CoordinateSystem<iNumDimensions, iNumAxes>::CoordinateSystem(
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumDimensions, 1>& xBasisVector,
        const Matrix<double, iNumDimensions, 1>& yBasisVector
    ) : _originPoint(originPoint) {

        static_assert(
            iNumAxes == 2,
            "2 basis vectors supplied but number of axes does not equal 2"
        );
        _basisMatrix << xBasisVector, yBasisVector;
        _inverseMatrix = detail::computeInverseMatrix(_basisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    CoordinateSystem<iNumDimensions, iNumAxes>::CoordinateSystem(
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumDimensions, 1>& xBasisVector,
        const Matrix<double, iNumDimensions, 1>& yBasisVector,
        const Matrix<double, iNumDimensions, 1>& zBasisVector
    ) : _originPoint(originPoint) {

        static_assert(
            iNumAxes == 3,
            "3 basis vectors supplied but number of axes does not equal 3"
        );
        _basisMatrix << xBasisVector, yBasisVector, zBasisVector;
        _inverseMatrix = detail::computeInverseMatrix(_basisMatrix);
    }
        
    template <int iNumDimensions, int iNumAxes>
    inline const Point<iNumDimensions>&
    CoordinateSystem<iNumDimensions, iNumAxes>::originPoint() const {
        return _originPoint;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumDimensions, iNumAxes>&
    CoordinateSystem<iNumDimensions, iNumAxes>::basisMatrix() const {
        return _basisMatrix;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumDimensions, iNumAxes>&
    CoordinateSystem<iNumDimensions, iNumAxes>::basisVector() const {
        static_assert(
            iNumAxes == 1,
            "Only axial coordinate systems have a single basis vector"
        );
        return basisMatrix();
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumAxes, iNumDimensions>&
    CoordinateSystem<iNumDimensions, iNumAxes>::inverseMatrix() const {
        return _inverseMatrix;
    }

    template <int iNumDimensions, int iNumAxes>
    inline Point<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::point(double x) const {
        static_assert(
            iNumAxes == 1,
            "1 point coordinate supplied but number of axes does not equal 1"
        );
        return originPoint() + basisVector() * x;
    }

    template <int iNumDimensions, int iNumAxes>
    inline Point<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::point(double x, double y) const {
        static_assert(
            iNumAxes == 2,
            "2 point coordinates supplied but number of axes does not equal 2"
        );
        return originPoint() + basisMatrix() * Vector2d(x, y);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Point<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::point(double x, double y, double z) const {
        static_assert(
            iNumAxes == 3,
            "3 point coordinates supplied but number of axes does not equal 3"
        );
        return originPoint() + basisMatrix() * Vector3d(x, y, z);
    }

    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1>
    CoordinateSystem<iNumDimensions, iNumAxes>::vector(double x) const {
        static_assert(
            iNumAxes == 1,
            "1 vector coordinate supplied but number of axes does not equal 1"
        );
        return basisVector() * x;
    }

    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1>
    CoordinateSystem<iNumDimensions, iNumAxes>::vector(double x, double y) const {
        static_assert(
            iNumAxes == 2,
            "2 vector coordinates supplied but number of axes does not equal 2"
        );
        return basisMatrix() * Vector2d(x, y);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1>
    CoordinateSystem<iNumDimensions, iNumAxes>::vector(double x, double y, double z) const {
        static_assert(
            iNumAxes == 3,
            "3 vector coordinates supplied but number of axes does not equal 3"
        );
        return basisMatrix() * Vector3d(x, y, z);
    }

    template<int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    CoordinateSystem<iNumDimensions, iNumAxes>::xBasisVector() const {
        return basisMatrix().col(0);
    }

    template <int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    CoordinateSystem<iNumDimensions, iNumAxes>::yBasisVector() const {
        static_assert(
            iNumAxes >= 2,
            "Coordinate system must have at least two axes to have a Y basis vector"
        );
        return basisMatrix().col(1);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    CoordinateSystem<iNumDimensions, iNumAxes>::zBasisVector() const {
        static_assert(
            iNumAxes >= 3,
            "Coordinate system must have at least three axes to have a Z basis vector"
        );
        return basisMatrix().col(2);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    CoordinateSystem<iNumDimensions, iNumAxes>::basisVector(int axisIndex ) const {
        if (axisIndex < 0 || axisIndex >= iNumAxes) {
            throw PlaceholderError();
        }
        return basisMatrix().col(axisIndex);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Axis<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::xAxis() const {
        return Axis<iNumDimensions>(originPoint(), xBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Axis<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::yAxis() const {
        static_assert(
            iNumAxes >= 2,
            "Coordinate system must have at least two axes to have a Y axis"
        );
        return Axis<iNumDimensions>(originPoint(), yBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Axis<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::zAxis() const {
        static_assert(
            iNumAxes >= 3,
            "Coordinate system must have at least three axes to have a Z axis"
        );
        return Axis<iNumDimensions>(originPoint(), zBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Axis<iNumDimensions>
    CoordinateSystem<iNumDimensions, iNumAxes>::axis(int axisIndex) const {
        if (axisIndex < 0 || axisIndex >= iNumAxes) {
            throw PlaceholderError();
        }
        return Axis<iNumDimensions>(originPoint(), basisVector(axisIndex));
    }

    template <int iNumDimensions, int iNumAxes>
    inline Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::xyPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "XY plane requested for non-3D coordinate system"
        );
        return Plane3d(originPoint(), xBasisVector().cross(yBasisVector()));
    }

    template <int iNumDimensions, int iNumAxes>
    inline Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::xzPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "XZ plane requested for non-3D coordinate system"
        );
        return Plane3d(originPoint(), xBasisVector().cross(zBasisVector()));
    }

    template <int iNumDimensions, int iNumAxes>
    inline Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::yxPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "YX plane requested for non-3D coordinate system"
        );
        return Plane3d(originPoint(), yBasisVector().cross(xBasisVector()));
    }

    template <int iNumDimensions, int iNumAxes>
    inline Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::yzPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "YZ plane requested for non-3D coordinate system"
        );
        return Plane3d(originPoint(), yBasisVector().cross(zBasisVector()));
    }

    template <int iNumDimensions, int iNumAxes>
    inline Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::zxPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "ZX plane requested for non-3D coordinate system"
        );
        return Plane3d(originPoint(), zBasisVector().cross(xBasisVector()));
    }

    template <int iNumDimensions, int iNumAxes>
    inline Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::zyPlane() const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "ZY plane requested for non-3D coordinate system"
        );
        return Plane3d(originPoint(), zBasisVector().cross(yBasisVector()));
    }

    template <int iNumDimensions, int iNumAxes>
    inline Plane3d
    CoordinateSystem<iNumDimensions, iNumAxes>::plane(int firstAxisIndex, int secondAxisIndex) const {
        static_assert(
            iNumDimensions == 3 && iNumAxes == 3,
            "Component plane requested for non-3D coordinate system"
        );

        if (firstAxisIndex < 0 || firstAxisIndex > 2) {
            throw PlaceholderError();
        }
        if (secondAxisIndex < 0 || secondAxisIndex > 2) {
            throw PlaceholderError();
        }
        if (firstAxisIndex == secondAxisIndex) {
            throw PlaceholderError();
        }

        Vector3d normalVector = basisVector(firstAxisIndex).cross(basisVector(secondAxisIndex));
        return Plane3d(originPoint(), normalVector);
    }

    template <int iNumDimensions, int iNumAxes>
    CoordinateSystem<iNumDimensions, iNumAxes>
    CoordinateSystem<iNumDimensions, iNumAxes>::normalized() const {
        Matrix<double, iNumDimensions, iNumAxes> resultBasisMatrix = basisMatrix();
        for (int i = 0; i < iNumAxes; ++i) {
            Matrix<double, iNumDimensions, 1> resultBasisVector = resultBasisMatrix.col(i);
            for (int j = 0; j < i; ++j) {
                Matrix<double, iNumDimensions, 1> normalizedBasisVector = resultBasisMatrix.col(j);
                resultBasisVector = resultBasisVector -
                    resultBasisVector.dot(normalizedBasisVector) * normalizedBasisVector;
            }
            if (resultBasisVector.isZero()) {
                // Cannot normalize: basis matrix does not have full rank
                throw PlaceholderError();
            } else {
                resultBasisVector = resultBasisVector.normalized();
            }
            resultBasisMatrix.col(i) = resultBasisVector;
        }
        return CoordinateSystem<iNumDimensions, iNumAxes>(originPoint(), resultBasisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    CoordinateSystem<iNumDimensions, iNumAxes>
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
    CoordinateSystem<iNumDimensions, iNumAxes>
    ScalingFunction<CoordinateSystem<iNumDimensions, iNumAxes>>::operator()(
        const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
        double scale
    ) const {
        return CoordinateSystem<iNumDimensions, iNumAxes>(
            Point<iNumDimensions>::scaling(coordinateSystem.originPoint(), scale),
            scale * coordinateSystem.basisMatrix()
        );
    }

    template <int iNumDimensions, int iNumAxes> template <class TVector>
    CoordinateSystem<iNumDimensions, iNumAxes>
    TranslationFunction<CoordinateSystem<iNumDimensions, iNumAxes>>::operator()(
        const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
        const EigenBase<TVector>& vector
    ) const {
        return CoordinateSystem<iNumDimensions, iNumAxes>(
            Point<iNumDimensions>::translation(coordinateSystem.originPoint(), vector.derived()),
            coordinateSystem.basisMatrix()
        );
    }

    template <int iNumDimensions, int iNumAxes, int iNumTransformedDimensions>
    template <class TMatrix>
    CoordinateSystem<iNumTransformedDimensions, iNumAxes>
    TransformationFunction<CoordinateSystem<iNumDimensions, iNumAxes>, iNumTransformedDimensions>::operator()(
        const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
        const EigenBase<TMatrix>& matrix
    ) const {
        return CoordinateSystem<iNumTransformedDimensions, iNumAxes>(
            Point<iNumDimensions>::transformation(coordinateSystem.originPoint(), matrix.derived()),
            matrix.derived() * coordinateSystem.basisMatrix()
        );
    }

    template <int iNumDimensions, int iNumAxes, int iNumDestinationDimensions>
    inline CoordinateSystem<iNumDestinationDimensions, iNumAxes>
    MorphingFunction<CoordinateSystem<iNumDimensions, iNumAxes>, iNumDestinationDimensions>::operator()(
        const CoordinateSystem<iNumDimensions, iNumAxes>& coordinateSystem,
        const Function<iNumDestinationDimensions, iNumDimensions>& function
    ) const {
        return CoordinateSystem<iNumDestinationDimensions, iNumAxes>(
            coordinateSystem.originPoint().morphed(function),
            function.jacobian(coordinateSystem.originPoint().vector()) *
                coordinateSystem.basisMatrix()
        );
    }
}
