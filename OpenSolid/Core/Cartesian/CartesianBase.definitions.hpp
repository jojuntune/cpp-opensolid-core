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

#include <OpenSolid/Core/Cartesian/CartesianBase.declarations.hpp>

#include <OpenSolid/Core/Matrix.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumDimensions>
        class CartesianBase
        {
        private:
            Matrix<TScalar, iNumDimensions, 1> _components;
        protected:
            CartesianBase();

            CartesianBase(TScalar x, TScalar y);

            CartesianBase(TScalar x, TScalar y, TScalar z);

            CartesianBase(const Matrix<TScalar, iNumDimensions, 1>& components);
        public:
            const Matrix<TScalar, iNumDimensions, 1>&
            components() const;

            Matrix<TScalar, iNumDimensions, 1>&
            components();

            const TScalar*
            data() const;

            TScalar*
            data();

            TScalar
            component(int index) const;

            TScalar&
            component(int index);

            TScalar
            operator()(int index) const;

            TScalar&
            operator()(int index);

            TScalar
            x() const;

            TScalar&
            x();

            TScalar
            y() const;

            TScalar&
            y();

            TScalar
            z() const;

            TScalar&
            z();
        };
    }
}
