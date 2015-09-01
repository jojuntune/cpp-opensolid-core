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
#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/Intersection.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Plane.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>
#include <OpenSolid/Core/Vector.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class LineSegmentCommon
        {        
        private:
            Point<iNumDimensions> _vertices[2];

            const LineSegment<iNumDimensions>&
            derived() const;
        protected:
            LineSegmentCommon();

            LineSegmentCommon(
                const Point<iNumDimensions>& startVertex,
                const Point<iNumDimensions>& endVertex
            );
        public:
            const Point<iNumDimensions>&
            startVertex() const;

            const Point<iNumDimensions>&
            endVertex() const;

            const Point<iNumDimensions>&
            vertex(int index) const;

            SimplexVertices<LineSegment<iNumDimensions>, 2>
            vertices() const;

            Point<iNumDimensions>
            centroid() const;

            double
            length() const;

            double
            squaredLength() const;

            Vector<double, iNumDimensions>
            vector() const;

            Box<iNumDimensions>
            bounds() const;
        };
    }

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
        public detail::LineSegmentCommon<2>,
        public Transformable<LineSegment<2>, Point<2>>,
        public Convertible<LineSegment<2>>
    {
    private:
        Handedness _handedness;
    public:
        LineSegment();

        LineSegment(const Point<2>& startVertex, const Point<2>& endVertex);

        LineSegment(const Point<2>& startVertex, const Point<2>& endVertex, Handedness handedness);

        Handedness
        handedness() const;

        UnitVector<2>
        normalVector() const;

        Axis<2>
        axis() const;

        template <class TTransformation>
        LineSegment<2>
        transformedBy(const TTransformation& transformation) const;

        LineSegment<3>
        placedOnto(const Plane3d& plane) const;

        bool
        operator==(const LineSegment<2>& other) const;

        bool
        equals(const LineSegment<2>& other, double precision = 1e-12) const;
    };
    
    typedef LineSegment<2> LineSegment2d;

    template <>
    class LineSegment<3> :
        public detail::LineSegmentCommon<3>,
        public Transformable<LineSegment<3>, Point<3>>,
        public Convertible<LineSegment<3>>
    {
    public:
        LineSegment();

        LineSegment(const Point<3>& startVertex, const Point<3>& endVertex);

        UnitVector<3>
        normalVector() const;

        Axis<3>
        axis() const;

        Intersection<LineSegment<3>, Plane3d>
        intersection(const Plane3d& plane, double precision = 1e-12) const;

        template <class TTransformation>
        LineSegment<3>
        transformedBy(const TTransformation& transformation) const;

        LineSegment<2>
        projectedInto(const Plane3d& plane) const;

        LineSegment<3>
        projectedOnto(const Plane3d& plane) const;

        bool
        operator==(const LineSegment<3>& other) const;

        bool
        equals(const LineSegment<3>& other, double precision = 1e-12) const;
    };

    typedef LineSegment<3> LineSegment3d;
}
