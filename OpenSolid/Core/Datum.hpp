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

#include <OpenSolid/Core/Datum.definitions.hpp>

#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Function.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Point.hpp>
#include <OpenSolid/Core/Transformable.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    void
    Datum<iNumDimensions, iNumAxes>::initialize(
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
    ) {
        _originPoint = originPoint;
        _basisMatrix = basisMatrix;
        _inverseMatrix = (_basisMatrix.transpose() * _basisMatrix).inverse() *
            _basisMatrix.transpose();
    }

    template <int iNumDimensions, int iNumAxes>
    inline void
    Datum<iNumDimensions, iNumAxes>::initialize(const Datum<iNumDimensions, iNumAxes>& otherDatum) {
        _originPoint = otherDatum.originPoint();
        _basisMatrix = otherDatum.basisMatrix();
        _inverseMatrix = otherDatum.inverseMatrix();
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum() {
        _originPoint = Point<iNumDimensions>::Origin();
        _basisMatrix.setIdentity();
        _inverseMatrix.setIdentity();
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum(const Point<iNumDimensions>& originPoint) :
        _originPoint(originPoint) {

        _basisMatrix.setIdentity();
        _inverseMatrix.setIdentity();
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum(
        const Point<iNumDimensions>& originPoint,
        const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
    ) {
        initialize(originPoint, basisMatrix);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum(
        const Datum<iNumDimensions, iNumAxes>& otherDatum
    ) {
        initialize(otherDatum);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>&
    Datum<iNumDimensions, iNumAxes>::operator=(const Datum<iNumDimensions, iNumAxes>& otherDatum) {
        initialize(otherDatum);
        return *this;
    }
        
    template <int iNumDimensions, int iNumAxes>
    inline const Point<iNumDimensions>&
    Datum<iNumDimensions, iNumAxes>::originPoint() const {
        return _originPoint;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumDimensions, iNumAxes>&
    Datum<iNumDimensions, iNumAxes>::basisMatrix() const {
        return _basisMatrix;
    }
    
    template <>
    inline const Matrix1d&
    Datum<1, 1>::basisVector() const {
        return basisMatrix();
    }
    
    template <>
    inline const Vector2d&
    Datum<2, 1>::basisVector() const {
        return basisMatrix();
    }
    
    template <>
    inline const Vector3d&
    Datum<3, 1>::basisVector() const {
        return basisMatrix();
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumAxes, iNumDimensions>&
    Datum<iNumDimensions, iNumAxes>::inverseMatrix() const {
        return _inverseMatrix;
    }

    template <>
    inline Point<1>
    Datum<1, 1>::point(double x) const {
        return originPoint() + x * basisVector();
    }

    template <>
    inline Point2d
    Datum<2, 1>::point(double x) const {
        return originPoint() + x * basisVector();
    }

    template <>
    inline Point3d
    Datum<3, 1>::point(double x) const {
        return originPoint() + x * basisVector();
    }

    template <>
    inline Point2d
    Datum<2, 2>::point(double x, double y) const {
        return originPoint() + basisMatrix() * Vector2d(x, y);
    }

    template <>
    inline Point3d
    Datum<3, 2>::point(double x, double y) const {
        return originPoint() + basisMatrix() * Vector2d(x, y);
    }
    
    template <>
    inline Point3d
    Datum<3, 3>::point(double x, double y, double z) const {
        return originPoint() + basisMatrix() * Vector3d(x, y, z);
    }

    template <>
    inline Matrix1d
    Datum<1, 1>::vector(double x) const {
        return x * basisVector();
    }

    template <>
    inline Vector2d
    Datum<2, 1>::vector(double x) const {
        return x * basisVector();
    }

    template <>
    inline Vector3d
    Datum<3, 1>::vector(double x) const {
        return x * basisVector();
    }

    template <>
    inline Vector2d
    Datum<2, 2>::vector(double x, double y) const {
        return basisMatrix() * Vector2d(x, y);
    }

    template <>
    inline Vector3d
    Datum<3, 2>::vector(double x, double y) const {
        return basisMatrix() * Vector2d(x, y);
    }
    
    template <>
    inline Vector3d
    Datum<3, 3>::vector(double x, double y, double z) const {
        return basisMatrix() * Vector3d(x, y, z);
    }

    template<int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    Datum<iNumDimensions, iNumAxes>::xBasisVector() const {
        return basisMatrix().col(0);
    }

    template <int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    Datum<iNumDimensions, iNumAxes>::yBasisVector() const {
        return basisMatrix().col(1);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    Datum<iNumDimensions, iNumAxes>::zBasisVector() const {
        return basisMatrix().col(2);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    Datum<iNumDimensions, iNumAxes>::basisVector(int axisIndex ) const {
        return basisMatrix().col(axisIndex);
    }

    template <>
    inline Vector2d
    Datum<2, 1>::normalVector() const {
        return basisVector().unitOrthogonal();
    }

    template <>
    inline Vector3d
    Datum<3, 1>::normalVector() const {
        return basisVector().unitOrthogonal();
    }

    template <>
    inline Vector3d
    Datum<3, 2>::normalVector() const {
        return xBasisVector().cross(yBasisVector()).normalized();
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, 1>
    Datum<iNumDimensions, iNumAxes>::xAxis() const {
        return Datum<iNumDimensions, 1>(originPoint(), xBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, 1>
    Datum<iNumDimensions, iNumAxes>::yAxis() const {
        return Datum<iNumDimensions, 1>(originPoint(), yBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, 1>
    Datum<iNumDimensions, iNumAxes>::zAxis() const {
        return Datum<iNumDimensions, 1>(originPoint(), zBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, 1>
    Datum<iNumDimensions, iNumAxes>::axis(int axisIndex) const {
        return Datum<iNumDimensions, 1>(originPoint(), basisVector(axisIndex));
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, 1>
    Datum<iNumDimensions, iNumAxes>::normalAxis() const {
        return Datum<iNumDimensions, 1>(originPoint(), normalVector());
    }

    template <>
    inline Datum<3, 2>
    Datum<3, 3>::xyPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << xBasisVector(), yBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2>
    Datum<3, 3>::xzPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << xBasisVector(), zBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2>
    Datum<3, 3>::yxPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << yBasisVector(), xBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2>
    Datum<3, 3>::yzPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << yBasisVector(), zBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2>
    Datum<3, 3>::zxPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << zBasisVector(), xBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2>
    Datum<3, 3>::zyPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << zBasisVector(), yBasisVector();
        
        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2>
    Datum<3, 3>::plane(int firstAxisIndex, int secondAxisIndex) const {
        assert(firstAxisIndex >= 0 && firstAxisIndex < 3);
        assert(secondAxisIndex >= 0 && secondAxisIndex < 3);
        assert(firstAxisIndex != secondAxisIndex);

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << basisVector(firstAxisIndex), basisVector(secondAxisIndex);
        
        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2>
    Datum<3, 1>::normalPlane() const {
        Vector3d planeXBasisVector = basisVector().unitOrthogonal();
        Vector3d planeYBasisVector = basisVector().cross(planeXBasisVector).normalized();

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << planeXBasisVector, planeYBasisVector;

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes>
    Datum<iNumDimensions, iNumAxes>::reversed() const {
        Datum<iNumDimensions, iNumAxes> result;
        result._originPoint = originPoint();
        result._basisMatrix = -basisMatrix();
        result._inverseMatrix = -inverseMatrix();
        return result;
    }
        
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes>
    Datum<iNumDimensions, iNumAxes>::xReversed() const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basisMatrix.col(0) = -basisMatrix().col(0);
        result._inverseMatrix.row(0) = -inverseMatrix().row(0);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes>
    Datum<iNumDimensions, iNumAxes>::yReversed() const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basisMatrix.col(1) = -basisMatrix().col(1);
        result._inverseMatrix.row(1) = -inverseMatrix().row(1);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes>
    Datum<iNumDimensions, iNumAxes>::zReversed() const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basisMatrix.col(2) = -basisMatrix().col(2);
        result._inverseMatrix.row(2) = -inverseMatrix().row(2);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes>
    Datum<iNumDimensions, iNumAxes>::reversed(int axisIndex) const {
        assert(axisIndex >= 0 && axisIndex < iNumAxes);
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basisMatrix.col(axisIndex) = -basisMatrix().col(axisIndex);
        result._inverseMatrix.row(axisIndex) = -inverseMatrix().row(axisIndex);
        return result;
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>
    Datum<iNumDimensions, iNumAxes>::offset(double distance) const {
        return *this + distance * normalVector();
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes>
    Datum<iNumDimensions, iNumAxes>::normalized() const {
        Matrix<double, iNumDimensions, iNumAxes> resultBasisMatrix = basisMatrix();
        for (int i = 0; i < iNumAxes; ++i) {
            Matrix<double, iNumDimensions, 1> resultBasisVector = resultBasisMatrix.col(i);
            for (int j = 0; j < i; ++j) {
                Matrix<double, iNumDimensions, 1> normalizedBasisVector = resultBasisMatrix.col(j);
                resultBasisVector = resultBasisVector -
                    resultBasisVector.dot(normalizedBasisVector) * normalizedBasisVector;
            }
            if (resultBasisVector.isZero()) {
                assert(false);
            } else {
                resultBasisVector = resultBasisVector.normalized();
            }
            resultBasisMatrix.col(i) = resultBasisVector;
        }
        return Datum<iNumDimensions, iNumAxes>(originPoint(), resultBasisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes>
    ScalingFunction<Datum<iNumDimensions, iNumAxes>>::operator()(
        const Datum<iNumDimensions, iNumAxes>& datum,
        double scale
    ) const {
        return Datum<iNumDimensions, iNumAxes>(
            Point<iNumDimensions>::scaling(datum.originPoint(), scale),
            scale * datum.basisMatrix()
        );
    }

    template <int iNumDimensions, int iNumAxes> template <class TVector>
    Datum<iNumDimensions, iNumAxes>
    TranslationFunction<Datum<iNumDimensions, iNumAxes>>::operator()(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const EigenBase<TVector>& vector
    ) const {
        return Datum<iNumDimensions, iNumAxes>(
            Point<iNumDimensions>::translation(datum.originPoint(), vector.derived()),
            datum.basisMatrix()
        );
    }

    template <int iNumDimensions, int iNumAxes, int iNumTransformedDimensions>
    template <class TMatrix>
    Datum<iNumTransformedDimensions, iNumAxes>
    TransformationFunction<Datum<iNumDimensions, iNumAxes>, iNumTransformedDimensions>::operator()(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const EigenBase<TMatrix>& matrix
    ) const {
        return Datum<iNumTransformedDimensions, iNumAxes>(
            Point<iNumDimensions>::transformation(datum.originPoint(), matrix.derived()),
            matrix.derived() * datum.basisMatrix()
        );
    }

    template <int iNumDimensions, int iNumAxes, int iNumDestinationDimensions>
    inline Datum<iNumDestinationDimensions, iNumAxes>
    MorphingFunction<Datum<iNumDimensions, iNumAxes>, iNumDestinationDimensions>::operator()(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const Function<iNumDestinationDimensions, iNumDimensions>& function
    ) const {
        return Datum<iNumDestinationDimensions, iNumAxes>(
            datum.originPoint().morphed(function),
            function.jacobian(datum.originPoint().vector()) * datum.basisMatrix()
        );
    }
}
