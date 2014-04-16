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

#include <OpenSolid/Core/MatrixView.declarations.hpp>

#include <OpenSolid/Core/Matrix/MatrixInterface.definitions.hpp>

namespace opensolid
{
    template <class TScalar, int iRows, int iCols, int iColStride>
    class MatrixView :
        public detail::MatrixInterface<MatrixView<TScalar, iRows, iCols, iColStride>>
    {
    private:
        TScalar* _data;
        int _rows;
        int _cols;
        int _size;
        int _colStride;
    public:
        MatrixView(TScalar* sourcePtr);

        MatrixView(TScalar* sourcePtr, int size);

        MatrixView(TScalar* sourcePtr, int rows, int cols);

        MatrixView(TScalar* sourcePtr, int rows, int cols, int colStride);

        template <class TOtherDerived>
        void
        operator=(const detail::MatrixInterface<TOtherDerived>& other);

        const TScalar*
        data() const;

        TScalar*
        data();

        int
        rows() const;

        int
        cols() const;

        int
        size() const;

        int
        colStride() const;
    };

    typedef MatrixView<double, -1, -1, -1> MatrixViewXxX;
    typedef MatrixView<const double, -1, -1, -1> ConstMatrixViewXxX;
    typedef MatrixView<Interval, -1, -1, -1> IntervalMatrixViewXxX;
    typedef MatrixView<const Interval, -1, -1, -1> ConstIntervalMatrixViewXxX;

    template <class TScalar, int iRows, int iCols, int iColStride>
    struct MatrixTraits<MatrixView<TScalar, iRows, iCols, iColStride>>
    {
        typedef TScalar ScalarType;
        static const int Rows = iRows;
        static const int Cols = iCols;
        static const int ColStride = iColStride;
    };
}
