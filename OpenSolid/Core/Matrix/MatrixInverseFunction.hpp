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

#include <OpenSolid/Core/Matrix/MatrixInverseFunction.definitions.hpp>

#include <OpenSolid/Core/Matrix/MatrixInterface.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TDerived>
        inline
        Matrix<typename MatrixTraits<TDerived>::PlainScalarType, 1, 1>
        MatrixInverseFunction<1, 1>::operator()(const MatrixInterface<TDerived>& matrix) const {
            typedef typename MatrixTraits<TDerived>::PlainScalarType ScalarType;

            if (matrix.rows() != 1 || matrix.cols() != 1) {
                assert(false);
                return Matrix<ScalarType, 1, 1>::Zero();
            }

            ScalarType value = matrix.value();
            if (value == Zero()) {
                assert(false);
                return Matrix<ScalarType, 1, 1>::Zero();
            }

            Matrix<ScalarType, 1, 1> result;
            result.value() = 1.0 / value;
            return result;
        }

        template <class TDerived>
        Matrix<typename MatrixTraits<TDerived>::PlainScalarType, 2, 2>
        MatrixInverseFunction<2, 2>::operator()(const MatrixInterface<TDerived>& matrix) const {
            typedef typename MatrixTraits<TDerived>::PlainScalarType ScalarType;

            if (matrix.rows() != 2 || matrix.cols() != 2) {
                assert(false);
                return Matrix<ScalarType, 2, 2>::Zero();
            }

            ScalarType coeff00 = matrix.coeff(0, 0);
            ScalarType coeff10 = matrix.coeff(1, 0);
            ScalarType coeff01 = matrix.coeff(0, 1);
            ScalarType coeff11 = matrix.coeff(1, 1);

            ScalarType determinant = coeff00 * coeff11 - coeff01 * coeff10;
            if (determinant == Zero()) {
                assert(false);
                return Matrix<ScalarType, 2, 2>::Zero();
            }
            ScalarType inverseDeterminant = 1.0 / determinant;

            Matrix<ScalarType, 2, 2> result;
            result.coeff(0, 0) = inverseDeterminant * coeff11;
            result.coeff(1, 0) = -inverseDeterminant * coeff10;
            result.coeff(0, 1) = -inverseDeterminant * coeff01;
            result.coeff(1, 1) = inverseDeterminant * coeff00;
            return result;
        }

        template <class TDerived>
        Matrix<typename MatrixTraits<TDerived>::PlainScalarType, 3, 3>
        MatrixInverseFunction<3, 3>::operator()(const MatrixInterface<TDerived>& matrix) const {
            typedef typename MatrixTraits<TDerived>::PlainScalarType ScalarType;

            if (matrix.rows() != 3 || matrix.cols() != 3) {
                assert(false);
                return Matrix<ScalarType, 3, 3>::Zero();
            }

            ScalarType coeff00 = matrix.coeff(0, 0);
            ScalarType coeff10 = matrix.coeff(1, 0);
            ScalarType coeff20 = matrix.coeff(2, 0);
            ScalarType coeff01 = matrix.coeff(0, 1);
            ScalarType coeff11 = matrix.coeff(1, 1);
            ScalarType coeff21 = matrix.coeff(2, 1);
            ScalarType coeff02 = matrix.coeff(0, 2);
            ScalarType coeff12 = matrix.coeff(1, 2);
            ScalarType coeff22 = matrix.coeff(2, 2);

            ScalarType cofactor00 = coeff11 * coeff22 - coeff12 * coeff21;
            ScalarType cofactor01 = coeff12 * coeff20 - coeff10 * coeff22;
            ScalarType cofactor02 = coeff10 * coeff21 - coeff11 * coeff20;

            ScalarType determinant = coeff00 * cofactor00 + coeff01 * cofactor01 +
                coeff02 * cofactor02;
            if (determinant == Zero()) {
                assert(false);
                return Matrix<ScalarType, 3, 3>::Zero();
            }
            ScalarType inverseDeterminant = 1.0 / determinant;

            Matrix<ScalarType, 3, 3> result;
            result.coeff(0, 0) = inverseDeterminant * cofactor00;
            result.coeff(1, 0) = inverseDeterminant * cofactor01;
            result.coeff(2, 0) = inverseDeterminant * cofactor02;
            result.coeff(0, 1) = inverseDeterminant * (coeff02 * coeff21 - coeff01 * coeff22);
            result.coeff(1, 1) = inverseDeterminant * (coeff00 * coeff22 - coeff02 * coeff20);
            result.coeff(2, 1) = inverseDeterminant * (coeff01 * coeff20 - coeff00 * coeff21);
            result.coeff(0, 2) = inverseDeterminant * (coeff01 * coeff12 - coeff02 * coeff11);
            result.coeff(1, 2) = inverseDeterminant * (coeff02 * coeff10 - coeff00 * coeff12);
            result.coeff(2, 2) = inverseDeterminant * (coeff00 * coeff11 - coeff01 * coeff10);
            return result;
        }

        template <class TDerived>
        Matrix<typename MatrixTraits<TDerived>::PlainScalarType, -1, -1>
        MatrixInverseFunction<-1, -1>::operator()(const MatrixInterface<TDerived>& matrix) const {
            if (matrix.rows() == 1 && matrix.cols() == 1) {
                return MatrixInverseFunction<1, 1>()(matrix);
            } else if (matrix.rows() == 2 && matrix.cols() == 2) {
                return MatrixInverseFunction<2, 2>()(matrix);
            } else if (matrix.rows() == 3 && matrix.cols() == 3) {
                return MatrixInverseFunction<3, 3>()(matrix);
            } else {
                assert(false);
                return Matrix<typename MatrixTraits<TDerived>::PlainScalarType, -1, -1>(
                    matrix.rows(),
                    matrix.cols()
                );
            }
        }
    }
}
