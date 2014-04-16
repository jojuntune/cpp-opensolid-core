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

#include <OpenSolid/Core/Matrix/ColStride.definitions.hpp>
#include <OpenSolid/Core/Matrix/MatrixDimensions.definitions.hpp>
#include <OpenSolid/Core/Matrix/MatrixInterface.definitions.hpp>

namespace opensolid
{
    template <class TScalar, int iRows, int iCols, int iColStride>
    class MatrixView :
        public detail::MatrixInterface<MatrixView<TScalar, iRows, iCols, iColStride>>,
        private detail::MatrixDimensions<iRows, iCols>,
        private detail::ColStride<iColStride>
    {
    private:
        TScalar* _data;
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

    template <class TScalar, int iRows, int iCols, int iColStride>
    struct MatrixTraits<MatrixView<TScalar, iRows, iCols, iColStride>>
    {
        typedef TScalar ScalarType;
        static const int Rows = iRows;
        static const int Cols = iCols;
        static const int ColStride = iColStride;
    };
}
