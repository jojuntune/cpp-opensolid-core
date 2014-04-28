/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Matrix/MatrixDeterminantFunction.definitions.hpp>

#include <OpenSolid/Core/Matrix/MatrixInterface.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixDeterminantFunction<1, 1>::operator()(const MatrixInterface<TDerived>& matrix) const {
            if (matrix.numRows() != 1 || matrix.numColumns() != 1) {
                assert(false);
                return 0.0;
            }

            return matrix.value();
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixDeterminantFunction<2, 2>::operator()(const MatrixInterface<TDerived>& matrix) const {
            if (matrix.numRows() != 2 || matrix.numColumns() != 2) {
                assert(false);
                return 0.0;
            }
            
            return matrix.component(0, 0) * matrix.component(1, 1) -
                matrix.component(1, 0) * matrix.component(0, 1);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixDeterminantFunction<3, 3>::operator()(const MatrixInterface<TDerived>& matrix) const {
            if (matrix.numRows() != 3 || matrix.numColumns() != 3) {
                assert(false);
                return 0.0;
            }

            double component00 = matrix.component(0, 0);
            double component10 = matrix.component(1, 0);
            double component20 = matrix.component(2, 0);
            double component01 = matrix.component(0, 1);
            double component11 = matrix.component(1, 1);
            double component21 = matrix.component(2, 1);
            double component02 = matrix.component(0, 2);
            double component12 = matrix.component(1, 2);
            double component22 = matrix.component(2, 2);

            return component00 * (component11 * component22 - component12 * component21) +
                component01 * (component12 * component20 - component10 * component22 ) +
                component02 * (component10 * component21 - component11 * component20);
        }

        template <class TDerived>
        typename MatrixTraits<TDerived>::PlainScalarType
        MatrixDeterminantFunction<-1, -1>::operator()(
            const MatrixInterface<TDerived>& matrix
        ) const {
            if (matrix.numRows() == 1 && matrix.numColumns() == 1) {
                return MatrixDeterminantFunction<1, 1>()(matrix);
            } else if (matrix.numRows() == 2 && matrix.numColumns() == 2) {
                return MatrixDeterminantFunction<2, 2>()(matrix);
            } else if (matrix.numRows() == 3 && matrix.numColumns() == 3) {
                return MatrixDeterminantFunction<3, 3>()(matrix);
            } else {
                assert(false);
                return typename MatrixTraits<TDerived>::PlainScalarType();
            }
        }
    }
}
