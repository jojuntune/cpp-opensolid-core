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

#include <OpenSolid/Core/Vector/DoubleVectorBase.declarations.hpp>

#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>
#include <OpenSolid/Core/Vector/VectorBase.definitions.hpp>
#include <OpenSolid/Core/Zero.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class DoubleVectorBase :
            public VectorBase<double, iNumDimensions>
        {
        private:
            const Vector<double, iNumDimensions>&
            derived() const;
        protected:
            DoubleVectorBase();

            DoubleVectorBase(double value);

            DoubleVectorBase(double x, double y);

            DoubleVectorBase(double x, double y, double z);

            DoubleVectorBase(const Matrix<double, iNumDimensions, 1>& components);
        public:
            const UnitVector<iNumDimensions>
            normalized() const;

            bool
            operator==(const Vector<double, iNumDimensions>& other) const;

            bool
            operator!=(const Vector<double, iNumDimensions>& other) const;

            void
            operator*=(double scale);

            void
            operator/=(double divisor);

            void
            operator+=(const Vector<double, iNumDimensions>& other);

            void
            operator-=(const Vector<double, iNumDimensions>& other);
        };
    }
}
