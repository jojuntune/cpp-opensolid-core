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

#include <OpenSolid/Core/SpatialCollection/SimplexVertices.declarations.hpp>

#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/SpatialCollection/IndexIterator.declarations.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TSimplex, int iNumVertices>
        class SimplexVertices :
            public SpatialCollection<SimplexVertices<TSimplex, iNumVertices>>
        {
        private:
            TSimplex _simplex;
        public:
            SimplexVertices(const TSimplex& simplex);

            const TSimplex&
            simplex() const;

            IndexIterator<SimplexVertices<TSimplex, iNumVertices>>
            begin() const;

            IndexIterator<SimplexVertices<TSimplex, iNumVertices>>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            typename BoundsType<TSimplex>::Type
            bounds() const;

            const Point<NumDimensions<TSimplex>::Value>&
            operator[](std::int64_t index) const;
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
    template <class TSimplex, int iNumVertices>
    struct ScalingFunction<detail::SimplexVertices<TSimplex, iNumVertices>>
    {
        detail::SimplexVertices<TSimplex, iNumVertices>
        operator()(
            const detail::SimplexVertices<TSimplex, iNumVertices>& simplexVertices,
            double scale
        ) const;
    };

    template <class TSimplex, int iNumVertices>
    struct TranslationFunction<detail::SimplexVertices<TSimplex, iNumVertices>>
    {
        template <class TVector>
        detail::SimplexVertices<TSimplex, iNumVertices>
        operator()(
            const detail::SimplexVertices<TSimplex, iNumVertices>& simplexVertices,
            const EigenBase<TVector>& vector
        ) const;
    };

    template <class TSimplex, int iNumVertices, int iNumResultDimensions>
    struct TransformationFunction<
        detail::SimplexVertices<TSimplex, iNumVertices>,
        iNumResultDimensions
    >
    {
        template <class TMatrix>
        detail::SimplexVertices<
            typename TransformedType<TSimplex, iNumResultDimensions>::Type,
            iNumVertices
        >
        operator()(
            const detail::SimplexVertices<TSimplex, iNumVertices>& simplexVertices,
            const EigenBase<TMatrix>& matrix
        ) const;
    };

    template <class TSimplex, int iNumVertices, int iNumResultDimensions>
    struct MorphingFunction<detail::SimplexVertices<TSimplex, iNumVertices>, iNumResultDimensions>
    {
        detail::SimplexVertices<
            typename MorphedType<TSimplex, iNumResultDimensions>::Type,
            iNumVertices
        >
        operator()(
            const detail::SimplexVertices<TSimplex, iNumVertices>& simplexVertices,
            const ParametricExpression<
                iNumResultDimensions,
                NumDimensions<TSimplex>::Value
            >& morphingExpression
        ) const;
    };
}
