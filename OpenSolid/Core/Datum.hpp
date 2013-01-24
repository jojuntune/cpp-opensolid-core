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

#include <OpenSolid/Core/Datum/declarations.hpp>
#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Utils/Convertible.hpp>

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
    protected:
        void initialize(
            const Matrix<double, iNumDimensions, 1>& originPoint,
            const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
        );

        template <int iOtherNumDimensions, int iOtherNumAxes>
        void initialize(const Datum<iOtherNumDimensions, iOtherNumAxes>& otherDatum );
    public:
        Datum();

        Datum(
            const Matrix<double, iNumDimensions, 1>& originPoint,
            const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
        );

        Datum(const Datum<iNumDimensions, iNumAxes>& otherDatum);

        template <int iOtherNumDimensions, int iOtherNumAxes>
        Datum(const Datum<iOtherNumDimensions, iOtherNumAxes>& otherDatum);

        Datum<iNumDimensions, iNumAxes>& operator=(
            const Datum<iNumDimensions, iNumAxes>& otherDatum
        );

        template <int iOtherNumDimensions, int iOtherNumAxes>
        Datum<iNumDimensions, iNumAxes>& operator=(
            const Datum<iOtherNumDimensions, iOtherNumAxes>& otherDatum
        );
        
        const Matrix<double, iNumDimensions, 1>& originPoint() const;
        const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix() const;
        const Matrix<double, iNumAxes, iNumDimensions>& inverseMatrix() const;
        
        int numDimensions() const;
        int numAxes() const;
        
        Matrix<double, iNumDimensions, 1> point(double x) const;
        Matrix<double, iNumDimensions, 1> point(double x, double y) const;
        Matrix<double, iNumDimensions, 1> point(double x, double y, double z) const;

        Matrix<double, iNumDimensions, 1> vector(double x) const;
        Matrix<double, iNumDimensions, 1> vector(double x, double y) const;
        Matrix<double, iNumDimensions, 1> vector(double x, double y, double z) const;

        typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr basisVector() const;
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

    typedef Datum<Dynamic, Dynamic> DatumXd;

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
        assert(originPoint.size() >= 1);
        assert(basisMatrix.cols() >= 1);
        assert(originPoint.size() == basisMatrix.rows());
        _originPoint = originPoint;
        _basisMatrix = basisMatrix;
        _inverseMatrix = (_basisMatrix.transpose() * _basisMatrix).inverse() *
            _basisMatrix.transpose();
    }

    template <int iNumDimensions, int iNumAxes>
    template <int iOtherNumDimensions, int iOtherNumAxes>
    inline void Datum<iNumDimensions, iNumAxes>::initialize(
        const Datum<iOtherNumDimensions, iOtherNumAxes>& otherDatum
    ) {
        assertCompatible<iNumDimensions, iOtherNumDimensions>();
        assertCompatible<iNumDimensions>(otherDatum.numDimensions());
        assertCompatible<iNumAxes, iOtherNumAxes>();
        assertCompatible<iNumAxes>(otherDatum.numAxes());
        _originPoint = otherDatum.originPoint();
        _basisMatrix = otherDatum.basisMatrix();
        _inverseMatrix = otherDatum.inverseMatrix();
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum() {
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
    template <int iOtherNumDimensions, int iOtherNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum(
        const Datum<iOtherNumDimensions, iOtherNumAxes>& otherDatum
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
    template <int iOtherNumDimensions, int iOtherNumAxes>
    inline Datum<iNumDimensions, iNumAxes>& Datum<iNumDimensions, iNumAxes>::operator=(
        const Datum<iOtherNumDimensions, iOtherNumAxes>& otherDatum
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
    
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumAxes, iNumDimensions>&
    Datum<iNumDimensions, iNumAxes>::inverseMatrix() const {
        return _inverseMatrix;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline int Datum<iNumDimensions, iNumAxes>::numDimensions() const {
        return basisMatrix().rows();
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline int Datum<iNumDimensions, iNumAxes>::numAxes() const {
        return basisMatrix().cols();
    }

    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1>  Datum<iNumDimensions, iNumAxes>::point(
        double x
    ) const {
        assertCompatible<iNumAxes, 1>();
        assert(numAxes() == 1);
        return originPoint() + basisMatrix() * x;
    }

    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1>  Datum<iNumDimensions, iNumAxes>::point(
        double x,
        double y
    ) const {
        assertCompatible<iNumAxes, 2>();
        assert(numAxes() == 2);
        return originPoint() + basisMatrix() * Vector2d(x, y);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::point(
        double x,
        double y,
        double z
    ) const {
        assertCompatible<iNumAxes, 3>();
        assert(numAxes() == 3);
        return originPoint() + basisMatrix() * Vector3d(x, y, z);
    }
        
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1>  Datum<iNumDimensions, iNumAxes>::vector(
        double x
    ) const {
        assertCompatible<iNumAxes, 1>();
        assert(numAxes() == 1);
        return basisMatrix() * x;
    }
        
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1>  Datum<iNumDimensions, iNumAxes>::vector(
        double x,
        double y
    ) const {
        assertCompatible<iNumAxes, 2>();
        assert(numAxes() == 2);
        return basisMatrix() * Vector2d(x, y);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::vector(
        double x,
        double y,
        double z
    ) const {
        assertCompatible<iNumAxes, 3>();
        assert(numAxes() == 3);
        return basisMatrix() * Vector3d(x, y, z);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    Datum<iNumDimensions, iNumAxes>::basisVector() const {
        assertCompatible<iNumAxes, 1>();
        assert(numAxes() == 1);
        return basisMatrix().col(0);
    }

    template<int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    Datum<iNumDimensions, iNumAxes>::xBasisVector() const {
        return basisMatrix().col(0);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    Datum<iNumDimensions, iNumAxes>::yBasisVector() const {
        assert(numAxes() >= 2);
        return basisMatrix().col(1);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    Datum<iNumDimensions, iNumAxes>::zBasisVector() const {
        assert(numAxes() >= 3);
        return basisMatrix().col(2);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline typename Matrix<double, iNumDimensions, iNumAxes>::ConstColXpr
    Datum<iNumDimensions, iNumAxes>::basisVector(int axisIndex ) const {
        assert(axisIndex >= 0 && axisIndex < numAxes());
        return basisMatrix().col(axisIndex);
    }

    namespace detail
    {
        inline Vector2d datumNormalVector(const Datum<2, 1>& axis) {
            return axis.basisVector().unitOrthogonal();
        }

        inline Vector3d datumNormalVector(const Datum<3, 1>& axis) {
            return axis.basisVector().unitOrthogonal();
        }

        inline VectorXd datumNormalVector(const Datum<Dynamic, 1>& axis) {
            return axis.basisVector().unitOrthogonal();
        }

        inline Vector3d datumNormalVector(const Datum<3, 2>& plane) {
            return plane.xBasisVector().cross(plane.yBasisVector()).normalized();
        }

        inline VectorXd datumNormalVector(const DatumXd& datum) {
            if (datum.numAxes() == 1) {
                return datum.basisVector().unitOrthogonal();
            } else if (datum.numAxes() == 2 && datum.numDimensions() == 3) {
                return datumNormalVector(Datum<3, 2>(datum));
            } else {
                assert(false);
                return VectorXd::Zero(datum.numDimensions());
            }
        }
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::normalVector() const {
        return detail::datumNormalVector(*this);
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::xAxis() const {
        return Datum<iNumDimensions, 1>(originPoint(), xBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::yAxis() const {
        assert(numAxes() >= 2);
        return Datum<iNumDimensions, 1>(originPoint(), yBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::zAxis() const {
        assert(numAxes() >= 3);
        return Datum<iNumDimensions, 1>(originPoint(), zBasisVector());
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::axis(int axisIndex) const {
        assert(axisIndex >= 0 && axisIndex < numAxes());
        return Datum<iNumDimensions, 1>(originPoint(), basisVector(axisIndex));
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::normalAxis() const {
        return Datum<iNumDimensions, 1>(originPoint(), normalVector());
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<3, 2> Datum<iNumDimensions, iNumAxes>::xyPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(numDimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(numAxes() == 3);

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << xBasisVector(), yBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<3, 2> Datum<iNumDimensions, iNumAxes>::xzPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(numDimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(numAxes() == 3);

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << xBasisVector(), zBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<3, 2> Datum<iNumDimensions, iNumAxes>::yxPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(numDimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(numAxes() == 3);

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << yBasisVector(), xBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<3, 2> Datum<iNumDimensions, iNumAxes>::yzPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(numDimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(numAxes() == 3);

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << yBasisVector(), zBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<3, 2> Datum<iNumDimensions, iNumAxes>::zxPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(numDimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(numAxes() == 3);

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << zBasisVector(), xBasisVector();

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<3, 2> Datum<iNumDimensions, iNumAxes>::zyPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(numDimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(numAxes() == 3);

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << zBasisVector(), yBasisVector();
        
        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<3, 2> Datum<iNumDimensions, iNumAxes>::plane(
        int firstAxisIndex,
        int secondAxisIndex
    ) const {
        assertCompatible<iNumDimensions, 3>();
        assert(numDimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(numAxes() == 3);
        assert(firstAxisIndex != secondAxisIndex);

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << basisVector(firstAxisIndex), basisVector(secondAxisIndex);
        
        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<3, 2> Datum<iNumDimensions, iNumAxes>::normalPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(numDimensions() == 3);
        assertCompatible<iNumAxes, 1>();
        assert(numAxes() == 1);

        Vector3d planeXBasisVector = basisVector().unitOrthogonal();
        Vector3d planeYBasisVector = basisVector().cross(planeXBasisVector).normalized();

        Matrix<double, 3, 2> planeBasisMatrix;
        planeBasisMatrix << planeXBasisVector, planeYBasisVector;

        return Datum<3, 2>(originPoint(), planeBasisMatrix);
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::reversed() const {
        assertCompatible<iNumAxes, 1>();
        assert(numAxes() == 1);
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
        assert(numAxes() >= 2);
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basisMatrix.col(1) = -basisMatrix().col(1);
        result._inverseMatrix.row(1) = -inverseMatrix().row(1);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::zReversed() const {
        assert(numAxes() >= 3);
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basisMatrix.col(2) = -basisMatrix().col(2);
        result._inverseMatrix.row(2) = -inverseMatrix().row(2);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::reversed(
        int axisIndex
    ) const {
        assert(axisIndex >= 0 && axisIndex < numAxes());
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basisMatrix.col(axisIndex) = -basisMatrix().col(axisIndex);
        result._inverseMatrix.row(axisIndex) = -inverseMatrix().row(axisIndex);
        return result;
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::offset(
        double distance
    ) const {
        return *this + distance * normalVector();
    }

    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::normalized() const {
        Matrix<double, iNumDimensions, iNumAxes> resultBasisMatrix = basisMatrix();
        for (int i = 0; i < numAxes(); ++i) {
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
