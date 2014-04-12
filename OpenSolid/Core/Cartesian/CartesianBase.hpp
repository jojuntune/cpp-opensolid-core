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
        CartesianBase<TScalar, iNumDimensions>::CartesianBase(const TScalar* sourcePtr) :
            _components(sourcePtr) {
        }

        template <class TScalar, int iNumDimensions>
        inline
        CartesianBase<TScalar, iNumDimensions>::CartesianBase(TScalar value) {
            static_assert(
                iNumDimensions == 1,
                "Non-1D Cartesian object cannot be initialized with a single component"
            );

            _components.value() = value;
        }

        template <class TScalar, int iNumDimensions>
        inline
        CartesianBase<TScalar, iNumDimensions>::CartesianBase(TScalar x, TScalar y) {
            static_assert(
                iNumDimensions == 2,
                "Non-2D Cartesian objects cannot be initialized with two components"
            );

            _components(0) = x;
            _components(1) = y;
        }

        template <class TScalar, int iNumDimensions>
        inline
        CartesianBase<TScalar, iNumDimensions>::CartesianBase(TScalar x, TScalar y, TScalar z) {
            static_assert(
                iNumDimensions == 3,
                "Non-3D Cartesian objects cannot be initialized with three components"
            );

            _components(0) = x;
            _components(1) = y;
            _components(2) = z;
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
            return components().coeff(index);
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar&
        CartesianBase<TScalar, iNumDimensions>::component(int index) {
            assert(index >= 0 && index < iNumDimensions);
            return components().coeff(index);
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
        CartesianBase<TScalar, iNumDimensions>::value() const {
            static_assert(iNumDimensions == 1, "value() only defined for 1D objects");
            return *data();
        }

        template <class TScalar, int iNumDimensions>
        inline
        TScalar&
        CartesianBase<TScalar, iNumDimensions>::value() {
            static_assert(iNumDimensions == 1, "value() only defined for 1D objects");
            return *data();
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
