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

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Cartesian/CartesianBase.definitions.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class PointBase :
            public detail::CartesianBase<double, iNumDimensions>,
            public Transformable<Point<iNumDimensions>, Point<iNumDimensions>>
        {
        private:
            const Point<iNumDimensions>&
            derived() const;
        protected:
            PointBase();

            PointBase(double x, double y);

            PointBase(double x, double y, double z);

            PointBase(const Matrix<double, iNumDimensions, 1>& components);
        public:
            Box<iNumDimensions>
            bounds() const;

            double
            squaredDistanceTo(const Point<iNumDimensions>& other) const;

            double
            distanceTo(const Point<iNumDimensions>& other) const;

            bool
            isEqualTo(const Point<iNumDimensions>& other, double precision = 1e-12) const;

            bool
            isOrigin(double precision = 1e-12) const;

            double
            distanceAlong(const Axis<iNumDimensions>& axis) const;

            Box<iNumDimensions>
            hull(const Point<iNumDimensions>& other) const;

            Box<iNumDimensions>
            hull(const Box<iNumDimensions>& box) const;

            template <class TTransformation>
            Point<iNumDimensions>
            transformedBy(const TTransformation& transformation) const;

            Point<iNumDimensions>
            projectedOnto(const Axis<iNumDimensions>& axis) const;

            bool
            operator==(const Point<iNumDimensions>& other) const;

            bool
            operator!=(const Point<iNumDimensions>& other) const;

            static Point<iNumDimensions>
            origin();
        };
    }
}
