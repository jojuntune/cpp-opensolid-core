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

#include <OpenSolid/Core/Matrix/MatrixBase.declarations.hpp>

namespace opensolid
{
    template <int iNumRows, int iNumColumns>
    class MatrixBase
    {
    private:
        double _components[iNumRows * iNumColumns];
    protected:
        MatrixBase();

        void
        setZero();
    public:
        const double
        component(std::int64_t index) const;

        double&
        component(std::int64_t index);

        const double
        component(std::int64_t rowIndex, std::int64_t columnIndex) const;

        double&
        component(std::int64_t rowIndex, std::int64_t columnIndex);

        const double
        operator()(std::int64_t index) const;

        double&
        operator()(std::int64_t index);

        const double
        operator()(std::int64_t rowIndex, std::int64_t columnIndex) const;

        double&
        operator()(std::int64_t rowIndex, std::int64_t columnIndex);

        const double*
        data() const;

        double*
        data();

        const Matrix<iNumColumns, iNumRows>
        transpose() const;

        void
        operator*=(double scale);

        void
        operator+=(const Matrix<iNumRows, iNumColumns>& other);

        void
        operator-=(const Matrix<iNumRows, iNumColumns>& other);

        static const Matrix<iNumRows, iNumColumns>
        Zero();

        static const Matrix<iNumRows, iNumColumns>
        Ones();

        static const Matrix<iNumRows, iNumColumns>
        Identity();

        static const Matrix<iNumRows, iNumColumns>
        Random();

        static const Matrix<iNumRows, iNumColumns>
        OuterProduct(
            const Matrix<iNumRows, 1>& columnMatrix,
            const Matrix<1, iNumColumns>& rowMatrix
        );
    };
}
