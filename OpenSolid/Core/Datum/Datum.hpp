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

#include <OpenSolid/Datum/declarations.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    template <int iNumDimensions, int iNumAxes>
    class Datum
    {
    private:
        Matrix<double, iNumDimensions, 1> _originPoint;
        Matrix<double, iNumDimensions, iNumAxes> _basisMatrix;
    protected:
        Datum(
            const Matrix<double, iNumDimensions, 1>& originPoint,
            const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
        );

        template <int iOtherNumDimensions, int iOtherNumAxes>
        Datum(const Datum<iOtherNumDimensions, iOtherNumAxes>& otherDatum);
    public:
        const Matrix<double, iNumDimensions, 1>& originPoint() const;
        const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix() const;
        
        int numDimensions() const;
        int numAxes() const;
        
        Matrix<double, iNumDimensions, 1> point(double x) const;
        Matrix<double, iNumDimensions, 1> point(double x, double y) const;
        Matrix<double, iNumDimensions, 1> point(double x, double y, double z) const;
        
        Matrix<double, iNumDimensions, 1> vector(double x = 1) const;
        Matrix<double, iNumDimensions, 1> vector(double x, double y) const;
        Matrix<double, iNumDimensions, 1> vector(double x, double y, double z) const;

        Matrix<double, iNumDimensions, 1> basisVector() const;
        Matrix<double, iNumDimensions, 1> basisVector(int index) const;
        Matrix<double, iNumDimensions, 1> xBasisVector() const;
        Matrix<double, iNumDimensions, 1> yBasisVector() const;
        Matrix<double, iNumDimensions, 1> zBasisVector() const;
        
        // Datum<iNumDimensions, 1> xAxis() const;
        // Datum<iNumDimensions, 1> yAxis() const;
        // Datum<iNumDimensions, 1> zAxis() const;
        // Datum<iNumDimensions, 1> axis(int index) const;
        // Datum<iNumDimensions, 1> normalAxis() const;

        // Datum<3, 2> xyPlane() const;
        // Datum<3, 2> xzPlane() const;
        // Datum<3, 2> yxPlane() const;
        // Datum<3, 2> yzPlane() const;
        // Datum<3, 2> zxPlane() const;
        // Datum<3, 2> zyPlane() const;
        // Datum<3, 2> plane(int firstIndex, int secondIndex) const;
        // Datum<3, 2> normalPlane() const;

        // template <class TTransformMatrix, class TTransformVector>
        // Datum<TTransformMatrix::RowsAtCompileTime, iNumAxes> transformed(
        //     const TTransformMatrix& matrix,
        //     const TTransformVector& vector
        // ) const;

        // Datum<iNumDimensions, iNumAxes> scaled(
        //     double scale,
        //     const Matrix<double, iNumDimensions, 1>& point
        // ) const;
        
        // Datum<iNumDimensions, iNumAxes> scaled(
        //     double scale
        // ) const;
        
        // Datum<iNumDimensions, iNumAxes> xReversed() const;
        // Datum<iNumDimensions, iNumAxes> yReversed() const;
        // Datum<iNumDimensions, iNumAxes> zReversed() const;
        // Datum<iNumDimensions, iNumAxes> reversed(int index) const;
        // Datum<iNumDimensions, iNumAxes> reversed() const;

        // Datum<iNumDimensions, iNumAxes> orientation() const;
    };

    template <class TTransformable, int iNumDimensions, int iNumAxes>
    typename Transformed<TTransformable, iNumDimensions>::Type
    operator*(const TTransformable& transformable, const Datum<iNumDimensions, iNumAxes>& datum);

    // template <class TTransformable, int iNumDimensions, int iNumAxes>
    // typename Transformed<TTransformable, iNumAxes>::Type
    // operator/(const TTransformable& transformable, const Datum<iNumDimensions, iNumAxes>& datum);

    // template <class TTransformable, int iNumDimensions, int iNumAxes>
    // typename Transformed<TTransformable, iNumDimensions>::Type
    // operator%(const TTransformable& transformable, const Datum<iNumDimensions, iNumAxes>& datum);
}

