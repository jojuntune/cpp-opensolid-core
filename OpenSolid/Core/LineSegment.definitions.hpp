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
#include <OpenSolid/Core/CoordinateSystem.declarations.hpp>
#include <OpenSolid/Core/EqualityFunction.declarations.hpp>
#include <OpenSolid/Core/Intersection.declarations.hpp>
#include <OpenSolid/Core/Matrix.declarations.hpp>
#include <OpenSolid/Core/Plane.definitions.hpp>
#include <OpenSolid/Core/Point.definitions.hpp>
#include <OpenSolid/Core/Simplex/SimplexVertices.declarations.hpp>
#include <OpenSolid/Core/Transformable.definitions.hpp>

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
    class LineSegment :
        public Convertible<LineSegment<iNumDimensions>>,
        public Transformable<LineSegment<iNumDimensions>>
    {
    private:
        Point<iNumDimensions> _vertices[2];
    public:
        LineSegment();

        LineSegment(
            const Point<iNumDimensions>& startVertex,
            const Point<iNumDimensions>& endVertex
        );

        const Point<iNumDimensions>&
        startVertex() const;

        Point<iNumDimensions>&
        startVertex();

        const Point<iNumDimensions>&
        endVertex() const;

        Point<iNumDimensions>&
        endVertex();

        const Point<iNumDimensions>&
        vertex(int index) const;

        Point<iNumDimensions>&
        vertex(int index);

        detail::SimplexVertices<LineSegment<iNumDimensions>, 2>
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

        CoordinateSystem<iNumDimensions, 1>
        coordinateSystem() const;

        Axis<iNumDimensions>
        axis() const;

        Box<iNumDimensions>
        bounds() const;

        bool
        operator==(const LineSegment<iNumDimensions>& other) const;

        Intersection<LineSegment<3>, Plane3d>
        intersection(const Plane3d& plane, double precision = 1e-12) const;
        
        bool
        contains(const Point<2>& point, double precision = 1e-12) const;
        
        bool
        contains(const Point<3>& point, double precision = 1e-12) const;
    };

    typedef LineSegment<1> LineSegment1d;
    typedef LineSegment<2> LineSegment2d;
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
    
    template <int iNumDimensions>
    struct ScalingFunction<LineSegment<iNumDimensions>>
    {
        LineSegment<iNumDimensions>
        operator()(const LineSegment<iNumDimensions>& lineSegment, double scale) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<LineSegment<iNumDimensions>>
    {
        LineSegment<iNumDimensions>
        operator()(
            const LineSegment<iNumDimensions>& lineSegment,
            const Vector<double, iNumDimensions>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<LineSegment<iNumDimensions>, iNumResultDimensions>
    {
        LineSegment<iNumResultDimensions>
        operator()(
            const LineSegment<iNumDimensions>& lineSegment,
            const Matrix<double, iNumResultDimensions, iNumDimensions>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<LineSegment<iNumDimensions>, iNumResultDimensions>
    {
        LineSegment<iNumResultDimensions>
        operator()(
            const LineSegment<iNumDimensions>& lineSegment,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };
}
