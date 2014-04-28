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

#include <OpenSolid/Core/Vector/IntervalVectorBase.declarations.hpp>

#include <OpenSolid/Core/Vector.declarations.hpp>
#include <OpenSolid/Core/Vector/IntervalVectorVertices.declarations.hpp>
#include <OpenSolid/Core/Vector/VectorBase.definitions.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class IntervalVectorBase :
            public VectorBase<Interval, iNumDimensions>
        {
        private:
            const Vector<Interval, iNumDimensions>&
            derived() const;
        protected:
            IntervalVectorBase();

            IntervalVectorBase(Interval value);

            IntervalVectorBase(Interval x, Interval y);

            IntervalVectorBase(Interval x, Interval y, Interval z);

            IntervalVectorBase(const Matrix<Interval, iNumDimensions, 1>& components);

            IntervalVectorBase(const Interval* sourcePtr);
        public:
            bool
            isEmpty() const;

            const Vector<double, iNumDimensions>
            minVertex() const;
            
            const Vector<double, iNumDimensions>
            maxVertex() const;

            const Vector<double, iNumDimensions>
            vertex(int index) const;

            const IntervalVectorVertices<iNumDimensions>
            vertices() const;
            
            const Vector<double, iNumDimensions>
            centroid() const;
            
            const Vector<double, iNumDimensions>
            randomVector() const;

            const Vector<double, iNumDimensions>
            diagonalVector() const;

            bool
            overlaps(
                const Vector<Interval, iNumDimensions>& other,
                double precision = 1e-12
            ) const;

            bool
            strictlyOverlaps(
                const Vector<Interval, iNumDimensions>& other,
                double precision = 1e-12
            ) const;

            bool
            contains(
                const Vector<double, iNumDimensions>& other,
                double precision = 1e-12
            ) const;

            bool
            strictlyContains(
                const Vector<double, iNumDimensions>& other,
                double precision = 1e-12
            ) const;

            bool
            contains(
                const Vector<Interval, iNumDimensions>& other,
                double precision = 1e-12
            ) const;

            bool
            strictlyContains(
                const Vector<Interval, iNumDimensions>& other,
                double precision = 1e-12
            ) const;

            void
            operator*=(double scale);

            void
            operator*=(Interval scale);

            void
            operator/=(double divisor);

            void
            operator/=(Interval divisor);

            void
            operator+=(const Vector<double, iNumDimensions>& other);

            void
            operator+=(const Vector<Interval, iNumDimensions>& other);

            void
            operator-=(const Vector<double, iNumDimensions>& other);

            void
            operator-=(const Vector<Interval, iNumDimensions>& other);

            static const Vector<Interval, iNumDimensions>
            Unit();

            static const Vector<Interval, iNumDimensions>
            Empty();

            static const Vector<Interval, iNumDimensions>
            Whole();
        };
    }
}
