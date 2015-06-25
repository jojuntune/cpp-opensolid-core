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

#include <OpenSolid/Core/LineSegment.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/EqualityFunction.declarations.hpp>
#include <OpenSolid/Core/Intersection.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Plane.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Simplex/LineSegmentBase.definitions.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<LineSegment<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<LineSegment<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <>
    class LineSegment<2> :
        public detail::LineSegmentBase<2>,
        public Convertible<LineSegment<2>>
    {
    public:
        LineSegment();

        LineSegment(const Point<2>& startVertex, const Point<2>& endVertex);

        LineSegment<3>
        toGlobalFrom(const Plane3d& plane) const;

        using detail::LineSegmentBase<2>::toGlobalFrom;
    };
    
    typedef LineSegment<2> LineSegment2d;

    template <>
    class LineSegment<3> :
        public detail::LineSegmentBase<3>,
        public Convertible<LineSegment<3>>
    {
    public:
        LineSegment();

        LineSegment(const Point<3>& startVertex, const Point<3>& endVertex);

        Intersection<LineSegment<3>, Plane3d>
        intersection(const Plane3d& plane, double precision = 1e-12) const;

        LineSegment<2>
        toLocalIn(const Plane3d& plane) const;

        using detail::LineSegmentBase<3>::toLocalIn;

        LineSegment<3>
        projectedOnto(const Plane3d& plane) const;
    };

    typedef LineSegment<3> LineSegment3d;

    template <int iNumDimensions>
    struct EqualityFunction<LineSegment<iNumDimensions>>
    {
        bool
        operator()(
            const LineSegment<iNumDimensions>& firstLineSegment,
            const LineSegment<iNumDimensions>& secondLineSegment,
            double precision
        ) const;
    };
}
