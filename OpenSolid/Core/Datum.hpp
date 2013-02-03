/***************************************************************************
 *   Copyright (C) 2007 by Ian Mackenzie                                   *
 *   ian.e.mackenzie@gmail.com                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

// Public headers
#include <OpenSolid/Core/Convertible.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Transformable.hpp>
 
// Declarations headers
#include <OpenSolid/Core/Datum/declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    class Datum :
        public Transformable<Datum<iNumDimensions, iNumAxes>>,
        public Convertible<Datum<iNumDimensions, iNumAxes>>
    {
    private:
        Matrix<double, iNumDimensions, 1> _originPoint;
        Matrix<double, iNumDimensions, iNumAxes> _basisMatrix;
        Matrix<double, iNumAxes, iNumDimensions> _inverseMatrix;

        void initialize(
            const Matrix<double, iNumDimensions, 1>& originPoint,
            const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
        );

        void initialize(const Datum<iNumDimensions, iNumAxes>& otherDatum );
    public:
        Datum();

        Datum(const Matrix<double, iNumDimensions, 1>& originPoint);

        Datum(
            const Matrix<double, iNumDimensions, 1>& originPoint,
            const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
        );

        Datum(const Datum<iNumDimensions, iNumAxes>& otherDatum);
        
        Datum<iNumDimensions, iNumAxes>& operator=(
            const Datum<iNumDimensions, iNumAxes>& otherDatum
        );
        
        const Matrix<double, iNumDimensions, 1>& originPoint() const;
        const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix() const;
        const Matrix<double, iNumDimensions, iNumAxes>& basisVector() const;
        const Matrix<double, iNumAxes, iNumDimensions>& inverseMatrix() const;
        
        Matrix<double, iNumDimensions, 1> point(double x) const;
        Matrix<double, iNumDimensions, 1> point(double x, double y) const;
        Matrix<double, iNumDimensions, 1> point(double x, double y, double z) const;

        Matrix<double, iNumDimensions, 1> vector(double x) const;
        Matrix<double, iNumDimensions, 1> vector(double x, double y) const;
        Matrix<double, iNumDimensions, 1> vector(double x, double y, double z) const;

        typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr xBasisVector() const;
        typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr yBasisVector() const;
        typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr zBasisVector() const;
        
        typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr basisVector(
            int axisIndex
        ) const;

        Matrix<double, iNumDimensions, 1> normalVector() const;
        
        Datum<iNumDimensions, 1> xAxis() const;
        Datum<iNumDimensions, 1> yAxis() const;
        Datum<iNumDimensions, 1> zAxis() const;
        Datum<iNumDimensions, 1> axis(int axisIndex) const;
        Datum<iNumDimensions, 1> normalAxis() const;

        Datum<3, 2> xyPlane() const;
        Datum<3, 2> xzPlane() const;
        Datum<3, 2> yxPlane() const;
        Datum<3, 2> yzPlane() const;
        Datum<3, 2> zxPlane() const;
        Datum<3, 2> zyPlane() const;
        Datum<3, 2> plane(int firstAxisIndex, int secondAxisIndex) const;
        Datum<3, 2> normalPlane() const;
        
        Datum<iNumDimensions, iNumAxes> reversed() const;
        Datum<iNumDimensions, iNumAxes> xReversed() const;
        Datum<iNumDimensions, iNumAxes> yReversed() const;
        Datum<iNumDimensions, iNumAxes> zReversed() const;
        Datum<iNumDimensions, iNumAxes> reversed(int index) const;

        Datum<iNumDimensions, iNumAxes> offset(double distance) const;

        Datum<iNumDimensions, iNumAxes> normalized() const;

        Datum<iNumDimensions, iNumAxes> linear() const;
    };

    template <int iNumDimensions, int iNumAxes, class TMatrix>
    Matrix<typename TMatrix::Scalar, iNumDimensions, TMatrix::ColsAtCompileTime> operator*(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const EigenBase<TMatrix>& matrix
    );

    template <class TMatrix, int iNumDimensions, int iNumAxes>
    Matrix<typename TMatrix::Scalar, iNumAxes, TMatrix::ColsAtCompileTime> operator/(
        const EigenBase<TMatrix>& matrix,
        const Datum<iNumDimensions, iNumAxes>& datum
    );

    template <int iNumDimensions, int iNumAxes, class TTransformable>
    typename Transformed<TTransformable, iNumDimensions>::Type operator*(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const Transformable<TTransformable>& transformable
    );

    template <class TTransformable, int iNumDimensions, int iNumAxes>
    typename Transformed<TTransformable, iNumAxes>::Type operator/(
        const Transformable<TTransformable>& transformable,
        const Datum<iNumDimensions, iNumAxes>& datum
    );

    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> operator*(
        double scaleFactor,
        const Datum<iNumDimensions, iNumAxes>& datum
    );

    template <int iNumDimensions, int iNumAxes, class TVector>
    Datum<iNumDimensions, iNumAxes> operator+(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const EigenBase<TVector>& vector
    );

    template <class TMatrix, int iNumDimensions, int iNumAxes>
    Datum<TMatrix::RowsAtCompileTime, iNumAxes> operator*(
        const EigenBase<TMatrix>& transformationMatrix,
        const Datum<iNumDimensions, iNumAxes>& datum
    );
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes, int iTransformedDimensions>
    struct Transformed<Datum<iNumDimensions, iNumAxes>, iTransformedDimensions>
    {
        typedef Datum<iTransformedDimensions, iNumAxes> Type;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    void Datum<iNumDimensions, iNumAxes>::initialize(
        const Matrix<double, iNumDimensions, 1>& originPoint,
        const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
    ) {
        _originPoint = originPoint;
        _basisMatrix = basisMatrix;
        _inverseMatrix = (_basisMatrix.transpose() * _basisMatrix).inverse() *
            _basisMatrix.transpose();
    }

    template <int iNumDimensions, int iNumAxes>
    inline void Datum<iNumDimensions, iNumAxes>::initialize(
        const Datum<iNumDimensions, iNumAxes>& otherDatum
    ) {
        _originPoint = otherDatum.originPoint();
        _basisMatrix = otherDatum.basisMatrix();
        _inverseMatrix = otherDatum.inverseMatrix();
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum() {
        _originPoint.setZero();
        _basisMatrix.setIdentity();
        _inverseMatrix.setIdentity();
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum(
        const Matrix<double, iNumDimensions, 1>& originPoint
    ) : _originPoint(originPoint) {

        _basisMatrix.setIdentity();
        _inverseMatrix.setIdentity();
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum(
        const Matrix<double, iNumDimensions, 1>& originPoint,
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
    inline Datum<iNumDimensions, iNumAxes>& Datum<iNumDimensions, iNumAxes>::operator=(
        const Datum<iNumDimensions, iNumAxes>& otherDatum
    ) {
        initialize(otherDatum);
        return *this;
    }
        
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumDimensions, 1>&
    Datum<iNumDimensions, iNumAxes>::originPoint() const {
        return _originPoint;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumDimensions, iNumAxes>&
    Datum<iNumDimensions, iNumAxes>::basisMatrix() const {
        return _basisMatrix;
    }
    
    template <>
    inline const Matrix1d& Datum<1, 1>::basisVector() const {
        return basisMatrix();
    }
    
    template <>
    inline const Vector2d& Datum<2, 1>::basisVector() const {
        return basisMatrix();
    }
    
    template <>
    inline const Vector3d& Datum<3, 1>::basisVector() const {
        return basisMatrix();
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumAxes, iNumDimensions>&
    Datum<iNumDimensions, iNumAxes>::inverseMatrix() const {
        return _inverseMatrix;
    }

    template <>
    inline Matrix1d Datum<1, 1>::point(double x) const {
        return originPoint() + x * basisVector();
    }

    template <>
    inline Vector2d Datum<2, 1>::point(double x) const {
        return originPoint() + x * basisVector();
    }

    template <>
    inline Vector3d Datum<3, 1>::point(double x) const {
        return originPoint() + x * basisVector();
    }

    template <>
    inline Vector2d Datum<2, 2>::point(double x, double y) const {
        return originPoint() + basisMatrix() * Vector2d(x, y);
    }

    template <>
    inline Vector3d Datum<3, 2>::point(double x, double y) const {
        return originPoint() + basisMatrix() * Vector2d(x, y);
    }
    
    template <>
    inline Vector3d Datum<3, 3>::point(double x, double y, double z) const {
        return originPoint() + basisMatrix() * Vector3d(x, y, z);
    }

    template <>
    inline Matrix1d Datum<1, 1>::vector(double x) const {
        return x * basisVector();
    }

    template <>
    inline Vector2d Datum<2, 1>::vector(double x) const {
        return x * basisVector();
    }

    template <>
    inline Vector3d Datum<3, 1>::vector(double x) const {
        return x * basisVector();
    }

    template <>
    inline Vector2d Datum<2, 2>::vector(double x, double y) const {
        return basisMatrix() * Vector2d(x, y);
    }

    template <>
    inline Vector3d Datum<3, 2>::vector(double x, double y) const {
        return basisMatrix() * Vector2d(x, y);
    }
    
    template <>
    inline Vector3d Datum<3, 3>::vector(double x, double y, double z) const {
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
    inline Vector2d Datum<2, 1>::normalVector() const {
        return basisVector().unitOrthogonal();
    }

    template <>
    inline Vector3d Datum<3, 1>::normalVector() const {
        return basisVector().unitOrthogonal();
    }

    template <>
    inline Vector3d Datum<3, 2>::normalVector() const {
        return xBasisVector().cross(yBasisVector()).normalized();
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::xAxis() const {
        return Datum<iNumDimensions, 1>(originPoint(), xBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::yAxis() const {
        return Datum<iNumDimensions, 1>(originPoint(), yBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::zAxis() const {
        return Datum<iNumDimensions, 1>(originPoint(), zBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::axis(int axisIndex) const {
        return Datum<iNumDimensions, 1>(originPoint(), basisVector(axisIndex));
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::normalAxis() const {
        return Datum<iNumDimensions, 1>(originPoint(), normalVector());
    }

    template <>
    inline Datum<3, 2> Datum<3, 3>::xyPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << xBasisVector(), yBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2> Datum<3, 3>::xzPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << xBasisVector(), zBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2> Datum<3, 3>::yxPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << yBasisVector(), xBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2> Datum<3, 3>::yzPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << yBasisVector(), zBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2> Datum<3, 3>::zxPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << zBasisVector(), xBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2> Datum<3, 3>::zyPlane() const {
        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << zBasisVector(), yBasisVector();
        
        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2> Datum<3, 3>::plane(int firstAxisIndex, int secondAxisIndex) const {
        assert(firstAxisIndex >= 0 && firstAxisIndex < 3);
        assert(secondAxisIndex >= 0 && secondAxisIndex < 3);
        assert(firstAxisIndex != secondAxisIndex);

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << basisVector(firstAxisIndex), basisVector(secondAxisIndex);
        
        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <>
    inline Datum<3, 2> Datum<3, 1>::normalPlane() const {
        Vector3d planeXBasisVector = basisVector().unitOrthogonal();
        Vector3d planeYBasisVector = basisVector().cross(planeXBasisVector).normalized();

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << planeXBasisVector, planeYBasisVector;

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::reversed() const {
        Datum<iNumDimensions, iNumAxes> result;
        result._originPoint = originPoint();
        result._basisMatrix = -basisMatrix();
        result._inverseMatrix = -inverseMatrix();
        return result;
    }
        
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::xReversed() const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basisMatrix.col(0) = -basisMatrix().col(0);
        result._inverseMatrix.row(0) = -inverseMatrix().row(0);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::yReversed() const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basisMatrix.col(1) = -basisMatrix().col(1);
        result._inverseMatrix.row(1) = -inverseMatrix().row(1);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::zReversed() const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basisMatrix.col(2) = -basisMatrix().col(2);
        result._inverseMatrix.row(2) = -inverseMatrix().row(2);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::reversed(
        int axisIndex
    ) const {
        assert(axisIndex >= 0 && axisIndex < iNumAxes);
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basisMatrix.col(axisIndex) = -basisMatrix().col(axisIndex);
        result._inverseMatrix.row(axisIndex) = -inverseMatrix().row(axisIndex);
        return result;
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::offset(
        double distance
    ) const {
        return *this + distance * normalVector();
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::normalized() const {
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
    inline Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::linear() const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._originPoint.setZero();
        return result;
    }

    template <int iNumDimensions, int iNumAxes, class TMatrix>
    Matrix<typename TMatrix::Scalar, iNumDimensions, TMatrix::ColsAtCompileTime> operator*(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const EigenBase<TMatrix>& matrix
    ) {
        typedef typename TMatrix::Scalar MatrixScalar;
        return (datum.basisMatrix().template cast<MatrixScalar>() * matrix.derived()).colwise() +
            datum.originPoint().template cast<MatrixScalar>();
    }

    template <class TMatrix, int iNumDimensions, int iNumAxes>
    Matrix<typename TMatrix::Scalar, iNumAxes, TMatrix::ColsAtCompileTime> operator/(
        const EigenBase<TMatrix>& matrix,
        const Datum<iNumDimensions, iNumAxes>& datum
    ) {
        typedef typename TMatrix::Scalar MatrixScalar;
        return datum.inverseMatrix().template cast<MatrixScalar>() *
            (matrix.derived().colwise() - datum.originPoint().template cast<MatrixScalar>());
    }

    template <int iNumDimensions, int iNumAxes, class TTransformable>
    inline typename Transformed<TTransformable, iNumDimensions>::Type operator*(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const Transformable<TTransformable>& transformable
    ) {
        return datum.basisMatrix() * transformable.derived() + datum.originPoint();
    }

    template <class TTransformable, int iNumDimensions, int iNumAxes>
    inline typename Transformed<TTransformable, iNumAxes>::Type operator/(
        const Transformable<TTransformable>& transformable,
        const Datum<iNumDimensions, iNumAxes>& datum
    ) {
        return datum.inverseMatrix() * (transformable.derived() - datum.originPoint());
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> operator*(
        double scaleFactor,
        const Datum<iNumDimensions, iNumAxes>& datum
    ) {
        return Datum<iNumDimensions, iNumAxes>(
            scaleFactor * datum.originPoint(),
            scaleFactor * datum.basisMatrix()
        );
    }

    template <int iNumDimensions, int iNumAxes, class TVector>
    Datum<iNumDimensions, iNumAxes> operator+(
        const Datum<iNumDimensions, iNumAxes>& datum,
        const EigenBase<TVector>& vector
    ) {
        return Datum<iNumDimensions, iNumAxes>(
            datum.originPoint() + vector.derived(),
            datum.basisMatrix()
        );
    }

    template <class TMatrix, int iNumDimensions, int iNumAxes>
    Datum<TMatrix::RowsAtCompileTime, iNumAxes> operator*(
        const EigenBase<TMatrix>& transformationMatrix,
        const Datum<iNumDimensions, iNumAxes>& datum
    ) {
        return Datum<TMatrix::RowsAtCompileTime, iNumAxes>(
            transformationMatrix.derived() * datum.originPoint(),
            transformationMatrix.derived() * datum.basisMatrix()
        );
    }
}
