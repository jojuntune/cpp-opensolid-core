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

#ifndef OPENSOLID__DATUM_HPP
#define OPENSOLID__DATUM_HPP

#include <functional>

#include <boost/functional/hash.hpp>

#include <OpenSolid/Common/config.hpp>
#include <OpenSolid/Common/Transformable.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>

namespace OpenSolid
{
    template <int dimensions_>
    class Axis;
    
    template <int dimensions_>
    class Plane;
    
    template <int dimensions_>
    class Frame;

    template <int dimensions_, int axes_>
    class CoordinateSystem;

    template <int dimensions_, int axes_>
    class Datum : public Transformable<Datum<dimensions_, axes_>>
    {
    private:
        void checkValidSizes() const;

        Matrix<double, dimensions_, 1> _origin;
        Matrix<double, dimensions_, axes_> _basis;
        Matrix<double, axes_, dimensions_> _inverse_matrix;
        Matrix<double, dimensions_, dimensions_> _projection_matrix;
    protected:
        template <int other_dimensions_, int other_axes_>
        friend class Datum;

        Datum(
            const Matrix<double, dimensions_, 1>& origin,
            const Matrix<double, dimensions_, axes_>& basis
        );
    public:
        Datum();
        
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
        
        Matrix<double, dimensions_, 1> vector(double x) const;
        Matrix<double, dimensions_, 1> vector(double x, double y) const;
        Matrix<double, dimensions_, 1> vector(double x, double y, double z) const;

        Matrix<double, dimensions_, 1> direction() const;
        Matrix<double, dimensions_, 1> normal() const;
        
        Axis<dimensions_> xAxis() const;
        Axis<dimensions_> yAxis() const;
        Axis<dimensions_> zAxis() const;
        Axis<dimensions_> axis(int index) const;
        Axis<dimensions_> normalAxis() const;

        Plane<dimensions_> xyPlane() const;
        Plane<dimensions_> xzPlane() const;
        Plane<dimensions_> yxPlane() const;
        Plane<dimensions_> yzPlane() const;
        Plane<dimensions_> zxPlane() const;
        Plane<dimensions_> zyPlane() const;
        Plane<dimensions_> plane(int first_index, int second_index) const;
        Plane<dimensions_> normalPlane() const;

        template <class MatrixType, class VectorType>
        Datum<MatrixType::RowsAtCompileTime, axes_> transformed(
            const MatrixType& matrix,
            const VectorType& vector
        ) const;

        Datum<dimensions_, axes_> orthonormalized() const;
        Datum<dimensions_, axes_> orientation() const;
        Frame<dimensions_> frame() const;
    };

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
    
    OPENSOLID_CORE_EXPORT MatrixXd orthonormalBasis(const MatrixXd& vectors);
}

namespace std
{
    template <int dimensions_, int axes_>
    struct hash<OpenSolid::Datum<dimensions_, axes_>> :
        public unary_function<OpenSolid::Datum<dimensions_, axes_>, size_t>
    {
        std::size_t operator()(const OpenSolid::Datum<dimensions_, axes_>& argument) const;
    };

    template <int dimensions_, int axes_>
    struct equal_to<OpenSolid::Datum<dimensions_, axes_>> :
        public binary_function<
            OpenSolid::Datum<dimensions_, axes_>,
            OpenSolid::Datum<dimensions_, axes_>,
            bool
        >
    {
        bool operator()(
            const OpenSolid::Datum<dimensions_, axes_>& first_argument,
            const OpenSolid::Datum<dimensions_, axes_>& second_argument
        ) const;
    };
}

namespace boost
{
    template <int dimensions_, int axes_>
    struct hash<OpenSolid::Datum<dimensions_, axes_>> :
        public std::hash<OpenSolid::Datum<dimensions_, axes_>>
    {
    };
}

////////// Implementation //////////

#include <OpenSolid/Datum/Axis.hpp>
#include <OpenSolid/Datum/Plane.hpp>
#include <OpenSolid/Datum/Frame.hpp>
#include <OpenSolid/Datum/CoordinateSystem.hpp>

