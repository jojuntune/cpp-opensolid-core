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

#include <OpenSolid/Core/Matrix/MatrixStorage.declarations.hpp>

#include <vector>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumRows, int iNumColumns>
        class MatrixStorage
        {
        private:
            TScalar _data[iNumRows * iNumColumns];
        public:
            MatrixStorage(std::size_t size = iNumRows * iNumColumns);

            TScalar*
            data();

            const TScalar*
            data() const;
        };

        template <class TScalar>
        class DynamicMatrixStorage
        {
        private:
            std::vector<TScalar> _data;
        public:
            DynamicMatrixStorage(std::size_t size);

            TScalar*
            data();

            const TScalar*
            data() const;
        };

        template <class TScalar, int iNumRows>
        class MatrixStorage<TScalar, iNumRows, -1> :
            public DynamicMatrixStorage<TScalar>
        {
        public:
            MatrixStorage(std::size_t size);
        };

        template <class TScalar, int iNumColumns>
        class MatrixStorage<TScalar, -1, iNumColumns> :
            public DynamicMatrixStorage<TScalar>
        {
        public:
            MatrixStorage(std::size_t size);
        };

        template <class TScalar>
        class MatrixStorage<TScalar, -1, -1> :
            public DynamicMatrixStorage<TScalar>
        {
        public:
            MatrixStorage(std::size_t size);
        };
    }
}
