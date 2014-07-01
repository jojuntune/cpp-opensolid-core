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

#include <OpenSolid/Core/Position/PointBase.declarations.hpp>

#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Cartesian/CartesianBase.definitions.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class PointBase :
            public detail::CartesianBase<double, iNumDimensions>
        {
        private:
            const Point<iNumDimensions>&
            derived() const;
        protected:
            PointBase();

            PointBase(double value);

            PointBase(double x, double y);

            PointBase(double x, double y, double z);

            PointBase(const Matrix<double, iNumDimensions, 1>& components);

            PointBase(const double* sourcePtr);
        public:
            double
            squaredDistanceTo(const Point<iNumDimensions>& other) const;

            double
            distanceTo(const Point<iNumDimensions>& other) const;

            const Box<iNumDimensions>
            hull(const Point<iNumDimensions>& other) const;

            const Box<iNumDimensions>
            hull(const Box<iNumDimensions>& box) const;

            bool
            isOrigin(double precision = 1e-12) const;

            bool
            operator==(const Point<iNumDimensions>& other) const;

            bool
            operator!=(const Point<iNumDimensions>& other) const;

            static const Point<iNumDimensions>
            origin();
        };
    }
}
