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

#include <OpenSolid/Core/Position/BoxVertices.declarations.hpp>

#include <OpenSolid/Core/Box.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection/IndexIterator.declarations.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

namespace opensolid
{
    template <int iNumDimensions>
    struct BoundsType<detail::BoxVertices<iNumDimensions>>
    {
        typedef Box<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct NumDimensions<detail::BoxVertices<iNumDimensions>>
    {
        static const int Value = iNumDimensions;
    };

    template <int iNumDimensions>
    struct ScaledType<detail::BoxVertices<iNumDimensions>>
    {
        typedef detail::BoxVertices<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct TranslatedType<detail::BoxVertices<iNumDimensions>>
    {
        typedef detail::BoxVertices<iNumDimensions> Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformedType<detail::BoxVertices<iNumDimensions>, iNumResultDimensions>
    {
        typedef typename TransformedType<
            SpatialCollection<detail::BoxVertices<iNumDimensions>>,
            iNumResultDimensions
        >::Type Type;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphedType<detail::BoxVertices<iNumDimensions>, iNumResultDimensions>
    {
        typedef typename MorphedType<
            SpatialCollection<detail::BoxVertices<iNumDimensions>>,
            iNumResultDimensions
        >::Type Type;
    };

    template <int iNumDimensions>
    struct ItemType<detail::BoxVertices<iNumDimensions>>
    {
        typedef Point<iNumDimensions> Type;
    };

    template <int iNumDimensions>
    struct ItemReferenceType<detail::BoxVertices<iNumDimensions>>
    {
        typedef Point<iNumDimensions> Type;
    };

    namespace detail
    {
        template <int iNumDimensions>
        class BoxVertices :
            public SpatialCollection<BoxVertices<iNumDimensions>>
        {
        private:
            Box<iNumDimensions> _box;
        public:
            BoxVertices(const Box<iNumDimensions>& box);

            const Box<iNumDimensions>&
            box() const;

            IndexIterator<BoxVertices<iNumDimensions>>
            begin() const;

            IndexIterator<BoxVertices<iNumDimensions>>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            Point<iNumDimensions>
            operator[](std::int64_t index) const;
        };
    }

    template <int iNumDimensions>
    struct BoundsFunction<detail::BoxVertices<iNumDimensions>>
    {
        const Box<iNumDimensions>&
        operator()(const detail::BoxVertices<iNumDimensions>& boxVertices) const;
    };

    template <int iNumDimensions>
    struct ScalingFunction<detail::BoxVertices<iNumDimensions>>
    {
        detail::BoxVertices<iNumDimensions>
        operator()(
            const detail::BoxVertices<iNumDimensions>& boxVertices,
            double scale
        ) const;
    };

    template <int iNumDimensions>
    struct TranslationFunction<detail::BoxVertices<iNumDimensions>>
    {
        template <class TVector>
        detail::BoxVertices<iNumDimensions>
        operator()(
            const detail::BoxVertices<iNumDimensions>& boxVertices,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct TransformationFunction<detail::BoxVertices<iNumDimensions>, iNumResultDimensions> :
        public TransformationFunction<
            SpatialCollection<detail::BoxVertices<iNumDimensions>>,
            iNumResultDimensions
        >
    {
    };

    template <int iNumDimensions, int iNumResultDimensions>
    struct MorphingFunction<detail::BoxVertices<iNumDimensions>, iNumResultDimensions> :
        public MorphingFunction<
            SpatialCollection<detail::BoxVertices<iNumDimensions>>,
            iNumResultDimensions
        >
    {
    };
}
