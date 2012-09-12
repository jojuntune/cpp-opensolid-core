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

#include "config.hpp"

#include "TypeName.hpp"
#include "Transformable.hpp"
#include "Matrix.hpp"

namespace opensolid
{
    template <int dimensions_, int axes_>
    class Datum : public Transformable<Datum<dimensions_, axes_>>
    {
    private:
        template <int other_dimensions_, int other_axes_>
        friend class Datum;

        Matrix<double, dimensions_, 1> _origin;
        Matrix<double, dimensions_, axes_> _basis;
        Matrix<double, axes_, dimensions_> _inverse_matrix;
        Matrix<double, dimensions_, dimensions_> _projection_matrix;
    protected:
        void initialize(
            const Matrix<double, dimensions_, 1>& origin,
            const Matrix<double, dimensions_, axes_>& basis
        );

        template <int other_dimensions_, int other_axes_>
        void initialize(const Datum<other_dimensions_, other_axes_>& other);
    public:
        Datum();
        
        Datum(
            const Matrix<double, dimensions_, 1>& origin,
            const Matrix<double, dimensions_, axes_>& basis
        );

        Datum(
            const Matrix<double, dimensions_, 1>& origin,
            const Matrix<double, dimensions_, 1>& x_direction,
            const Matrix<double, dimensions_, 1>& y_direction
        );

        Datum(
            const Matrix<double, dimensions_, 1>& origin,
            const Matrix<double, dimensions_, 1>& x_direction,
            const Matrix<double, dimensions_, 1>& y_direction,
            const Matrix<double, dimensions_, 1>& z_direction
        );
        
        Datum(const Datum<dimensions_, axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Datum(const Datum<other_dimensions_, other_axes_>& other);
        
        Datum<dimensions_, axes_>& operator=(const Datum<dimensions_, axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Datum<dimensions_, axes_>& operator=(const Datum<other_dimensions_, other_axes_>& other);
        
        const Matrix<double, dimensions_, 1>& origin() const;
        const Matrix<double, dimensions_, axes_>& basis() const;
        const Matrix<double, axes_, dimensions_>& inverseMatrix() const;
        const Matrix<double, dimensions_, dimensions_>& projectionMatrix() const;
        
        int dimensions() const;
        int axes() const;
        
        Matrix<double, dimensions_, 1> point(double x) const;
        Matrix<double, dimensions_, 1> point(double x, double y) const;
        Matrix<double, dimensions_, 1> point(double x, double y, double z) const;
        
        Matrix<double, dimensions_, 1> vector(double x = 1) const;
        Matrix<double, dimensions_, 1> vector(double x, double y) const;
        Matrix<double, dimensions_, 1> vector(double x, double y, double z) const;

        Matrix<double, dimensions_, 1> xDirection() const;
        Matrix<double, dimensions_, 1> yDirection() const;
        Matrix<double, dimensions_, 1> zDirection() const;
        Matrix<double, dimensions_, 1> direction(int index) const;
        Matrix<double, dimensions_, 1> direction() const;

        Matrix<double, dimensions_, 1> normal() const;
        
        Datum<dimensions_, 1> xAxis() const;
        Datum<dimensions_, 1> yAxis() const;
        Datum<dimensions_, 1> zAxis() const;
        Datum<dimensions_, 1> axis(int index) const;
        Datum<dimensions_, 1> normalAxis() const;

        Datum<3, 2> xyPlane() const;
        Datum<3, 2> xzPlane() const;
        Datum<3, 2> yxPlane() const;
        Datum<3, 2> yzPlane() const;
        Datum<3, 2> zxPlane() const;
        Datum<3, 2> zyPlane() const;
        Datum<3, 2> plane(int first_index, int second_index) const;
        Datum<3, 2> normalPlane() const;

        template <class MatrixType, class VectorType>
        Datum<MatrixType::RowsAtCompileTime, axes_> transformed(
            const MatrixType& matrix,
            const VectorType& vector
        ) const;

        Datum<dimensions_, axes_> scaled(
            double scale,
            const Matrix<double, dimensions_, 1>& point
        ) const;
        
        Datum<dimensions_, axes_> scaled(double scale) const;

        Datum<dimensions_, axes_> translated(const Matrix<double, dimensions_, 1>& vector) const;

        template <int other_dimensions_, int other_axes_>
        Datum<dimensions_, axes_> translated(
            double distance,
            const Datum<other_dimensions_, other_axes_>& axis
        ) const;
        
        Datum<dimensions_, axes_> xReversed() const;
        Datum<dimensions_, axes_> yReversed() const;
        Datum<dimensions_, axes_> zReversed() const;
        Datum<dimensions_, axes_> reversed(int index) const;
        Datum<dimensions_, axes_> reversed() const;

        Datum<dimensions_, axes_> orientation() const;
    };

    typedef Datum<2, 2> Datum2d;
    typedef Datum<3, 3> Datum3d;
    typedef Datum<Dynamic, Dynamic> DatumXd;

    template <class TransformableType, int dimensions_, int axes_>
    auto operator*(const TransformableType& argument, const Datum<dimensions_, axes_>& datum) ->
        decltype(argument.transformed(datum.basis(), datum.origin()));

    template <class TransformableType, int dimensions_, int axes_>
    auto operator/(const TransformableType& argument, const Datum<dimensions_, axes_>& datum) ->
        decltype(
            argument.transformed(datum.inverseMatrix(), -datum.inverseMatrix() * datum.origin())
        );

    template <class TransformableType, int dimensions_, int axes_>
    auto operator%(const TransformableType& argument, const Datum<dimensions_, axes_>& datum) ->
        decltype(
            argument.transformed(
                datum.projectionMatrix(),
                datum.origin() - datum.projectionMatrix() * datum.origin()
            )
        );
}

////////// Specializations //////////

namespace opensolid
{
    template <>
    struct TypeName<Datum2d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };

