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

#include <cassert>

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
        template <class TScalar, int iRows, int iCols>
        inline
        MatrixStorage<TScalar, iRows, iCols>::MatrixStorage() :
            _data() {
        }

        template <class TScalar, int iRows, int iCols>
        inline
        MatrixStorage<TScalar, iRows, iCols>::MatrixStorage(int size) :
            _data() {

            assert(size == iRows * iCols);
        }

        template <class TScalar, int iRows, int iCols>
        inline
        TScalar*
        MatrixStorage<TScalar, iRows, iCols>::data() {
            return _data;
        }

        template <class TScalar, int iRows, int iCols>
        inline
        const TScalar*
        MatrixStorage<TScalar, iRows, iCols>::data() const {
            return _data;
        }

        template <class TScalar>
        inline
        DynamicMatrixStorage<TScalar>::DynamicMatrixStorage(int size) :
            _data(std::size_t(size)) {

            assert(size > 0);
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

        template <class TScalar, int iRows>
        inline
        MatrixStorage<TScalar, iRows, -1>::MatrixStorage(int size) :
            DynamicMatrixStorage<TScalar>(size) {

            assert(size > 0);
        }

        template <class TScalar, int iCols>
        inline
        MatrixStorage<TScalar, -1, iCols>::MatrixStorage(int size) :
            DynamicMatrixStorage<TScalar>(size) {

            assert(size > 0);
        }

        template <class TScalar>
        inline
        MatrixStorage<TScalar, -1, -1>::MatrixStorage(int size) :
            DynamicMatrixStorage<TScalar>(size) {

            assert(size > 0);
        }
    }
}

// Restore Visual Studio warning state
#ifdef _MSC_VER
#pragma warning(pop)
#endif
