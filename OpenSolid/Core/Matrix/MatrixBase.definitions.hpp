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

#include <OpenSolid/Core/Matrix/MatrixBase.declarations.hpp>

#include <OpenSolid/Core/Matrix/MatrixInterface.definitions.hpp>

#include <vector>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumRows, int iNumColumns>
        class MatrixBase :
            public MatrixInterface<Matrix<TScalar, iNumRows, iNumColumns>>
        {
        private:
            TScalar _data[iNumRows * iNumColumns];
        public:
            static_assert(iNumRows > 0, "Matrices must have at least one row");
            static_assert(iNumColumns > 0, "Matrices must have at least one column");

            MatrixBase();

            MatrixBase(int size);

            MatrixBase(int numRows, int numColumns);

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

        template <class TScalar, int iNumRows>
        class MatrixBase<TScalar, iNumRows, -1> :
            public MatrixInterface<Matrix<TScalar, iNumRows, -1>>
        {
        private:
            std::vector<TScalar> _data;
            int _numColumns;
        public:
            static_assert(iNumRows > 0, "Matrices must have at least one row");

            MatrixBase(int numColumns);

            MatrixBase(int numRows, int numColumns);

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

        template <class TScalar, int iNumColumns>
        class MatrixBase<TScalar, -1, iNumColumns> :
            public MatrixInterface<Matrix<TScalar, -1, iNumColumns>>
        {
        private:
            std::vector<TScalar> _data;
            int _numRows;
        public:
            static_assert(iNumColumns > 0, "Matrices must have at least one column");

            MatrixBase(int numRows);

            MatrixBase(int numRows, int numColumns);

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

        template <class TScalar>
        class MatrixBase<TScalar, -1, -1> :
            public MatrixInterface<Matrix<TScalar, -1, -1>>
        {
        private:
            std::vector<TScalar> _data;
            int _numRows;
            int _numColumns;
        public:
            MatrixBase(int numRows, int numColumns);

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
    }
}
