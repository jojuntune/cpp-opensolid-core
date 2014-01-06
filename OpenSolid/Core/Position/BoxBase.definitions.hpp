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

#include <OpenSolid/Core/Position/PointBase.declarations.hpp>

#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Cartesian/CartesianBase.definitions.hpp>
#include <OpenSolid/Core/IntervalMatrix.declarations.hpp>
#include <OpenSolid/Core/IntervalVector.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class BoxBase :
            public detail::CartesianBase<Interval, iNumDimensions>
        {
        private:
            const Box<iNumDimensions>&
            derived() const;
        protected:
            BoxBase();

            BoxBase(const IntervalMatrix<iNumDimensions, 1>& components);

            BoxBase(const Interval* sourcePtr);
        public:
            const bool
            isEmpty() const;

            const Point<iNumDimensions>
            minVertex() const;
            
            const Point<iNumDimensions>
            maxVertex() const;

            const Point<iNumDimensions>
            vertex(std::int64_t index) const;

            detail::BoxVertices<iNumDimensions>
            vertices() const;
            
            const Point<iNumDimensions>
            midPoint() const;
            
            const Point<iNumDimensions>
            randomPoint() const;

            const Vector<iNumDimensions>
            diagonalVector() const;

            const bool
            overlaps(const Box<iNumDimensions>& other, double precision = 1e-12) const;

            const bool
            strictlyOverlaps(const Box<iNumDimensions>& other, double precision = 1e-12) const;
            
            const bool
            contains(const Point<iNumDimensions>& point, double precision = 1e-12) const;
            
            const bool
            strictlyContains(const Point<iNumDimensions>& point, double precision = 1e-12) const;
            
            const bool
            contains(const Box<iNumDimensions>& other, double precision = 1e-12) const;
            
            const bool
            strictlyContains(const Box<iNumDimensions>& other, double precision = 1e-12) const;

            const Box<iNumDimensions>
            hull(const Point<iNumDimensions>& point) const;
            
            const Box<iNumDimensions>
            hull(const Box<iNumDimensions>& other) const;

            const Box<iNumDimensions>
            intersection(const Box<iNumDimensions>& other) const;
        };
    }
}