    template <>
    struct TypeName<Datum3d>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };

    template <>
    struct TypeName<DatumXd>
    {
        OPENSOLID_CORE_EXPORT std::string operator()() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class DerivedType, class ResultType> template <int dimensions_, int axes_>
    inline ResultType Transformable<DerivedType, ResultType>::translated(
        double distance,
        const Datum<dimensions_, axes_>& axis
    ) const {
        assertCompatible<axes_, 1>();
        assert(axis.axes() == 1);
        assert(axis.direction().norm() == 1);
        Matrix<double, dimensions_, dimensions_> identity(axis.dimensions(), axis.dimensions());
        identity.setIdentity();
        return derived().transformed(identity, distance * axis.direction());
    }

    template <class DerivedType, class ResultType>
    inline ResultType Transformable<DerivedType, ResultType>::rotated(
        double angle,
        const Vector2d& point
    ) const {
        Matrix2d matrix;
        matrix = Rotation2Dd(angle);
        return derived().transformed(matrix, point - matrix * point);
    }

    template <class DerivedType, class ResultType> template <int dimensions_, int axes_>
    inline ResultType Transformable<DerivedType, ResultType>::rotated(
        double angle,
        const Datum<dimensions_, axes_>& axis
    ) const {
        Matrix3d matrix;
        matrix = AngleAxisd(angle, axis.direction());
        return derived().transformed(matrix, axis.origin() - matrix * axis.origin());
    }

    template <class DerivedType, class ResultType> template <int dimensions_, int axes_>
    inline ResultType Transformable<DerivedType, ResultType>::mirrored(
        const Datum<dimensions_, axes_>& plane
    ) const {
        Matrix<double, dimensions_, 1> normal = plane.normal();
        typedef Eigen::Matrix<double, dimensions_, dimensions_> Matrix;
        Matrix normal_matrix = 2 * normal * normal.transpose();
        Matrix matrix = Matrix::Identity(plane.dimensions(), plane.dimensions()) - normal_matrix;
        return derived().transformed(matrix, normal_matrix * plane.origin());
    }

