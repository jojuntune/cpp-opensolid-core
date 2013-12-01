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

#include <OpenSolid/Core/LineSegment.declarations.hpp>

#include <OpenSolid/Core/Axis.declarations.hpp>
#include <OpenSolid/Core/BoundsFunction.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/Point.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    class LineSegment :
        public Transformable<LineSegment<iNumDimensions>>
    {
    private:
        Point<iNumDimensions> _startPoint;
        Point<iNumDimensions> _endPoint;
    public:
        LineSegment();

        LineSegment(
            const Point<iNumDimensions>& startPoint,
            const Point<iNumDimensions>& endPoint
        );

        const Point<iNumDimensions>&
        startPoint() const;

        Point<iNumDimensions>&
        startPoint();

        const Point<iNumDimensions>&
        endPoint() const;

        Point<iNumDimensions>&
        endPoint();

        double
        length() const;

        double
        squaredLength() const;

        Matrix<double, iNumDimensions, 1>
        vector() const;

        Matrix<double, iNumDimensions, 1>
        normalVector() const;

        CoordinateSystem<iNumDimensions, 1>
        coordinateSystem() const;

        Axis<iNumDimensions>
        axis() const;

        Box<iNumDimensions>
        bounds() const;

        bool
        operator==(const LineSegment<iNumDimensions>& other) const;
    };

    typedef LineSegment<1> LineSegment1d;
    typedef LineSegment<2> LineSegment2d;
    typedef LineSegment<3> LineSegment3d;
}

////////// Specializations //////////

namespace opensolid
{
    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<LineSegment<iNumDimensions>, iNumResultDimensions>
    {
        typedef LineSegment<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<LineSegment<iNumDimensions>, iNumResultDimensions>
    {
        typedef LineSegment<iNumResultDimensions> Type;
    };

    template <int iNumDimensions>
    struct ScalingFunction<LineSegment<iNumDimensions>>
    {
        LineSegment<iNumDimensions>
        operator()(const LineSegment<iNumDimensions>& lineSegment, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<LineSegment<iNumDimensions>>
    {
        template <class TVector>
        LineSegment<iNumDimensions>
        operator()(
            const LineSegment<iNumDimensions>& lineSegment,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<LineSegment<iNumDimensions>, iNumResultDimensions>
    {
        template <class TMatrix>
        LineSegment<iNumResultDimensions>
        operator()(
            const LineSegment<iNumDimensions>& lineSegment,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    namespace detail
    {
        template <int iNumDimensions, int iNumResultDimensions>
        LineSegment<iNumResultDimensions>
        morphed(
            const LineSegment<iNumDimensions>& lineSegment,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        );
    }

    template <int iNumDimensions>
    class TolerantComparator<LineSegment<iNumDimensions>>
    {
    private:
        double _precision;
    public:
        TolerantComparator(double precision);

        bool
        operator()(
            const LineSegment<iNumDimensions>& firstLineSegment,
            const LineSegment<iNumDimensions>& secondLineSegment
        ) const;
    };
}
