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

#include <OpenSolid/Core/Matrix/MatrixStorage.definitions.hpp>

// Disable warning C4351 (Visual Studio warning that _data array will in fact be value-initialized
// as specified in the C++ standard; previous versions of Visual Studio did not always
// value-initialize as required)
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4351)
#endif

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        MatrixStorage<TScalar, iNumRows, iNumColumns>::MatrixStorage(std::size_t size) :
            _data() {

            assert(size == iNumRows * iNumColumns);
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        TScalar*
        MatrixStorage<TScalar, iNumRows, iNumColumns>::data() {
            return _data;
        }

        template <class TScalar, int iNumRows, int iNumColumns>
        inline
        const TScalar*
        MatrixStorage<TScalar, iNumRows, iNumColumns>::data() {
            return _data;
        }

        template <class TScalar>
        inline
        DynamicMatrixStorage<TScalar>::DynamicMatrixStorage(std::size_t size) :
            _data(size) {
        }

        template <class TScalar>
        inline
        TScalar*
        DynamicMatrixStorage<TScalar>::data() {
            return _data.data();
        }

        template <class TScalar>
        inline
        const TScalar*
        DynamicMatrixStorage<TScalar>::data() const {
            return _data.data();
        }

        template <class TScalar, int iNumRows>
        inline
        MatrixStorage<TScalar, iNumRows, -1>::MatrixStorage(std::size_t size) :
            DynamicMatrixStorage<TScalar>(size) {
        }

        template <class TScalar, int iNumColumns>
        inline
        MatrixStorage<TScalar, -1, iNumColumns>::MatrixStorage(std::size_t size) :
            DynamicMatrixStorage<TScalar>(size) {
        }

        template <class TScalar>
        inline
        MatrixStorage<TScalar, -1, -1>::MatrixStorage(std::size_t size) :
            DynamicMatrixStorage<TScalar>(size) {
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
