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

#include <OpenSolid/Core/Cartesian/CartesianBase.definitions.hpp>

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
        CartesianBase<TScalar, iNumDimensions>::CartesianBase(TScalar x, TScalar y) :
            _components(x, y) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        CartesianBase<TScalar, iNumDimensions>::CartesianBase(TScalar x, TScalar y, TScalar z) :
            _components(x, y, z) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        CartesianBase<TScalar, iNumDimensions>::CartesianBase(
            const Matrix<TScalar, iNumDimensions, 1>& components
        ) : _components(components) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        const Matrix<TScalar, iNumDimensions, 1>&
        CartesianBase<TScalar, iNumDimensions>::components() const {
            return _components;
        }

        template <class TScalar, int iNumDimensions>
        inline
        Matrix<TScalar, iNumDimensions, 1>&
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
        TScalar
        CartesianBase<TScalar, iNumDimensions>::component(int index) const {
            assert(index >= 0 && index < iNumDimensions);
            return components().component(index);
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar&
        CartesianBase<TScalar, iNumDimensions>::component(int index) {
            assert(index >= 0 && index < iNumDimensions);
            return components().component(index);
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar
        CartesianBase<TScalar, iNumDimensions>::operator()(int index) const {
            return components()(index);
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar&
        CartesianBase<TScalar, iNumDimensions>::operator()(int index) {
            return components()(index);
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar
        CartesianBase<TScalar, iNumDimensions>::x() const {
            return component(0);
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar&
        CartesianBase<TScalar, iNumDimensions>::x() {
            return component(0);
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar
        CartesianBase<TScalar, iNumDimensions>::y() const {
            static_assert(iNumDimensions >= 2, "y() only defined for 2D or 3D objects");
            return component(1);
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar&
        CartesianBase<TScalar, iNumDimensions>::y() {
            static_assert(iNumDimensions >= 2, "y() only defined for 2D or 3D objects");
            return component(1);
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar
        CartesianBase<TScalar, iNumDimensions>::z() const {
            static_assert(iNumDimensions == 3, "z() only defined for 3D objects");
            return component(2);
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar&
        CartesianBase<TScalar, iNumDimensions>::z() {
            static_assert(iNumDimensions == 3, "z() only defined for 3D objects");
            return component(2);
        }
    }
}