////////// Implementation //////////

namespace opensolid
{
    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline typename Transformed<TDerived, iNumDimensions>::Type
    Transformable<TDerived>::translated(
        double distance,
        const Datum<iNumDimensions, iNumAxes>& axis
    ) const {
        assertCompatible<iNumAxes, 1>();
        assert(axis.numAxes() == 1);
        assert(axis.basisVector().norm() == 1);
        return derived().transformed(
            Matrix<double, iNumDimensions, iNumDimensions>::Identity(axis.numDimensions()),
            distance * axis.directionVector()
        );
    }

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline typename Transformed<TDerived, 3>::Type
    Transformable<DerivedType, ResultType>::rotated(
        double angle,
        const Datum<iNumDimensions, iNumAxes>& axis
    ) const {
        assertCompatible<iNumDimensions, 3>();
        assert(axis.numDimensions() == 3);
        assertCompatible<iNumAxes, 1>();
        assert(axis.numAxes() == 1);
        Matrix3d matrix = Matrix3d(AngleAxisd(angle, axis.directionVector()));
        return derived().transformed(matrix, axis.originPoint() - matrix * axis.originPoint());
    }

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline typename Transformed<TDerived, iNumDimensions>::Type
    Transformable<TDerived>::mirrored(
        const Datum<iNumDimensions, iNumAxes>& plane
    ) const {
        Matrix<double, iNumDimensions, 1> normal = plane.normalVector();
        typedef Eigen::Matrix<double, iNumDimensions, iNumDimensions> Matrix;
        Matrix normalMatrix = 2 * normal * normal.transpose();
        Matrix matrix = Matrix::Identity(plane.numDimensions(), plane.numDimensions());
        matrix -= normalMatrix;
        return derived().transformed(matrix, normalMatrix * plane.originPoint());
    }

    template <class TDerived> template <int iNumDimensions, int iNumAxes>
    inline typename Transformed<TDerived, iNumDimensions>::Type
    Transformable<TDerived>::projected(
        const Datum<iNumDimensions, iNumAxes>& datum
    ) const {
        // TODO
    }

    template <int iNumDimensions, int iNumAxes>
    inline void Datum<iNumDimensions, iNumAxes>::initialize(
        const Matrix<double, iNumDimensions, 1>& originPoint,
        const Matrix<double, iNumDimensions, iNumAxes>& basisMatrix
    ) {
        assert(originPoint.size() >= 1);
        assert(basisMatrix.cols() >= 1);
        assert(originPoint.size() == basisMatrix.rows());
        _originPoint = originPoint;
        _basisMatrix = basisMatrix;

        _inverseMatrix =
            (_basisMatrix.transpose() * _basisMatrix).inverse() * _basisMatrix.transpose();
        _projectionMatrix = _basisMatrix * _inverseMatrix;
    }

