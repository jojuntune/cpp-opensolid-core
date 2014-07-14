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

#include <OpenSolid/Core/MatrixView.declarations.hpp>

#include <OpenSolid/Core/Matrix/MatrixInterface.definitions.hpp>

#include <type_traits>

namespace opensolid
{
    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    class MatrixView :
        public detail::MatrixInterface<MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>>
    {
    private:
        TScalar* _data;
        int _numRows;
        int _numColumns;
        int _size;
        int _columnStride;
    public:
        MatrixView(const MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>& other);

        template <int iOtherNumRows, int iOtherNumColumns, int iOtherColumnStride>
        MatrixView(
            const MatrixView<TScalar, iOtherNumRows, iOtherNumColumns, iOtherColumnStride>& other
        );

        MatrixView(TScalar* sourcePtr);

        MatrixView(TScalar* sourcePtr, int size);

        MatrixView(TScalar* sourcePtr, int numRows, int numColumns);

        MatrixView(TScalar* sourcePtr, int numRows, int numColumns, int columnStride);

        void
        operator=(const MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>& other);

        template <class TOtherDerived>
        void
        operator=(const detail::MatrixInterface<TOtherDerived>& other);

        const TScalar*
        data() const;

        TScalar*
        data();

        int
        numRows() const;

        int
        numColumns() const;

        int
        size() const;

        int
        columnStride() const;
    };

    typedef MatrixView<double, -1, -1, -1> MatrixViewXd;
    typedef MatrixView<const double, -1, -1, -1> ConstMatrixViewXd;
    typedef MatrixView<Interval, -1, -1, -1> IntervalMatrixViewXd;
    typedef MatrixView<const Interval, -1, -1, -1> ConstIntervalMatrixViewXd;

    template <class TScalar, int iNumRows, int iNumColumns, int iColumnStride>
    struct MatrixTraits<MatrixView<TScalar, iNumRows, iNumColumns, iColumnStride>>
    {
        typedef TScalar Scalar;
        typedef typename std::remove_cv<TScalar>::type PlainScalar;
        static const int NumRows = iNumRows;
        static const int NumColumns = iNumColumns;
        static const int ColumnStride = iColumnStride;
    };
}
