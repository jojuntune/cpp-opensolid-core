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

#include <OpenSolid/Core/Position/BoxBase.declarations.hpp>

#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Cartesian/CartesianBase.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Position/BoxVertices.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

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

            BoxBase(Interval x, Interval y);

            BoxBase(Interval x, Interval y, Interval z);

            BoxBase(const Matrix<Interval, iNumDimensions, 1>& components);
        public:
            bool
            isEmpty() const;

            const Box<iNumDimensions>&
            bounds() const;

            const Point<iNumDimensions>
            minVertex() const;
            
            const Point<iNumDimensions>
            maxVertex() const;

            const Point<iNumDimensions>
            vertex(int index) const;

            const BoxVertices<iNumDimensions>
            vertices() const;
            
            const Point<iNumDimensions>
            centroid() const;
            
            const Point<iNumDimensions>
            randomPoint() const;

            const Vector<double, iNumDimensions>
            diagonalVector() const;

            bool
            overlaps(const Box<iNumDimensions>& other, double precision = 1e-12) const;

            bool
            strictlyOverlaps(const Box<iNumDimensions>& other, double precision = 1e-12) const;
            
            bool
            contains(const Point<iNumDimensions>& point, double precision = 1e-12) const;
            
            bool
            strictlyContains(const Point<iNumDimensions>& point, double precision = 1e-12) const;
            
            bool
            contains(const Box<iNumDimensions>& other, double precision = 1e-12) const;
            
            bool
            strictlyContains(const Box<iNumDimensions>& other, double precision = 1e-12) const;

            const Box<iNumDimensions>
            hull(const Point<iNumDimensions>& point) const;
            
            const Box<iNumDimensions>
            hull(const Box<iNumDimensions>& other) const;

            const Box<iNumDimensions>
            intersection(const Box<iNumDimensions>& other) const;

            static const Box<iNumDimensions>
            UNIT();

            static const Box<iNumDimensions>
            EMPTY();

            static const Box<iNumDimensions>
            WHOLE();
        };
    }
}
