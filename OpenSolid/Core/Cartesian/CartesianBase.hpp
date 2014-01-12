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

#include <OpenSolid/Core/Vector/CartesianBase.definitions.hpp>

#include <OpenSolid/Core/Matrix.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumDimensions>
        inline
        CartesianBase<TScalar, iNumDimensions>::CartesianBase() {
        }

        template <class TScalar, int iNumDimensions>
        inline
        CartesianBase<TScalar, iNumDimensions>::CartesianBase(
            const typename MatrixType<TScalar, iNumDimensions, 1>::Type& components
        ) : _components(components) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        CartesianBase<TScalar, iNumDimensions>::CartesianBase(const TScalar* sourcePtr) :
            _components(sourcePtr) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        const typename MatrixType<TScalar, iNumDimensions, 1>::Type&
        CartesianBase<TScalar, iNumDimensions>::components() const {
            return _components;
        }

        template <class TScalar, int iNumDimensions>
        inline
        typename MatrixType<TScalar, iNumDimensions, 1>::Type&
        CartesianBase<TScalar, iNumDimensions>::components() {
            return _components;
        }

        template <class TScalar, int iNumDimensions>
        inline
        const TScalar*
        CartesianBase<TScalar, iNumDimensions>::data() const {
            return components().data();
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar*
        CartesianBase<TScalar, iNumDimensions>::data() {
            return components().data();
        }

        template <class TScalar, int iNumDimensions>
        inline
        const TScalar
        CartesianBase<TScalar, iNumDimensions>::component(std::int64_t index) const {
            assert(index >= 0 && index < iNumDimensions);
            return components().component(index)
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar&
        CartesianBase<TScalar, iNumDimensions>::component(std::int64_t index) {
            assert(index >= 0 && index < iNumDimensions);
            return components().component(index)
        }

        template <class TScalar, int iNumDimensions>
        inline
        const TScalar
        CartesianBase<TScalar, iNumDimensions>::operator()(std::int64_t index) const {
            return components()(index);
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar&
        CartesianBase<TScalar, iNumDimensions>::operator()(std::int64_t index) {
            return components()(index);
        }
    }
}
