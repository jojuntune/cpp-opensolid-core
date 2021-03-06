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

#include <OpenSolid/Core/Matrix/MatrixInverseFunction.definitions.hpp>

#include <OpenSolid/Core/Matrix/MatrixInterface.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TDerived>
        inline
        Matrix<typename MatrixTraits<TDerived>::PlainScalar, 1, 1>
        MatrixInverseFunction<1>::operator()(const MatrixInterface<TDerived>& matrix) const {
            typedef typename MatrixTraits<TDerived>::PlainScalar ScalarType;

            if (matrix.numRows() != 1 || matrix.numColumns() != 1) {
                assert(false);
                return Matrix<ScalarType, 1, 1>();
            }

            ScalarType value = matrix.value();
            if (value == 0.0) {
                assert(false);
                return Matrix<ScalarType, 1, 1>();
            }

            Matrix<ScalarType, 1, 1> result(1.0 / value);
            assert(checkIdentity(result * matrix));
            return result;
        }

        template <class TDerived>
        Matrix<typename MatrixTraits<TDerived>::PlainScalar, 2, 2>
        MatrixInverseFunction<2>::operator()(const MatrixInterface<TDerived>& matrix) const {
            typedef typename MatrixTraits<TDerived>::PlainScalar ScalarType;

            if (matrix.numRows() != 2 || matrix.numColumns() != 2) {
                assert(false);
                return Matrix<ScalarType, 2, 2>::ZERO();
            }

            ScalarType component00 = matrix.component(0, 0);
            ScalarType component10 = matrix.component(1, 0);
            ScalarType component01 = matrix.component(0, 1);
            ScalarType component11 = matrix.component(1, 1);

            ScalarType determinant = component00 * component11 - component01 * component10;
            if (determinant == 0.0) {
                assert(false);
                return Matrix<ScalarType, 2, 2>::ZERO();
            }
            ScalarType inverseDeterminant = 1.0 / determinant;

            Matrix<ScalarType, 2, 2> result;
            result.component(0, 0) = inverseDeterminant * component11;
            result.component(1, 0) = -inverseDeterminant * component10;
            result.component(0, 1) = -inverseDeterminant * component01;
            result.component(1, 1) = inverseDeterminant * component00;

            assert(checkIdentity(result * matrix));

            return result;
        }

        template <class TDerived>
        Matrix<typename MatrixTraits<TDerived>::PlainScalar, 3, 3>
        MatrixInverseFunction<3>::operator()(const MatrixInterface<TDerived>& matrix) const {
            typedef typename MatrixTraits<TDerived>::PlainScalar ScalarType;

            if (matrix.numRows() != 3 || matrix.numColumns() != 3) {
                assert(false);
                return Matrix<ScalarType, 3, 3>::ZERO();
            }

            ScalarType component00 = matrix.component(0, 0);
            ScalarType component10 = matrix.component(1, 0);
            ScalarType component20 = matrix.component(2, 0);
            ScalarType component01 = matrix.component(0, 1);
            ScalarType component11 = matrix.component(1, 1);
            ScalarType component21 = matrix.component(2, 1);
            ScalarType component02 = matrix.component(0, 2);
            ScalarType component12 = matrix.component(1, 2);
            ScalarType component22 = matrix.component(2, 2);

            ScalarType cofactor00 = component11 * component22 - component12 * component21;
            ScalarType cofactor01 = component12 * component20 - component10 * component22;
            ScalarType cofactor02 = component10 * component21 - component11 * component20;

            ScalarType determinant = component00 * cofactor00 + component01 * cofactor01 +
                component02 * cofactor02;
            if (determinant == 0.0) {
                assert(false);
                return Matrix<ScalarType, 3, 3>::ZERO();
            }
            ScalarType inverseDeterminant = 1.0 / determinant;

            Matrix<ScalarType, 3, 3> result;
            result.component(0, 0) = inverseDeterminant * cofactor00;
            result.component(1, 0) = inverseDeterminant * cofactor01;
            result.component(2, 0) = inverseDeterminant * cofactor02;
            result.component(0, 1) = inverseDeterminant *
                (component02 * component21 - component01 * component22);
            result.component(1, 1) = inverseDeterminant *
                (component00 * component22 - component02 * component20);
            result.component(2, 1) = inverseDeterminant *
                (component01 * component20 - component00 * component21);
            result.component(0, 2) = inverseDeterminant *
                (component01 * component12 - component02 * component11);
            result.component(1, 2) = inverseDeterminant *
                (component02 * component10 - component00 * component12);
            result.component(2, 2) = inverseDeterminant *
                (component00 * component11 - component01 * component10);

            assert(checkIdentity(result * matrix));

            return result;
        }

        template <class TDerived>
        Matrix<typename MatrixTraits<TDerived>::PlainScalar, -1, -1>
        MatrixInverseFunction<-1>::operator()(const MatrixInterface<TDerived>& matrix) const {
            if (matrix.numRows() == 1 && matrix.numColumns() == 1) {
                return MatrixInverseFunction<1>()(matrix);
            } else if (matrix.numRows() == 2 && matrix.numColumns() == 2) {
                return MatrixInverseFunction<2>()(matrix);
            } else if (matrix.numRows() == 3 && matrix.numColumns() == 3) {
                return MatrixInverseFunction<3>()(matrix);
            } else {
                assert(false);
                return Matrix<typename MatrixTraits<TDerived>::PlainScalar, -1, -1>(
                    matrix.dimensions()
                );
            }
        }
        
        template <class TDerived>
        inline
        bool
        CheckIdentity<TDerived, double>::operator()(
            const MatrixInterface<TDerived>& matrix
        ) const {
            return matrix.isIdentity();
        }

        template <class TDerived>
        inline
        bool
        CheckIdentity<TDerived, Interval>::operator()(
            const MatrixInterface<TDerived>& matrix
        ) const {
            for (int columnIndex = 0; columnIndex < matrix.numColumns(); ++columnIndex) {
                for (int rowIndex = 0; rowIndex < matrix.numRows(); ++rowIndex) {
                    double expected = double(rowIndex == columnIndex);
                    if (!matrix.component(rowIndex, columnIndex).contains(expected)) {
                        return false;
                    }
                }
            }
            return true;
        }

        template <class TDerived>
        inline
        bool
        checkIdentity(const MatrixInterface<TDerived>& matrix) {
            return CheckIdentity<TDerived>()(matrix);
        }
    }
}
