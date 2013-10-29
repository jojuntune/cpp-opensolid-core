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

#include <OpenSolid/Core/LineSegment.declarations.hpp>

#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Simplex.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class LineSegment :
        public Simplex<iNumDimensions, 2>
    {
    public:
        LineSegment();

        LineSegment(const Simplex<iNumDimensions, 2>& other);

        LineSegment(
            const Point<iNumDimensions>& firstVertex,
            const Point<iNumDimensions>& secondVertex
        );
    };

    typedef LineSegment<2> LineSegment2d;
    typedef LineSegment<3> LineSegment3d;

    template <>
    class LineSegment<1> :
        public Simplex<1, 2>
    {
    public:
        LineSegment();

        LineSegment(const Simplex<1, 2>& other);

        LineSegment(double startPoint, double endPoint);

        double
        startPoint() const;
        
        double
        endPoint() const;

        static LineSegment<1>
        Unit();
    };

    typedef LineSegment<1> LineSegment1d;
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions>
    struct NumDimensions<LineSegment<iNumDimensions>> :
        public NumDimensions<Simplex<iNumDimensions, 2>>
    {
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct ChangeDimensions<LineSegment<iNumDimensions>, iNumResultDimensions> :
        public ChangeDimensions<Simplex<iNumDimensions, 2>, iNumResultDimensions>
    {
    };

    template <int iNumDimensions>
    struct ScalingFunction<LineSegment<iNumDimensions>> :
        public ScalingFunction<Simplex<iNumDimensions, 2>>
    {
    };

    template <int iNumDimensions>
    struct TranslationFunction<LineSegment<iNumDimensions>> :
        public TranslationFunction<Simplex<iNumDimensions, 2>>
    {
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<LineSegment<iNumDimensions>, iNumResultDimensions> :
        public TransformationFunction<Simplex<iNumDimensions, 2>, iNumResultDimensions>
    {
    };

    template <int iNumDimensions>
    struct BoundsType<LineSegment<iNumDimensions>> :
        public BoundsType<Simplex<iNumDimensions, 2>>
    {
    };

    template <int iNumDimensions>
    class TolerantComparator<LineSegment<iNumDimensions>> :
        public TolerantComparator<Simplex<iNumDimensions, 2>>
    {
    public:
        TolerantComparator(double precision);
    };
}