    template <int dimensions_, int axes_>
    inline void Datum<dimensions_, axes_>::initialize(
        const Matrix<double, dimensions_, 1>& origin,
        const Matrix<double, dimensions_, axes_>& basis
    ) {
        assert(origin.size() >= 1);
        assert(basis.cols() >= 1);
        assert(origin.size() == basis.rows());
        _origin = origin;
        _basis = basis;
        _inverse_matrix = (_basis.transpose() * _basis).inverse() * _basis.transpose();
        _projection_matrix = _basis * _inverse_matrix;
    }

    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline void Datum<dimensions_, axes_>::initialize(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        assertCompatible<dimensions_, other_dimensions_>();
        assertCompatible<dimensions_>(other.dimensions());
        assertCompatible<axes_, other_axes_>();
        assertCompatible<axes_>(other.axes());
        _origin = other.origin();
        _basis = other.basis();
        _inverse_matrix = other.inverseMatrix();
        _projection_matrix = other.projectionMatrix();
    }

    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum() {}
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum(
        const Matrix<double, dimensions_, 1>& origin,
        const Matrix<double, dimensions_, axes_>& basis
    ) {initialize(origin, basis);}

    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum(
        const Matrix<double, dimensions_, 1>& origin,
        const Matrix<double, dimensions_, 1>& x_direction,
        const Matrix<double, dimensions_, 1>& y_direction
    ) {
        assertCompatible<2, axes_>();
        Matrix<double, dimensions_, axes_> basis(origin.size(), 2);
        basis.col(0) = x_direction;
        basis.col(1) = y_direction;
        initialize(origin, basis);
    }

    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum(
        const Matrix<double, dimensions_, 1>& origin,
        const Matrix<double, dimensions_, 1>& x_direction,
        const Matrix<double, dimensions_, 1>& y_direction,
        const Matrix<double, dimensions_, 1>& z_direction
    ) {
        assertCompatible<3, axes_>();
        Matrix<double, dimensions_, axes_> basis(origin.size(), 3);
        basis.col(0) = x_direction;
        basis.col(1) = y_direction;
        basis.col(2) = z_direction;
        initialize(origin, basis);
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum(const Datum<dimensions_, axes_>& other) {
        initialize(other);
    }
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>::Datum(const Datum<other_dimensions_, other_axes_>& other) {
        initialize(other);
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const Datum<dimensions_, axes_>& other
    ) {
        initialize(other);
        return *this;
    }
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        initialize(other);
        return *this;
    }
        
    template <int dimensions_, int axes_>
    inline const Matrix<double, dimensions_, 1>&
    Datum<dimensions_, axes_>::origin() const {return _origin;}
    
    template <int dimensions_, int axes_>
    inline const Matrix<double, dimensions_, axes_>&
    Datum<dimensions_, axes_>::basis() const {return _basis;}
    
    template <int dimensions_, int axes_>
    inline const Matrix<double, axes_, dimensions_>&
    Datum<dimensions_, axes_>::inverseMatrix() const {return _inverse_matrix;}
    
    template <int dimensions_, int axes_>
    inline const Matrix<double, dimensions_, dimensions_>&
    Datum<dimensions_, axes_>::projectionMatrix() const {return _projection_matrix;}
    
    template <int dimensions_, int axes_>
    inline int Datum<dimensions_, axes_>::dimensions() const {return basis().rows();}
    
    template <int dimensions_, int axes_>
    inline int Datum<dimensions_, axes_>::axes() const {return basis().cols();}

    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::point(double x) const {
        assert(axes() == 1);
        return origin() + basis() * x;
    }

    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::point(
        double x,
        double y
    ) const {
        assert(axes() == 2);
        return origin() + basis() * Vector2d(x, y);
    }
    
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::point(
        double x,
        double y,
        double z
    ) const {
        assert(axes() == 3);
        return origin() + basis() * Vector3d(x, y, z);
    }
        
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::vector(double x) const {
        assert(axes() == 1);
        return basis() * x;
    }
        
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::vector(
        double x,
        double y
    ) const {
        assert(axes() == 2);
        return basis() * Vector2d(x, y);
    }
    
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::vector(
        double x,
        double y,
        double z
    ) const {
        assertCompatible<axes_, 3>();
        assert(axes() == 3);
        return basis() * Vector3d(x, y, z);
    }

    template<int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::xDirection() const {
        return basis().col(0);
    }
    
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::yDirection() const {
        assert(axes() >= 2);
        return basis().col(1);
    }
    
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::zDirection() const {
        assert(axes() >= 3);
        return basis().col(2);
    }
    
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::direction(int index) const {
        assert(index >= 0 && index < axes());
        return basis().col(index);
    }
    
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::direction() const {
        assert(axes() == 1);
        return basis();
    }

    namespace
    {
        inline Vector2d datumNormal(const Datum<2, 1>& axis) {
            return axis.direction().unitOrthogonal();
        }

        inline Vector3d datumNormal(const Datum<3, 1>& axis) {
            return axis.direction().unitOrthogonal();
        }

