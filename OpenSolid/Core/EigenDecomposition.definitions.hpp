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

#include <OpenSolid/Core/EigenDecomposition.declarations.hpp>

#include <OpenSolid/Core/Matrix.definitions.hpp>
#include <OpenSolid/Core/Matrix/MatrixInterface.declarations.hpp>

namespace opensolid
{
    template <>
    class EigenDecomposition<1>
    {
    private:
        Matrix<double, 1, 1> _eigenvalues;
        Matrix<double, 1, 1> _eigenvectors;
    public:
        template <class TDerived>
        EigenDecomposition(const detail::MatrixInterface<TDerived>& matrix);

        bool
        exists() const;

        const Matrix<double, 1, 1>&
        eigenvalues() const;

        const Matrix<double, 1, 1>&
        eigenvectors() const;
    };

    typedef EigenDecomposition<1> EigenDecomposition1d;

    template <>
    class EigenDecomposition<2>
    {
    private:
        bool _exists;
        Matrix<double, 2, 1> _eigenvalues;
        Matrix<double, 2, 2> _eigenvectors;

        OPENSOLID_CORE_EXPORT
        void
        compute(const Matrix<double, 2, 2>& matrix);
    public:
        template <class TDerived>
        EigenDecomposition(const detail::MatrixInterface<TDerived>& matrix);

        bool
        exists() const;

        const Matrix<double, 2, 1>&
        eigenvalues() const;

        const Matrix<double, 2, 2>&
        eigenvectors() const;
    };

    typedef EigenDecomposition<2> EigenDecomposition2d;

    template <>
    class EigenDecomposition<3>
    {
    private:
        bool _exists;
        Matrix<double, 3, 1> _eigenvalues;
        Matrix<double, 3, 3> _eigenvectors;

        OPENSOLID_CORE_EXPORT
        void
        compute(const Matrix<double, 3, 3>& matrix);
    public:
        template <class TDerived>
        EigenDecomposition(const detail::MatrixInterface<TDerived>& matrix);

        bool
        exists() const;

        const Matrix<double, 3, 1>&
        eigenvalues() const;

        const Matrix<double, 3, 3>&
        eigenvectors() const;
    };

    typedef EigenDecomposition<3> EigenDecomposition3d;

    template <>
    class EigenDecomposition<-1>
    {
    private:
        bool _exists;
        Matrix<double, -1, 1> _eigenvalues;
        Matrix<double, -1, -1> _eigenvectors;

        OPENSOLID_CORE_EXPORT
        void
        compute(const Matrix<double, -1, -1>& matrix);
    public:
        template <class TDerived>
        EigenDecomposition(const detail::MatrixInterface<TDerived>& matrix);

        bool
        exists() const;

        const Matrix<double, -1, 1>&
        eigenvalues() const;

        const Matrix<double, -1, -1>&
        eigenvectors() const;
    };

    typedef EigenDecomposition<-1> EigenDecompositionXd;
}
