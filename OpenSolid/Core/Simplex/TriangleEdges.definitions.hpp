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

#include <OpenSolid/Core/Simplex/TriangleEdges.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/Box.declarations.hpp>
#include <OpenSolid/Core/LineSegment.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>
#include <OpenSolid/Core/Triangle.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<detail::TriangleEdges<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions>
    struct ScaledType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef detail::TriangleEdges<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct TranslatedType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef detail::TriangleEdges<iNumDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<detail::TriangleEdges<iNumDimensions>, iNumResultDimensions>
    {
        typedef detail::TriangleEdges<iNumResultDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<detail::TriangleEdges<iNumDimensions>, iNumResultDimensions>
    {
        typedef detail::TriangleEdges<iNumResultDimensions> Type;
    };

    template <int iNumDimensions>
    struct ItemType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef LineSegment<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct ItemReferenceType<detail::TriangleEdges<iNumDimensions>>
    {
        typedef LineSegment<iNumDimensions> Type;
    };

    namespace detail
    {
        template <int iNumDimensions>
        class TriangleEdges :
            public SpatialCollection<TriangleEdges<iNumDimensions>>
        {
        private:
            Triangle<iNumDimensions> _triangle;
        public:
            TriangleEdges(const Triangle<iNumDimensions>& triangle);

            const Triangle<iNumDimensions>&
            triangle() const;

            IndexIterator<TriangleEdges<iNumDimensions>>
            begin() const;

            IndexIterator<TriangleEdges<iNumDimensions>>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            Box<iNumDimensions>
            bounds() const;

            LineSegment<iNumDimensions>
            operator[](std::int64_t index) const;
        };
    }

    template <int iNumDimensions>
    struct ScalingFunction<detail::TriangleEdges<iNumDimensions>>
    {
        detail::TriangleEdges<iNumDimensions>
        operator()(
            const detail::TriangleEdges<iNumDimensions>& triangleEdges,
            double scale
        ) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<detail::TriangleEdges<iNumDimensions>>
    {
        template <class TVector>
        detail::TriangleEdges<iNumDimensions>
        operator()(
            const detail::TriangleEdges<iNumDimensions>& triangleEdges,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<detail::TriangleEdges<iNumDimensions>, iNumResultDimensions>
    {
        template <class TMatrix>
        detail::TriangleEdges<iNumResultDimensions>
        operator()(
            const detail::TriangleEdges<iNumDimensions>& triangleEdges,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<detail::TriangleEdges<iNumDimensions>, iNumResultDimensions>
    {
        detail::TriangleEdges<iNumResultDimensions>
        operator()(
            const detail::TriangleEdges<iNumDimensions>& triangleEdges,
            const ParametricExpression<iNumResultDimensions, iNumDimensions>& morphingExpression
        ) const;
    };
}