    template <int iNumDimensions, int iNumAxes>
    template <int iOtherNumDimensions, int iOtherNumAxes>
    inline void Datum<iNumDimensions, iNumAxes>::initialize(
        const Datum<iOtherNumDimensions, iOtherNumAxes>& otherDatum
    ) {
        assertCompatible<iNumDimensions, iOtherNumDimensions>();
        assertCompatible<iNumDimensions>(otherDatum.dimensions());
        assertCompatible<iNumAxes, iOtherNumAxes>();
        assertCompatible<iNumAxes>(otherDatum.numAxes());
        _originPoint = otherDatum.originPoint();
        _basisMatrix = other.basisMatrix();
        _inverseMatrix = otherDatum.inverseMatrix();
        _projectionMatrix = otherDatum.projectionMatrix();
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum() {
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum(
        const Matrix<double, iNumDimensions, 1>& origin,
        const Matrix<double, iNumDimensions, iNumAxes>& basis
    ) {initialize(origin, basis);}

    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum(
        const Matrix<double, iNumDimensions, 1>& origin,
        const Matrix<double, iNumDimensions, 1>& x_direction,
        const Matrix<double, iNumDimensions, 1>& y_direction
    ) {
        assertCompatible<2, iNumAxes>();
        Matrix<double, iNumDimensions, iNumAxes> basis(origin.size(), 2);
        basis.col(0) = x_direction;
        basis.col(1) = y_direction;
        initialize(origin, basis);
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum(
        const Matrix<double, iNumDimensions, 1>& origin,
        const Matrix<double, iNumDimensions, 1>& x_direction,
        const Matrix<double, iNumDimensions, 1>& y_direction,
        const Matrix<double, iNumDimensions, 1>& z_direction
    ) {
        assertCompatible<3, iNumAxes>();
        Matrix<double, iNumDimensions, iNumAxes> basis(origin.size(), 3);
        basis.col(0) = x_direction;
        basis.col(1) = y_direction;
        basis.col(2) = z_direction;
        initialize(origin, basis);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum(const Datum<iNumDimensions, iNumAxes>& other) {
        initialize(other);
    }
    
    template <int iNumDimensions, int iNumAxes> template <int iOtherNumDimensions, int iOtherNumAxes>
    inline Datum<iNumDimensions, iNumAxes>::Datum(const Datum<iOtherNumDimensions, iOtherNumAxes>& other) {
        initialize(other);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes>& Datum<iNumDimensions, iNumAxes>::operator=(
        const Datum<iNumDimensions, iNumAxes>& other
    ) {
        initialize(other);
        return *this;
    }
    
    template <int iNumDimensions, int iNumAxes> template <int iOtherNumDimensions, int iOtherNumAxes>
    inline Datum<iNumDimensions, iNumAxes>& Datum<iNumDimensions, iNumAxes>::operator=(
        const Datum<iOtherNumDimensions, iOtherNumAxes>& other
    ) {
        initialize(other);
        return *this;
    }
        
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumDimensions, 1>&
    Datum<iNumDimensions, iNumAxes>::origin() const {return _origin;}
    
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumDimensions, iNumAxes>&
    Datum<iNumDimensions, iNumAxes>::basis() const {return _basis;}
    
    template <int iNumDimensions, int iNumAxes>
    inline const Matrix<double, iNumAxes, iNumDimensions>&
    Datum<iNumDimensions, iNumAxes>::inverseMatrix() const {return _inverse_matrix;}
    
    template <int iNumDimensions, int iNumAxes>
    inline int Datum<iNumDimensions, iNumAxes>::dimensions() const {return basis().rows();}
    
    template <int iNumDimensions, int iNumAxes>
    inline int Datum<iNumDimensions, iNumAxes>::axes() const {return basis().cols();}

    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1>  Datum<iNumDimensions, iNumAxes>::point(double x) const {
        assert(axes() == 1);
        return origin() + basis() * x;
    }

    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1>  Datum<iNumDimensions, iNumAxes>::point(
        double x,
        double y
    ) const {
        assert(axes() == 2);
        return origin() + basis() * Vector2d(x, y);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::point(
        double x,
        double y,
        double z
    ) const {
        assert(axes() == 3);
        return origin() + basis() * Vector3d(x, y, z);
    }
        
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1>  Datum<iNumDimensions, iNumAxes>::vector(double x) const {
        assert(axes() == 1);
        return basis() * x;
    }
        
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1>  Datum<iNumDimensions, iNumAxes>::vector(
        double x,
        double y
    ) const {
        assert(axes() == 2);
        return basis() * Vector2d(x, y);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::vector(
        double x,
        double y,
        double z
    ) const {
        assertCompatible<iNumAxes, 3>();
        assert(axes() == 3);
        return basis() * Vector3d(x, y, z);
    }

    template<int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::xDirection() const {
        return basis().col(0);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::yDirection() const {
        assert(axes() >= 2);
        return basis().col(1);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::zDirection() const {
        assert(axes() >= 3);
        return basis().col(2);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::direction(int index) const {
        assert(index >= 0 && index < axes());
        return basis().col(index);
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::direction() const {
        assert(axes() == 1);
        return basis();
    }

    namespace
    {
        inline Vector2d datumNormal(const Datum<2, 1>& axis) {
            return axis.basisVector().unitOrthogonal();
        }

        inline Vector3d datumNormal(const Datum<3, 1>& axis) {
            return axis.basisVector().unitOrthogonal();
        }

        inline VectorXd datumNormal(const Datum<Dynamic, 1>& axis) {
            return axis.basisVector().unitOrthogonal();
        }

        inline Vector3d datumNormal(const Datum<3, 2>& plane) {
            return plane.xBasisVector().cross(plane.yBasisVector()).normalized();
        }

        inline VectorXd datumNormal(const DatumXd& datum) {
            if (datum.numAxes() == 1) {
                return datum.basisVector().unitOrthogonal();
            } else {
                assert(datum.dimensions() == 3);
                assert(datum.axes() == 2);
                Vector3d x_direction = datum.xDirection();
                Vector3d y_direction = datum.yDirection();
                return x_direction.cross(y_direction).normalized();
            }
        }
    }
    
    template <int iNumDimensions, int iNumAxes>
    Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::normalVector() const {
        assert(axes() < dimensions());
        return datumNormal(*this);
    }
    
    template <int iNumDimensions, int iNumAxes>
    Matrix<double, iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::directionVector() const {
        assertCompatible<iNumAxes, 1>();
        assert(numAxes() == 1);
        return basisVector().normalized();
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::xAxis() const {
        return Datum<iNumDimensions, 1>(origin(), xDirection());
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::yAxis() const {
        return Datum<iNumDimensions, 1>(origin(), yDirection());
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::zAxis() const {
        return Datum<iNumDimensions, 1>(origin(), zDirection());
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::axis(int index) const {
        return Datum<iNumDimensions, 1>(origin(), direction(index));
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, 1> Datum<iNumDimensions, iNumAxes>::normalAxis() const {
        return Datum<iNumDimensions, 1>(origin(), normal());
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<3, 2> Datum<iNumDimensions, iNumAxes>::xyPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(dimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), xDirection(), yDirection());
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<3, 2> Datum<iNumDimensions, iNumAxes>::xzPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(dimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), xDirection(), zDirection());
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<3, 2> Datum<iNumDimensions, iNumAxes>::yxPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(dimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), yDirection(), xDirection());
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<3, 2> Datum<iNumDimensions, iNumAxes>::yzPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(dimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), yDirection(), zDirection());
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<3, 2> Datum<iNumDimensions, iNumAxes>::zxPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(dimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), zDirection(), xDirection());
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<3, 2> Datum<iNumDimensions, iNumAxes>::zyPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(dimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), zDirection(), yDirection());
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<3, 2> Datum<iNumDimensions, iNumAxes>::plane(int first_index, int second_index) const {
        assertCompatible<iNumDimensions, 3>();
        assert(dimensions() == 3);
        assertCompatible<iNumAxes, 3>();
        assert(axes() == 3);
        assert(first_index != second_index);
        return Datum<3, 2>(origin(), direction(first_index), direction(second_index));
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<3, 2> Datum<iNumDimensions, iNumAxes>::normalPlane() const {
        assertCompatible<iNumDimensions, 3>();
        assert(dimensions() == 3);
        Vector3d axial_direction(direction());
        Vector3d x_direction = axial_direction.unitOrthogonal();
        Vector3d y_direction = axial_direction.cross(x_direction).normalized();
        return Datum<3, 2>(origin(), x_direction, y_direction);
    }

    template <int iNumDimensions, int iNumAxes> template <class MatrixType, class VectorType>
    inline Datum<MatrixType::RowsAtCompileTime, iNumAxes> Datum<iNumDimensions, iNumAxes>::transformed(
        const MatrixType& matrix,
        const VectorType& vector
    ) const {
        assertValidTransform<iNumDimensions>(dimensions(), matrix, vector);
        return Datum<MatrixType::RowsAtCompileTime, iNumAxes>(
            matrix * origin() + vector,
            matrix * basis()
        );
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::scaled(
        double scale,
        const Matrix<double, iNumDimensions, 1>& point
    ) const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basis *= scale;
        result._inverse_matrix /= scale;
        result._origin = point + scale * (origin() - point);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::scaled(double scale) const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basis *= scale;
        result._inverse_matrix /= scale;
        return result;
    }

    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::translated(
        const Matrix<double, iNumDimensions, 1>& vector
    ) const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._origin += vector;
        return result;
    }

    template <int iNumDimensions, int iNumAxes> template <int iOtherNumDimensions, int iOtherNumAxes>
    inline Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::translated(
        double distance,
        const Datum<iOtherNumDimensions, iOtherNumAxes>& axis
    ) const {
        assertCompatible<iOtherNumDimensions, iNumDimensions>();
        assert(axis.dimensions() == dimensions());
        assertCompatible<iOtherNumAxes, 1>();
        assert(axis.axes() == 1);
        assert(axis.direction().norm() - 1 == Zero());
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._origin += distance * axis.direction();
        return result;
    }
        
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::xReversed() const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basis.col(0) = -basis().row(0);
        result._inverse_matrix.row(0) = -inverseMatrix().row(0);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::yReversed() const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basis.col(1) = -basis().row(1);
        result._inverse_matrix.row(1) = -inverseMatrix().row(1);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::zReversed() const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basis.col(2) = -basis().row(2);
        result._inverse_matrix.row(2) = -inverseMatrix().row(2);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::reversed(int index) const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._basis.col(index) = -basis().row(index);
        result._inverse_matrix.row(index) = -inverseMatrix().row(index);
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    inline Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::reversed() const {
        assertCompatible<iNumAxes, 1>();
        assert(axes() == 1);
        Datum<iNumDimensions, iNumAxes> result;
        result._origin = origin();
        result._basis = -basis();
        result._inverse_matrix = -inverseMatrix();
        return result;
    }
    
    template <int iNumDimensions, int iNumAxes>
    Datum<iNumDimensions, iNumAxes> Datum<iNumDimensions, iNumAxes>::orientation() const {
        Datum<iNumDimensions, iNumAxes> result(*this);
        result._origin.setZero();
        return result;
    }

    template <class TTransformable, int iNumDimensions, int iNumAxes>
    inline auto operator*(
        const TTransformable& transformable,
        const Datum<iNumDimensions, iNumAxes>& datum
    ) -> decltype(
        transformable.transformed(
            Matrix<double, iNumDimensions, iNumAxes>(),
            Matrix<double, iNumDimensions, 1>()
        )
    ) {
        return transformable.transformed(
            datum.basis(),
            datum.origin()
        );
    }

    template <class TTransformable, int iNumDimensions, int iNumAxes>
    inline auto operator/(
        const TTransformable& transformable,
        const Datum<iNumDimensions, iNumAxes>& datum
    ) -> decltype(
        transformable.transformed(
            Matrix<double, iNumAxes, iNumDimensions>(),
            Matrix<double, iNumAxes, 1>()
        )
    ) {
        return transformable.transformed(
            datum.inverseMatrix(),
            -datum.inverseMatrix() * datum.origin()
        );
    }

    template <class TTransformable, int iNumDimensions, int iNumAxes>
    inline auto operator%(
        const TTransformable& transformable,
        const Datum<iNumDimensions, iNumAxes>& datum
    ) -> decltype(
        transformable.transformed(
            Matrix<double, iNumDimensions, iNumDimensions>(),
            Matrix<double, iNumDimensions, 1>()
        )
    ) {
        Matrix<double, iNumDimensions, iNumDimensions> projection_matrix =
            datum.basis() * datum.inverseMatrix();
        return transformable.transformed(
            projection_matrix,
            datum.origin() - projection_matrix * datum.origin()
        );
    }
}
