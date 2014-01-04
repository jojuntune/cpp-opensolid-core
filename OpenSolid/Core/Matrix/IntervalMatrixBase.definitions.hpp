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

#include <OpenSolid/Core/Matrix/IntervalMatrixBase.declarations.hpp>

namespace opensolid
{
    template <int iNumRows, int iNumColumns>
    class IntervalMatrixBase
    {
    private:
        Interval _components[iNumRows * iNumColumns];
    protected:
        IntervalMatrixBase();

        IntervalMatrixBase(const Matrix<iNumRows, iNumColumns>& matrix);
    public:
        const Interval
        component(std::int64_t index) const;

        Interval&
        component(std::int64_t index);

        const Interval
        component(std::int64_t row, std::int64_t column) const;

        Interval&
        component(std::int64_t row, std::int64_t column);

        const Interval
        operator()(std::int64_t index) const;

        Interval&
        operator()(std::int64_t index);

        const Interval
        operator()(std::int64_t row, std::int64_t column) const;

        Interval&
        operator()(std::int64_t row, std::int64_t column);

        const Interval*
        data() const;

        Interval*
        data();

        const IntervalMatrix<iNumColumns, iNumRows>
        transpose() const;

        void
        operator*=(double scale);

        void
        operator*=(Interval scale);

        void
        operator+=(const Matrix<iNumRows, iNumColumns>& matrix);

        void
        operator+=(const IntervalMatrix<iNumRows, iNumColumns>& other);

        void
        operator-=(const Matrix<iNumRows, iNumColumns>& other);

        void
        operator-=(const IntervalMatrix<iNumRows, iNumColumns>& other);

        static const Matrix<iNumRows, iNumColumns>
        OuterProduct(
            const IntervalMatrix<iNumRows, 1>& columnMatrix,
            const IntervalMatrix<1, iNumColumns>& rowMatrix
        );
    };
}
