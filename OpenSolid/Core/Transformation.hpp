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

#include <OpenSolid/Core/Matrix.hpp>
#include <OpenSolid/Core/Transformation/declarations.hpp>

namespace opensolid
{
    template <int iNumInputDimensions, int iNumOutputDimensions = iNumInputDimensions>
    class Transformation
    {
    public:
        typedef Matrix<double, iNumOutputDimensions, iNumInputDimensions> MatrixType;
        typedef Matrix<double, iNumOutputDimensions, 1> VectorType;
    private:
        MatrixType _matrix;
        VectorType _vector;
    public:
        Transformation(const MatrixType& matrix, const VectorType& vector);

        const MatrixType& matrix() const;
        const VectorType& vector() const;

        int numInputDimensions() const;
        int numOutputDimensions() const;

        Transformation<iNumInputDimensions, iNumOutputDimensions> linear() const;

        template <int iOtherNumInputDimensions, int iOtherNumOutputDimensions>
        Transformation<iOtherNumInputDimensions, iNumOutputDimensions> operator()(
            const Transformation<iOtherNumInputDimensions, iOtherNumOutputDimensions>& otherTransformation
        ) const;

        template <class TTransformable>
        typename Transformed<TTransformable, iNumOutputDimensions>::Type operator()(
            const TTransformable& transformable
        ) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    template <int iNumInputDimensions, int iNumOutputDimensions>
    Transformation<iNumInputDimensions, iNumOutputDimensions>::Transformation(
        const MatrixType& matrix,
        const VectorType& vector
    ) : _matrix(matrix),
        _vector(vector) {
    }

    template <int iNumInputDimensions, int iNumOutputDimensions>
    const MatrixType& Transformation<iNumInputDimensions, iNumOutputDimensions>::matrix() const {
        return _matrix;
    }
    
    template <int iNumInputDimensions, int iNumOutputDimensions>
    const VectorType& Transformation<iNumInputDimensions, iNumOutputDimensions>::vector() const {
        return _vector;
    }

    template <int iNumInputDimensions, int iNumOutputDimensions>
    int Transformation<iNumInputDimensions, iNumOutputDimensions>::numInputDimensions() const {
        return matrix().cols();
    }
    
    template <int iNumInputDimensions, int iNumOutputDimensions>
    int Transformation<iNumInputDimensions, iNumOutputDimensions>::numOutputDimensions() const {
        return matrix().rows();
    }

    Transformation<iNumInputDimensions, iNumOutputDimensions>
    Transformation<iNumInputDimensions, iNumOutputDimensions>::linear() const {
        return Transformation<iNumInputDimensions, iNumOutputDimensions>(
            matrix(),
            VectorType::Zero(vector().size())
        );
    }

    template <int iNumInputDimensions, int iNumOutputDimensions>
    template <int iOtherNumInputDimensions, int iOtherNumOutputDimensions>
    Transformation<iOtherNumInputDimensions, iNumOutputDimensions>
    Transformation<iNumInputDimensions, iNumOutputDimensions>::operator()(
        const Transformation<iOtherNumInputDimensions, iOtherNumOutputDimensions>& otherTransformation
    ) const {
        return Transformation<iOtherNumInputDimensions, iOtherNumOutputDimensions>(
            matrix() * otherTransformation.matrix(),
            matrix() * otherTransformation.vector() + vector()
        );
    }

    template <int iNumInputDimensions, int iNumOutputDimensions> template <class TTransformable>
    typename Transformed<TTransformable, iNumOutputDimensions>::Type
    Transformation<iNumInputDimensions, iNumOutputDimensions>::operator()(
        const TTransformable& transformable
    ) const {
        return transformable.transformed(*this);
    }
}