namespace OpenSolid
{
    template <class DerivedType, class ResultType> template <int dimensions_, int axes_>
    inline ResultType Transformable<DerivedType, ResultType>::translated(
        double distance,
        const Datum<dimensions_, axes_>& axis
    ) const {
        Matrix<double, dimensions_, dimensions_> identity(axis.dimensions(), axis.dimensions());
        identity.setIdentity();
        return derived().transformed(identity, distance * axis.direction());
    }

    template <class DerivedType, class ResultType>
    inline ResultType Transformable<DerivedType, ResultType>::rotated(
        double angle,
        const Vector2d& point
    ) const {
        Matrix2d matrix(Rotation2Dd(angle));
        return derived().transformed(matrix, point - matrix * point);
    }

    template <class DerivedType, class ResultType> template <int dimensions_, int axes_>
    inline ResultType Transformable<DerivedType, ResultType>::rotated(
        double angle,
        const Datum<dimensions_, axes_>& axis
    ) const {
        Matrix3d matrix(AngleAxisd(angle, axis.direction()));
        return derived().transformed(matrix, axis.origin() - matrix * axis.origin());
    }

    template <class DerivedType, class ResultType> template <int dimensions_, int axes_>
    inline ResultType Transformable<DerivedType, ResultType>::mirrored(
        const Datum<dimensions_, axes_>& datum
    ) const {
        Matrix<double, dimensions_, 1> normal = datum.normal();
        typedef Eigen::Matrix<double, dimensions_, dimensions_> Matrix;
        Matrix normal_matrix = 2 * normal * normal.transpose();
        Matrix matrix = Matrix::Identity(datum.dimensions(), datum.dimensions()) - normal_matrix;
        return derived().transformed(matrix, normal_matrix * datum.origin());
    }

    template <int dimensions_, int axes_>
    inline void Datum<dimensions_, axes_>::checkValidSizes() const {
        static_assert(
            dimensions_ >= 1 || dimensions_ == Dynamic,
            "Datum must have at least one dimension"
        );
        assert(dimensions() >= 1 && "Datum must have at least one dimension");
        static_assert(
            axes_ >= 1 || axes_ == Dynamic,
            "Datum must have at least one axis"
        );
        assert(axes() >= 1 && "Datum must have at least one axis");
    }

