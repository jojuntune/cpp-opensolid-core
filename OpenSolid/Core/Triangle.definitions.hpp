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

#include <OpenSolid/Core/Triangle.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Convertible.definitions.hpp>
#include <OpenSolid/Core/EqualityFunction.declarations.hpp>
#include <OpenSolid/Core/Handedness.definitions.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Plane.declarations.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.declarations.hpp>
#include <OpenSolid/Core/Simplex/TriangleEdges.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/UnitVector.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <int iNumDimensions>
        class TriangleCommon :
            public Transformable<Triangle<iNumDimensions>, Point<iNumDimensions>>
        {
        private:
            Point<iNumDimensions> _vertices[3];
            Handedness _handedness;

            const Triangle<iNumDimensions>&
            derived() const;
        protected:
            TriangleCommon();

            TriangleCommon(
                const Point<iNumDimensions>& firstVertex,
                const Point<iNumDimensions>& secondVertex,
                const Point<iNumDimensions>& thirdVertex,
                Handedness handedness
            );
        public:
            const Point<iNumDimensions>&
            vertex(int index) const;

            Handedness
            handedness() const;

            SimplexVertices<Triangle<iNumDimensions>, 3>
            vertices() const;

            Point<iNumDimensions>
            centroid() const;

            TriangleEdges<iNumDimensions>
            edges() const;

            Box<iNumDimensions>
            bounds() const;

            template <class TTransformation>
            Triangle<iNumDimensions>
            transformedBy(const TTransformation& transformation) const;

            bool
            operator==(const Triangle<iNumDimensions>& other) const;
        };
    }

    template <int iNumDimensions>
    struct BoundsType<Triangle<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };
    
    template <int iNumDimensions>
    struct NumDimensions<Triangle<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <>
    class Triangle<2> :
        public detail::TriangleCommon<2>,
        public Convertible<Triangle<2>>
    {
    public:
        Triangle();

        Triangle(
            const Point<2>& firstVertex,
            const Point<2>& secondVertex,
            const Point<2>& thirdVertex
        );

        Triangle(
            const Point<2>& firstVertex,
            const Point<2>& secondVertex,
            const Point<2>& thirdVertex,
            Handedness handedness
        );

        LineSegment<2>
        edge(int oppositeIndex) const;

        OPENSOLID_CORE_EXPORT
        double
        area() const;

        bool
        contains(const Point<2>& point) const;

        Triangle<3>
        placedOnto(const Plane3d& plane) const;

        OPENSOLID_CORE_EXPORT
        static const Triangle<2>&
        UNIT();
    };

    typedef Triangle<2> Triangle2d;

    template <>
    class Triangle<3> :
        public detail::TriangleCommon<3>,
        public Convertible<Triangle<3>>
    {
    public:
        Triangle();

        Triangle(
            const Point<3>& firstVertex,
            const Point<3>& secondVertex,
            const Point<3>& thirdVertex
        );

        Triangle(
            const Point<3>& firstVertex,
            const Point<3>& secondVertex,
            const Point<3>& thirdVertex,
            Handedness handedness
        );

        LineSegment<3>
        edge(int oppositeIndex) const;

        double
        area() const;

        OPENSOLID_CORE_EXPORT
        UnitVector<3>
        normalVector() const;

        OPENSOLID_CORE_EXPORT
        Plane3d
        plane() const;

        Triangle<2>
        projectedInto(const Plane3d& plane) const;

        Triangle<3>
        projectedOnto(const Plane3d& plane) const;
    };

    typedef Triangle<3> Triangle3d;

    template <int iNumDimensions>
    struct EqualityFunction<Triangle<iNumDimensions>>
    {
        bool
        operator()(
            const Triangle<iNumDimensions>& firstTriangle,
            const Triangle<iNumDimensions>& secondTriangle,
            double precision
        ) const;
    };
}
