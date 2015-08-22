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

#include <OpenSolid/Core/Simplex/LineSegmentBase.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/Frame.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
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
        class LineSegmentBase :
            public Transformable<LineSegment<iNumDimensions>, iNumDimensions>
        {        
        private:
            Point<iNumDimensions> _vertices[2];

            const LineSegment<iNumDimensions>&
            derived() const;
        protected:
            LineSegmentBase();

            LineSegmentBase(
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

            UnitVector<iNumDimensions>
            normalVector() const;

            Axis<iNumDimensions>
            axis() const;

            Box<iNumDimensions>
            bounds() const;

            bool
            operator==(const LineSegment<iNumDimensions>& other) const;

            LineSegment<iNumDimensions>
            scaledAbout(const Point<iNumDimensions>& point, double scale) const;

            LineSegment<iNumDimensions>
            rotatedAbout(
                const Point<iNumDimensions>& point,
                const Matrix<double, iNumDimensions, iNumDimensions>& rotationMatrix
            ) const;

            using Transformable<LineSegment<iNumDimensions>, iNumDimensions>::rotatedAbout;

            LineSegment<iNumDimensions>
            translatedBy(const Vector<double, iNumDimensions>& vector) const;

            LineSegment<iNumDimensions>
            toLocalIn(const Frame<iNumDimensions>& frame) const;

            LineSegment<iNumDimensions>
            toGlobalFrom(const Frame<iNumDimensions>& frame) const;

            LineSegment<iNumDimensions>
            projectedOnto(const Axis<iNumDimensions>& axis) const;

            LineSegment<iNumDimensions>
            mirroredAbout(
                const Point<iNumDimensions>& point,
                const UnitVector<iNumDimensions>& mirrorDirection
            ) const;

            using Transformable<LineSegment<iNumDimensions>, iNumDimensions>::mirroredAbout;
        };
    }
}
