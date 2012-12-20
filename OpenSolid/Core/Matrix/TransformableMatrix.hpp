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

#include <OpenSolid/Core/Transformable.hpp>
#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    template <class TMatrix>
    class TransformableMatrix : public Transformable<TransformableMatrix<TMatrix>>
    {
    private:
        const TMatrix& _matrix;
    public:
        TransformableMatrix(const TMatrix& matrix);

        template <class TTransformMatrix, class TTransformVector>
        Matrix<
            typename TMatrix::Scalar,
            TTransformMatrix::RowsAtCompileTime,
            TMatrix::ColsAtCompileTime
        >
        transformed(
            const TTransformMatrix& transformMatrix,
            const TTransformVector& transformVector
        ) const;
    };
}

////////// Specializations //////////

namespace opensolid
{
    template <class TMatrix, int iTransformedNumDimensions>
    struct Transformed<TransformableMatrix<TMatrix>, iTransformedNumDimensions>
    {
        typedef Matrix<
            typename TMatrix::Scalar,
            iTransformedNumDimensions,
            TMatrix::ColsAtCompileTime
        > Type;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <class TMatrix>
    TransformableMatrix<TMatrix>::TransformableMatrix(const TMatrix& matrix) :
        _matrix(matrix) {
    }

    template <class TMatrix> template <class TTransformMatrix, class TTransformVector>
    Matrix<
        typename TMatrix::Scalar,
        TTransformMatrix::RowsAtCompileTime,
        TMatrix::ColsAtCompileTime
    >
    TransformableMatrix<TMatrix>::transformed(
        const TTransformMatrix& transformMatrix,
        const TTransformVector& transformVector
    ) const {
        assertValidTransform<TMatrix::RowsAtCompileTime>(
            _matrix.rows(),
            transformMatrix,
            transformVector
        );
        return (transformMatrix.template cast<typename TMatrix::Scalar>() * _matrix).colwise() +
            transformVector.template cast<typename TMatrix::Scalar>();
    }
}