        inline VectorXd datumNormal(const Datum<Dynamic, 1>& axis) {
            return axis.direction().unitOrthogonal();
        }

        inline Vector3d datumNormal(const Datum<3, 2>& plane) {
            return plane.xDirection().cross(plane.yDirection()).normalized();
        }

        inline VectorXd datumNormal(const DatumXd& datum) {
            if (datum.axes() == 1) {
                return datum.direction().unitOrthogonal();
            } else {
                assert(datum.dimensions() == 3);
                assert(datum.axes() == 2);
                Vector3d x_direction = datum.xDirection();
                Vector3d y_direction = datum.yDirection();
                return x_direction.cross(y_direction).normalized();
            }
        }
    }
    
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::normal() const {
        assert(axes() < dimensions());
        return datumNormal(*this);
    }
    
    template <int dimensions_, int axes_>
    Datum<dimensions_, 1> Datum<dimensions_, axes_>::xAxis() const {
        return Datum<dimensions_, 1>(origin(), xDirection());
    }
    
    template <int dimensions_, int axes_>
    Datum<dimensions_, 1> Datum<dimensions_, axes_>::yAxis() const {
        return Datum<dimensions_, 1>(origin(), yDirection());
    }
    
    template <int dimensions_, int axes_>
    Datum<dimensions_, 1> Datum<dimensions_, axes_>::zAxis() const {
        return Datum<dimensions_, 1>(origin(), zDirection());
    }
    
    template <int dimensions_, int axes_>
    Datum<dimensions_, 1> Datum<dimensions_, axes_>::axis(int index) const {
        return Datum<dimensions_, 1>(origin(), direction(index));
    }
    
    template <int dimensions_, int axes_>
    Datum<dimensions_, 1> Datum<dimensions_, axes_>::normalAxis() const {
        return Datum<dimensions_, 1>(origin(), normal());
    }

