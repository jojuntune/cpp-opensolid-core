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

#include <OpenSolid/config.hpp>
#include <OpenSolid/declarations.hpp>
#include <OpenSolid/Common/Transformable.hpp>
#include <OpenSolid/Matrix/Matrix.hpp>

namespace OpenSolid
{
    template <int dimensions_, int axes_>
    struct TransformedDatum
    {
        static const bool dynamic = (dimensions_ == Dynamic || axes_ == Dynamic);
        typedef Datum<(dynamic ? Dynamic : dimensions_), (dynamic ? Dynamic : axes_)> Type;
    };

    template <int dimensions_, int axes_>
    class Datum : public Transformable<Datum<dimensions_, axes_>>
    {
    private:
        Matrix<double, dimensions_, 1> _origin;
        Matrix<double, dimensions_, axes_> _basis;
        Matrix<double, axes_, dimensions_> _inverse_matrix;
        Matrix<double, dimensions_, dimensions_> _projection_matrix;
    protected:
        template <int other_dimensions_, int other_axes_>
        friend class Datum;

        OPENSOLID_CORE_EXPORT Datum(
            const Matrix<double, dimensions_, 1>& origin,
            const Matrix<double, dimensions_, axes_>& basis
        );
    public:
        typedef Datum<dimensions_, (dimensions_ == Dynamic ? Dynamic : 1)> AxisType;
        typedef Datum<dimensions_, (dimensions_ == Dynamic ? Dynamic : dimensions_ - 1)> PlaneType;

        OPENSOLID_CORE_EXPORT Datum();
        
        OPENSOLID_CORE_EXPORT Datum(const Datum<dimensions_, axes_>& other);
        
        template <int other_dimensions_, int other_axes_>
        Datum(const Datum<other_dimensions_, other_axes_>& other);
        
        OPENSOLID_CORE_EXPORT Datum<dimensions_, axes_>& operator=(
            const Datum<dimensions_, axes_>& other
        );
        
        template <int other_dimensions_, int other_axes_>
        Datum<dimensions_, axes_>& operator=(const Datum<other_dimensions_, other_axes_>& other);
        
        const Matrix<double, dimensions_, 1>& origin() const;
        const Matrix<double, dimensions_, axes_>& basis() const;
        const Matrix<double, axes_, dimensions_>& inverseMatrix() const;
        const Matrix<double, dimensions_, dimensions_>& projectionMatrix() const;
        
        int dimensions() const;
        int axes() const;
        
        OPENSOLID_CORE_EXPORT Matrix<double, dimensions_, 1> point(double x) const;
        OPENSOLID_CORE_EXPORT Matrix<double, dimensions_, 1> point(double x, double y) const;
        
        OPENSOLID_CORE_EXPORT Matrix<double, dimensions_, 1> point(
            double x,
            double y,
            double z
        ) const;
        
        OPENSOLID_CORE_EXPORT Matrix<double, dimensions_, 1> vector(double x) const;
        OPENSOLID_CORE_EXPORT Matrix<double, dimensions_, 1> vector(double x, double y) const;

        OPENSOLID_CORE_EXPORT Matrix<double, dimensions_, 1> vector(
            double x,
            double y,
            double z
        ) const;

        OPENSOLID_CORE_EXPORT Matrix<double, dimensions_, 1> direction() const;
        OPENSOLID_CORE_EXPORT Matrix<double, dimensions_, 1> normal() const;
        
        OPENSOLID_CORE_EXPORT AxisType xAxis() const;
        OPENSOLID_CORE_EXPORT AxisType yAxis() const;
        OPENSOLID_CORE_EXPORT AxisType zAxis() const;
        OPENSOLID_CORE_EXPORT AxisType axis(int index) const;
        OPENSOLID_CORE_EXPORT AxisType normalAxis() const;

        OPENSOLID_CORE_EXPORT PlaneType xyPlane() const;
        OPENSOLID_CORE_EXPORT PlaneType xzPlane() const;
        OPENSOLID_CORE_EXPORT PlaneType yxPlane() const;
        OPENSOLID_CORE_EXPORT PlaneType yzPlane() const;
        OPENSOLID_CORE_EXPORT PlaneType zxPlane() const;
        OPENSOLID_CORE_EXPORT PlaneType zyPlane() const;
        OPENSOLID_CORE_EXPORT PlaneType plane(int first_index, int second_index) const;
        OPENSOLID_CORE_EXPORT PlaneType normalPlane() const;

        template <class MatrixType, class VectorType>
        typename TransformedDatum<MatrixType::RowsAtCompileTime, axes_>::Type transformed(
            const MatrixType& matrix,
            const VectorType& vector
        ) const;

        OPENSOLID_CORE_EXPORT Datum<dimensions_, axes_> orthonormalized() const;
        OPENSOLID_CORE_EXPORT Datum<dimensions_, axes_> orientation() const;
        OPENSOLID_CORE_EXPORT Datum<dimensions_, dimensions_> frame() const;
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

////////// Implementation //////////

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

    template <int dimensions_, int axes_> template <class MatrixType, class VectorType>
    typename TransformedDatum<MatrixType::RowsAtCompileTime, axes_>::Type
    Datum<dimensions_, axes_>::transformed(
        const MatrixType& matrix,
        const VectorType& vector
    ) const {
        assertValidTransform<dimensions_>(dimensions(), matrix, vector);
        return typename TransformedDatum<MatrixType::RowsAtCompileTime, axes_>::Type(
            matrix * origin() + vector,
            matrix * basis()
        );
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

#endif
