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

#include <OpenSolid/Core/Matrix/MatrixInterface.definitions.hpp>

#include <vector>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iRows, int iCols>
        class MatrixBase :
            public MatrixInterface<Matrix<TScalar, iRows, iCols>>
        {
        private:
            TScalar _data[iRows * iCols];
        public:
            static_assert(iRows > 0, "Matrices must have at least one row");
            static_assert(iCols > 0, "Matrices must have at least one column");

            MatrixBase();

            MatrixBase(int size);

            MatrixBase(int rows, int cols);

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

        template <class TScalar, int iRows>
        class MatrixBase<TScalar, iRows, -1> :
            public MatrixInterface<Matrix<TScalar, iRows, -1>>
        {
        private:
            std::vector<TScalar> _data;
            int _cols;
        public:
            static_assert(iRows > 0, "Matrices must have at least one row");

            MatrixBase(int cols);

            MatrixBase(int rows, int cols);

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

        template <class TScalar, int iCols>
        class MatrixBase<TScalar, -1, iCols> :
            public MatrixInterface<Matrix<TScalar, -1, iCols>>
        {
        private:
            std::vector<TScalar> _data;
            int _rows;
        public:
            static_assert(iCols > 0, "Matrices must have at least one column");

            MatrixBase(int rows);

            MatrixBase(int rows, int cols);

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

        template <class TScalar>
        class MatrixBase<TScalar, -1, -1> :
            public MatrixInterface<Matrix<TScalar, -1, -1>>
        {
        private:
            std::vector<TScalar> _data;
            int _rows;
            int _cols;
        public:
            MatrixBase(int rows, int cols);

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
    }
}
