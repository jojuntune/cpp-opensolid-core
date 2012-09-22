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

#include "Matrix.hpp"

////////// Implementation //////////

namespace opensolid
{
    template <int dimensions_, int axes_>
    class Datum;

    template <class DerivedType, class ResultType = DerivedType>
    class Transformable
    {
    private:
        const DerivedType& derived() const;
    public:
        template <class PointType>
        ResultType scaled(double scale, const EigenBase<PointType>& point) const;

        template <class VectorType>
        ResultType translated(const EigenBase<VectorType>& vector) const;

        template <int dimensions_, int axes_>
        ResultType translated(double distance, const Datum<dimensions_, axes_>& axis) const;

        ResultType rotated(double angle, const Vector2d& point) const;

        template <int dimensions_, int axes_>
        ResultType rotated(double angle, const Datum<dimensions_, axes_>& axis) const;

        template <int dimensions_, int axes_>
        ResultType mirrored(const Datum<dimensions_, axes_>& plane) const;
    };

    template <class ArgumentType>
    class TransformableMatrix : public Transformable<
        TransformableMatrix<ArgumentType>,
        typename ArgumentType::PlainObject
    >
    {
    private:
        const ArgumentType& _argument;
    public:
        TransformableMatrix(const ArgumentType& argument);

        template <class MatrixType, class VectorType>
        Matrix<
            typename ArgumentType::Scalar,
            MatrixType::RowsAtCompileTime,
            ArgumentType::ColsAtCompileTime
        > transformed(const MatrixType& matrix, const VectorType& vector) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class DerivedType, class ResultType>
    inline const DerivedType& Transformable<DerivedType, ResultType>::derived() const {
        return static_cast<const DerivedType&>(*this);
    }

    template <class DerivedType, class ResultType> template <class PointType>
    inline ResultType Transformable<DerivedType, ResultType>::scaled(
        double scale,
        const EigenBase<PointType>& point
    ) const {
        static const int static_dimensions = PointType::SizeAtCompileTime;
        Matrix<double, static_dimensions, static_dimensions> identity(point.size(), point.size());
        identity.setIdentity();
        return derived().transformed(scale * identity, point.derived() - scale * point.derived());
    }

    template <class DerivedType, class ResultType> template <class VectorType>
    inline ResultType Transformable<DerivedType, ResultType>::translated(
        const EigenBase<VectorType>& vector
    ) const {
        static const int dimensions = VectorType::SizeAtCompileTime;
        Matrix<double, dimensions, dimensions> identity(vector.size(), vector.size());
        identity.setIdentity();
        return derived().transformed(identity, vector.derived());
    }

    template <class ArgumentType>
    TransformableMatrix<ArgumentType>::TransformableMatrix(const ArgumentType& argument) :
        _argument(argument) {}

    template <class ArgumentType> template <class MatrixType, class VectorType>
    inline Matrix<
        typename ArgumentType::Scalar,
        MatrixType::RowsAtCompileTime,
        ArgumentType::ColsAtCompileTime
    > TransformableMatrix<ArgumentType>::transformed(
        const MatrixType& matrix,
        const VectorType& vector
    ) const {
        opensolid::assertValidTransform<ArgumentType::RowsAtCompileTime>(
            _argument.rows(),
            matrix,
            vector
        );
        return (matrix.template cast<typename ArgumentType::Scalar>() * _argument).colwise() +
            vector.template cast<typename ArgumentType::Scalar>();
    }
}

#include "Datum.hpp"