    template <int dimensions_, int axes_>
    Datum<dimensions_, axes_>::Datum(
        const Matrix<double, dimensions_, 1>& origin,
        const Matrix<double, dimensions_, axes_>& basis
    ) : _origin(origin),
        _basis(basis),
        _inverse_matrix((_basis.transpose() * _basis).inverse() * _basis.transpose()),
        _projection_matrix(_basis * _inverse_matrix) {checkValidSizes();}

    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum() {}
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>::Datum(const Datum<dimensions_, axes_>& other) :
        _origin(other.origin()),
        _basis(other.basis()),
        _inverse_matrix(other.inverseMatrix()),
        _projection_matrix(other.projectionMatrix()) {}
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>::Datum(const Datum<other_dimensions_, other_axes_>& other) {
        assertCompatible<dimensions_, other_dimensions_>();
        assertCompatible<axes_, other_axes_>();
        assertCompatible<dimensions_>(other.dimensions());
        assertCompatible<axes_>(other.axes());
        _origin = other.origin();
        _basis = other.basis();
        _inverse_matrix = other.inverseMatrix();
        _projection_matrix = other.projectionMatrix();
    }
        
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const Datum<dimensions_, axes_>& other
    ) {
        _origin = other.origin();
        _basis = other.basis();
        _inverse_matrix = other.inverseMatrix();
        _projection_matrix = other.projectionMatrix();
        return *this;
    }
    
    template <int dimensions_, int axes_> template <int other_dimensions_, int other_axes_>
    inline Datum<dimensions_, axes_>& Datum<dimensions_, axes_>::operator=(
        const Datum<other_dimensions_, other_axes_>& other
    ) {
        assertCompatible<dimensions_, other_dimensions_>();
        assertCompatible<axes_, other_axes_>();
        assertCompatible<dimensions_>(other.dimensions());
        assertCompatible<axes_>(other.axes());
        _origin = other.origin();
        _basis = other.basis();
        _inverse_matrix = other.inverseMatrix();
        _projection_matrix = other.projectionMatrix();
        return *this;
    }
        
    template <int dimensions_, int axes_>
    inline const Matrix<double, dimensions_, 1>& Datum<dimensions_, axes_>::origin() const {
        return _origin;
    }
    
    template <int dimensions_, int axes_>
    inline const Matrix<double, dimensions_, axes_>& Datum<dimensions_, axes_>::basis() const {
        return _basis;
    }
    
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
        assertCompatible<axes_, 1>();
        assert(axes() == 1);
        return origin() + basis() * x;
    }
        
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::point(
        double x,
        double y
    ) const {
        assertCompatible<axes_, 2>();
        assert(axes() == 2);
        return origin() + basis() * Vector2d(x, y);
    }
    
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::point(
        double x,
        double y,
        double z
    ) const {
        assertCompatible<axes_, 3>();
        assert(axes() == 3);
        return origin() + basis() * Vector3d(x, y, z);
    }
        
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::vector(double x) const {
        assertCompatible<axes_, 1>();
        assert(axes() == 1);
        return basis() * x;
    }
        
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1>  Datum<dimensions_, axes_>::vector(
        double x,
        double y
    ) const {
        assertCompatible<axes_, 2>();
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
    
    template <int dimensions_, int axes_>
    inline Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::direction() const {
        assertCompatible<axes_, 1>();
        assert(axes() == 1);
        assert(basis().squaredNorm() == One());
        return basis();
    }

    namespace
    {
        template <int dimensions_, int axes_>
        inline Matrix<double, dimensions_, 1, 0, dimensions_, 1>
        datumNormal(const Datum<dimensions_, axes_>& datum) {
            return orthonormalBasis(datum.basis()).col(datum.axes());
        }

        template <>
        inline Matrix<double, 2, 1, 0, 2, 1> datumNormal(const Datum<2, 1>& datum) {
            return datum.basis().unitOrthogonal();
        }

        template <>
        inline Matrix<double, 3, 1, 0, 3, 1> datumNormal(const Datum<3, 1>& datum) {
            return datum.basis().unitOrthogonal();
        }

        template <>
        inline Matrix<double, Dynamic, 1, 0, Dynamic, 1> datumNormal(
            const Datum<Dynamic, 1>& datum
        ) {return datum.basis().unitOrthogonal();}

        template <>
        inline Matrix<double, 3, 1, 0, 3, 1> datumNormal(const Datum<3, 2>& datum) {
            return datum.basis().col(0).cross(datum.basis().col(1)).normalized();
        }
    }
    
    template <int dimensions_, int axes_>
    Matrix<double, dimensions_, 1> Datum<dimensions_, axes_>::normal() const {
        static_assert(
            axes_ < dimensions_ || axes_ == Dynamic || dimensions_ == Dynamic,
            "Normal vector only exists for datums with fewer axes than dimensions"
        );
        assert(
            axes() < dimensions() &&
            "Normal vector only exists for datums with fewer axes than dimensions"
        );
        return datumNormal(*this);
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::xAxis() const {
        assert(basis().isUnitary());
        return Axis<dimensions_>(origin(), basis().col(0));
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::yAxis() const {
        assert(basis().isUnitary());
        static_assert(axes_ == Dynamic || axes_ >= 2, "No Y axis exists");
        assert(axes() >= 2 && "No Y axis exists");
        return Axis<dimensions_>(origin(), basis().col(1));
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::zAxis() const {
        assert(basis().isUnitary());
        static_assert(axes_ == Dynamic || axes_ >= 3, "No Z axis exists");
        assert(axes() >= 3 && "No Z axis exists");
        return Axis<dimensions_>(origin(), basis().col(2));
    }
    
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::axis(int index) const {
        assert(basis().isUnitary());
        assert(index >= 0 && index < axes() && "Axis index out of range");
        return Axis<dimensions_>(origin(), basis().col(index));
    }
        
    template <int dimensions_, int axes_>
    inline Axis<dimensions_> Datum<dimensions_, axes_>::normalAxis() const {
        assertCompatible<axes_, (dimensions_ == Dynamic ? Dynamic : dimensions_ - 1)>();
        assert(axes() == dimensions() - 1);
        return Axis<dimensions_>(origin(), normal());
    }
    
    template <int dimensions_, int axes_>
    inline Plane<dimensions_> Datum<dimensions_, axes_>::xyPlane() const {
        assertCompatible<dimensions_, 3>();
        assertCompatible<axes_, 3>();
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<dimensions_>(origin(), basis().col(0), basis().col(1));
    }
    
    template <int dimensions_, int axes_>
    inline Plane<dimensions_> Datum<dimensions_, axes_>::xzPlane() const {
        assertCompatible<dimensions_, 3>();
        assertCompatible<axes_, 3>();
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<3>(origin(), basis().col(0), basis().col(2));
    }
    
    template <int dimensions_, int axes_>
    inline Plane<dimensions_> Datum<dimensions_, axes_>::yxPlane() const {
        assertCompatible<dimensions_, 3>();
        assertCompatible<axes_, 3>();
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<3>(origin(), basis().col(1), basis().col(0));
    }
    
    template <int dimensions_, int axes_>
    inline Plane<dimensions_> Datum<dimensions_, axes_>::yzPlane() const {
        assertCompatible<dimensions_, 3>();
        assertCompatible<axes_, 3>();
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<3>(origin(), basis().col(1), basis().col(2));
    }
    
    template <int dimensions_, int axes_>
    inline Plane<dimensions_> Datum<dimensions_, axes_>::zxPlane() const {
        assertCompatible<dimensions_, 3>();
        assertCompatible<axes_, 3>();
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<3>(origin(), basis().col(2), basis().col(0));
    }
    
    template <int dimensions_, int axes_>
    inline Plane<dimensions_> Datum<dimensions_, axes_>::zyPlane() const {
        assertCompatible<dimensions_, 3>();
        assertCompatible<axes_, 3>();
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        return Plane<3>(origin(), basis().col(2), basis().col(1));
    }

    template <int dimensions_, int axes_>
    inline Plane<dimensions_> Datum<dimensions_, axes_>::plane(
        int first_index,
        int second_index
    ) const {
        assertCompatible<dimensions_, 3>();
        assertCompatible<axes_, 3>();
        assert(dimensions() == 3 && axes() == 3);
        assert(basis().isUnitary());
        assert(first_index >= 0 && first_index < 3);
        assert(second_index >= 0 && second_index < 3);
        assert(first_index != second_index);
        return Plane<3>(origin(), basis().col(first_index), basis().col(second_index));
    }
    
    template <int dimensions_, int axes_>
    inline Plane<dimensions_> Datum<dimensions_, axes_>::normalPlane() const {
        assertCompatible<axes_, 1>();
        assert(axes() == 1);
        return Plane<dimensions_>(origin(), direction());
    }

    template <int dimensions_, int axes_> template <class MatrixType, class VectorType>
    Datum<MatrixType::RowsAtCompileTime, axes_> Datum<dimensions_, axes_>::transformed(
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
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::orthonormalized() const {
        return Datum<dimensions_, axes_>(
            origin(),
            orthonormalBasis(basis()).leftCols(basis().cols())
        );
    }
    
    template <int dimensions_, int axes_>
    inline Datum<dimensions_, axes_> Datum<dimensions_, axes_>::orientation() const {
        Datum<dimensions_, axes_> result(*this);
        result._origin.setZero();
        return result;
    }

    template <int dimensions_, int axes_>
    inline Frame<dimensions_> Datum<dimensions_, axes_>::frame() const {
        return Frame<dimensions_>(origin(), orthonormalBasis(basis()));
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

namespace std
{
    template <int dimensions_, int axes_>
    inline size_t hash<OpenSolid::Datum<dimensions_, axes_>>::operator()(
        const OpenSolid::Datum<dimensions_, axes_>& argument
    ) const {
        size_t result = 0;
        boost::hash_combine(
            result,
            hash<Eigen::Matrix<double, dimensions_, 1>>()(argument.origin())
        );
        boost::hash_combine(
            result,
            hash<Eigen::Matrix<double, dimensions_, axes_>>()(argument.basis())
        );
        return result;
    }

    template <int dimensions_, int axes_>
    inline bool equal_to<OpenSolid::Datum<dimensions_, axes_>>::operator()(
        const OpenSolid::Datum<dimensions_, axes_>& first_argument,
        const OpenSolid::Datum<dimensions_, axes_>& second_argument
    ) const {
        return first_argument.origin() == second_argument.origin() &&
            first_argument.basis() == second_argument.basis();
    }
}

#endif
