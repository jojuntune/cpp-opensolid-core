/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2013 by Ian Mackenzie                                         *
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
        typename MatrixTraits<TDerived>::ScalarType
        MatrixDeterminantFunction<1, 1>::operator()(const MatrixInterface<TDerived>& matrix) const {
            if (matrix.rows() != 1 || matrix.cols() != 1) {
                assert(false);
                return 0.0;
            }

            return matrix.value();
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType
        MatrixDeterminantFunction<2, 2>::operator()(const MatrixInterface<TDerived>& matrix) const {
            if (matrix.rows() != 2 || matrix.cols() != 2) {
                assert(false);
                return 0.0;
            }
            
            return matrix.coeff(0, 0) * matrix.coeff(1, 1) -
                matrix.coeff(1, 0) * matrix.coeff(0, 1);
        }

        template <class TDerived>
        inline
        typename MatrixTraits<TDerived>::ScalarType
        MatrixDeterminantFunction<3, 3>::operator()(const MatrixInterface<TDerived>& matrix) const {
            if (matrix.rows() != 3 || matrix.cols() != 3) {
                assert(false);
                return 0.0;
            }

            double coeff00 = matrix.coeff(0, 0);
            double coeff10 = matrix.coeff(1, 0);
            double coeff20 = matrix.coeff(2, 0);
            double coeff01 = matrix.coeff(0, 1);
            double coeff11 = matrix.coeff(1, 1);
            double coeff21 = matrix.coeff(2, 1);
            double coeff02 = matrix.coeff(0, 2);
            double coeff12 = matrix.coeff(1, 2);
            double coeff22 = matrix.coeff(2, 2);

            return coeff00 * (coeff11 * coeff22 - coeff12 * coeff21) +
                coeff01 * (coeff12 * coeff20 - coeff10 * coeff22 ) +
                coeff02 * (coeff10 * coeff21 - coeff11 * coeff20);
        }

        template <class TDerived>
        typename MatrixTraits<TDerived>::ScalarType
        MatrixDeterminantFunction<-1, -1>::operator()(
            const MatrixInterface<TDerived>& matrix
        ) const {
            if (matrix.rows() == 1 && matrix.cols() == 1) {
                return MatrixDeterminantFunction<1, 1>(matrix);
            } else if (matrix.rows() == 2 && matrix.cols() == 2) {
                return MatrixDeterminantFunction<2, 2>(matrix);
            } else if (matrix.rows() == 3 && matrix.cols() == 3) {
                return MatrixDeterminantFunction<3, 3>(matrix);
            } else {
                assert(false);
                return typename MatrixTraits<TDerived>::ScalarType();
            }
        }
    }
}