    template <int dimensions_, int axes_>
    inline Datum<3, 2> Datum<dimensions_, axes_>::xyPlane() const {
        assertCompatible<dimensions_, 3>();
        assert(dimensions() == 3);
        assertCompatible<axes_, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), xDirection(), yDirection());
    }

    template <int dimensions_, int axes_>
    inline Datum<3, 2> Datum<dimensions_, axes_>::xzPlane() const {
        assertCompatible<dimensions_, 3>();
        assert(dimensions() == 3);
        assertCompatible<axes_, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), xDirection(), zDirection());
    }

    template <int dimensions_, int axes_>
    inline Datum<3, 2> Datum<dimensions_, axes_>::yxPlane() const {
        assertCompatible<dimensions_, 3>();
        assert(dimensions() == 3);
        assertCompatible<axes_, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), yDirection(), xDirection());
    }

    template <int dimensions_, int axes_>
    inline Datum<3, 2> Datum<dimensions_, axes_>::yzPlane() const {
        assertCompatible<dimensions_, 3>();
        assert(dimensions() == 3);
        assertCompatible<axes_, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), yDirection(), zDirection());
    }

    template <int dimensions_, int axes_>
    inline Datum<3, 2> Datum<dimensions_, axes_>::zxPlane() const {
        assertCompatible<dimensions_, 3>();
        assert(dimensions() == 3);
        assertCompatible<axes_, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), zDirection(), xDirection());
    }

    template <int dimensions_, int axes_>
    inline Datum<3, 2> Datum<dimensions_, axes_>::zyPlane() const {
        assertCompatible<dimensions_, 3>();
        assert(dimensions() == 3);
        assertCompatible<axes_, 3>();
        assert(axes() == 3);
        return Datum<3, 2>(origin(), zDirection(), yDirection());
    }

    template <int dimensions_, int axes_>
    inline Datum<3, 2> Datum<dimensions_, axes_>::plane(int first_index, int second_index) const {
        assertCompatible<dimensions_, 3>();
        assert(dimensions() == 3);
        assertCompatible<axes_, 3>();
        assert(axes() == 3);
        assert(first_index != second_index);
        return Datum<3, 2>(origin(), direction(first_index), direction(second_index));
    }

    template <int dimensions_, int axes_>
    inline Datum<3, 2> Datum<dimensions_, axes_>::normalPlane() const {
        assertCompatible<dimensions_, 3>();
        assert(dimensions() == 3);
        Vector3d axial_direction(direction());
        Vector3d x_direction = axial_direction.unitOrthogonal();
        Vector3d y_direction = axial_direction.cross(x_direction).normalized();
        return Datum<3, 2>(origin(), x_direction, y_direction);
    }

    template <int dimensions_, int axes_> template <class MatrixType, class VectorType>
    inline Datum<MatrixType::RowsAtCompileTime, axes_> Datum<dimensions_, axes_>::transformed(
        const MatrixType& matrix,
        const VectorType& vector
    ) const {
        assertValidTransform<dimensions_>(dimensions(), matrix, vector);
        return Datum<MatrixType::RowsAtCompileTime, axes_>(
            matrix * origin() + vector,
            matrix * basis()
        );
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::scaled(
        double scale,
        const Matrix<double, dimensions_, 1>& point
    ) const {
        Datum<dimensions_, axes_> result(*this);
        result._basis *= scale;
        result._inverse_matrix /= scale;
        result._origin = point + scale * (origin() - point);
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::scaled(double scale) const {
        Datum<dimensions_, axes_> result(*this);
        result._basis *= scale;
        result._inverse_matrix /= scale;
        return result;
    }

    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::translated(
        const Matrix<double, dimensions_, 1>& vector
    ) const {
        Datum<dimensions_, axes_> result(*this);
        result._origin += vector;
        return result;
    }

    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::translated(
        double distance,
        const Datum<other_dimensions_, other_axes_>& axis
    ) const {
        assertCompatible<other_dimensions_, dimensions_>();
        assert(axis.dimensions() == dimensions());
        assertCompatible<other_axes_, 1>();
        assert(axis.axes() == 1);
        assert(axis.direction().norm() == One());
        Datum<dimensions_, axes_> result(*this);
        result._origin += distance * axis.direction();
        return result;
    }
        
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::xReversed() const {
        Datum<dimensions_, axes_> result(*this);
        result._basis.col(0) = -basis().row(0);
        result._inverse_matrix.row(0) = -inverseMatrix().row(0);
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::yReversed() const {
        Datum<dimensions_, axes_> result(*this);
        result._basis.col(1) = -basis().row(1);
        result._inverse_matrix.row(1) = -inverseMatrix().row(1);
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::zReversed() const {
        Datum<dimensions_, axes_> result(*this);
        result._basis.col(2) = -basis().row(2);
        result._inverse_matrix.row(2) = -inverseMatrix().row(2);
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::reversed(int index) const {
        Datum<dimensions_, axes_> result(*this);
        result._basis.col(index) = -basis().row(index);
        result._inverse_matrix.row(index) = -inverseMatrix().row(index);
        return result;
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::reversed() const {
        assertCompatible<axes_, 1>();
        assert(axes() == 1);
        Datum<dimensions_, axes_> result;
        result._origin = origin();
        result._basis = -basis();
        result._inverse_matrix = -inverseMatrix();
        result._projection_matrix = projectionMatrix();
        return result;
    }
    
    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_> Datum<dimensions_, axes_>::orientation() const {
        Datum<dimensions_, axes_> result(*this);
        result._origin.setZero();
        return result;
    }

    template <class TransformableType, int dimensions_, int axes_>
    inline auto operator*(const TransformableType& argument, const Datum<dimensions_, axes_>& datum) ->
        decltype(argument.transformed(datum.basis(), datum.origin())) {
        return argument.transformed(datum.basis(), datum.origin());
    }

    template <class TransformableType, int dimensions_, int axes_>
    inline auto operator/(
        const TransformableType& argument, const Datum<dimensions_, axes_>& datum
    ) -> decltype(
        argument.transformed(datum.inverseMatrix(), -datum.inverseMatrix() * datum.origin())
    ) {
        return argument.transformed(
            datum.inverseMatrix(),
            -datum.inverseMatrix() * datum.origin()
        );
    }

    template <class TransformableType, int dimensions_, int axes_>
    inline auto operator%(
        const TransformableType& argument, const Datum<dimensions_, axes_>& datum
    ) -> decltype(
        argument.transformed(
            datum.projectionMatrix(),
            datum.origin() - datum.projectionMatrix() * datum.origin()
        )
    ) {
        return argument.transformed(
            datum.projectionMatrix(),
            datum.origin() - datum.projectionMatrix() * datum.origin()
        );
    }
}
