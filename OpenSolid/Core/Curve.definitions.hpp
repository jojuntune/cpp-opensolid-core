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
*************************************************************************************/

#pragma once

#include <OpenSolid/config.hpp>

#include <OpenSolid/Core/Curve.declarations.hpp>

#include <OpenSolid/Core/Curve/CurveConstructors.hpp>
#include <OpenSolid/Core/Geometry.definitions.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class Curve :
        public Geometry<iNumDimensions, 1>,
        public CurveConstructors<iNumDimensions>
    {
    public:
        Curve();

        Curve(const Geometry<iNumDimensions, 1>& other);

        Curve(const ParametricExpression<iNumDimensions, 1>& expression, Interval domain);

        Curve(const LineSegment<iNumDimensions>& lineSegment);

        Curve<iNumDimensions>
        reversed() const;

        Point<iNumDimensions>
        startPoint() const;

        Point<iNumDimensions>
        endPoint() const;
    };

    typedef Curve<2> Curve2d;
    typedef Curve<3> Curve3d;
}
