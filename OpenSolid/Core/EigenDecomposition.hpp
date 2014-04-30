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

#include <OpenSolid/Core/EigenDecomposition.definitions.hpp>

#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    template <class TDerived>
    inline
    EigenDecomposition1d::EigenDecomposition(const detail::MatrixInterface<TDerived>& matrix) :
        _eigenvalues(matrix),
        _eigenvectors(Matrix1d::Ones()) {
    }

    inline
    bool
    EigenDecomposition1d::exists() const {
        return true;
    }

    inline
    const Matrix<double, 1, 1>&
    EigenDecomposition1d::eigenvalues() const {
        return _eigenvalues;
    }

    inline
    const Matrix<double, 1, 1>&
    EigenDecomposition1d::eigenvectors() const {
        return _eigenvectors;
    }

    template <class TDerived>
    inline
    EigenDecomposition2d::EigenDecomposition(const detail::MatrixInterface<TDerived>& matrix) :
        _exists(false) {

        this->compute(matrix);
    }

    inline
    bool
    EigenDecomposition2d::exists() const {
        return _exists;
    }

    inline
    const ColumnMatrix2d&
    EigenDecomposition2d::eigenvalues() const {
        return _eigenvalues;
    }

    inline
    const Matrix2d&
    EigenDecomposition2d::eigenvectors() const {
        return _eigenvectors;
    }

    template <class TDerived>
    inline
    EigenDecomposition3d::EigenDecomposition(const detail::MatrixInterface<TDerived>& matrix) :
        _exists(false) {

        this->compute(matrix);
    }

    inline
    bool
    EigenDecomposition3d::exists() const {
        return _exists;
    }

    inline
    const ColumnMatrix3d&
    EigenDecomposition3d::eigenvalues() const {
        return _eigenvalues;
    }

    inline
    const Matrix3d&
    EigenDecomposition3d::eigenvectors() const {
        return _eigenvectors;
    }


    template <class TDerived>
    inline
    EigenDecompositionXd::EigenDecomposition(const detail::MatrixInterface<TDerived>& matrix) :
        _exists(false) {

        this->compute(matrix);
    }

    inline
    bool
    EigenDecompositionXd::exists() const {
        return _exists;
    }

    inline
    const Matrix<double, -1, 1>&
    EigenDecompositionXd::eigenvalues() const {
        return _eigenvalues;
    }

    inline
    const Matrix<double, -1, -1>&
    EigenDecompositionXd::eigenvectors() const {
        return _eigenvectors;
    }
}
