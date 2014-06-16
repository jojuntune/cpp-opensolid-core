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

#include <OpenSolid/Core/Vector/VectorBase.declarations.hpp>

#include <OpenSolid/Core/Cartesian/CartesianBase.definitions.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TScalar, int iNumDimensions>
        class VectorBase :
            public CartesianBase<TScalar, iNumDimensions>
        {
        private:
            const Vector<TScalar, iNumDimensions>&
            derived() const;
        protected:
            VectorBase();

            VectorBase(TScalar value);

            VectorBase(TScalar x, TScalar y);

            VectorBase(TScalar x, TScalar y, TScalar z);

            VectorBase(const Matrix<TScalar, iNumDimensions, 1>& components);

            VectorBase(const TScalar* sourcePtr);
        public:
            TScalar
            squaredNorm() const;

            TScalar
            norm() const;

            bool
            isZero(double precision = 1e-12) const;

            TScalar
            dot(const Vector<double, iNumDimensions>& other) const;

            Interval
            dot(const Vector<Interval, iNumDimensions>& other) const;

            template <class TOtherScalar>
            const Vector<Interval, iNumDimensions>
            hull(const Vector<TOtherScalar, iNumDimensions>& other) const;

            template <class TOtherScalar>
            const Vector<Interval, iNumDimensions>
            intersection(const Vector<TOtherScalar, iNumDimensions>& other) const;

            static const Vector<TScalar, iNumDimensions>
            zero();

            static const Vector<TScalar, iNumDimensions>
            random();
        };
    }
}
