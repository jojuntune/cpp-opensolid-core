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

#include <OpenSolid/Core/SpatialCollection/ScaledCollection.declarations.hpp>

#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TBaseCollection>
        class ScaledCollection :
            public SpatialCollection<ScaledCollection<TBaseCollection>>
        {
        private:
            TBaseCollection _baseCollection;
            double _scale;
        public:
            ScaledCollection(const ScaledCollection<TBaseCollection>& other);
            
            ScaledCollection(ScaledCollection<TBaseCollection>&& other);

            ScaledCollection(const TBaseCollection& baseCollection, double scale);

            ScaledCollection(TBaseCollection&& baseCollection, double scale);

            const TBaseCollection&
            baseCollection() const;

            double
            scale() const;

            ScaledCollectionIterator<TBaseCollection>
            begin() const;

            ScaledCollectionIterator<TBaseCollection>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            typename ScaledType<typename BoundsType<TBaseCollection>::Type>::Type
            bounds() const;
        };

        template <class TBaseCollection>
        class ScaledCollectionIterator :
            public boost::iterator_facade<
                ScaledCollectionIterator<TBaseCollection>,
                typename ScaledType<typename ItemType<TBaseCollection>::Type>::Type,
                boost::forward_traversal_tag,
                typename ScaledType<typename ItemType<TBaseCollection>::Type>::Type
            >
        {
        private:
            typename IteratorType<TBaseCollection>::Type _baseIterator;
            double _scale;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(const ScaledCollectionIterator<TBaseCollection>& other) const;

            typename ScaledType<typename ItemType<TBaseCollection>::Type>::Type
            dereference() const;
        public:
            ScaledCollectionIterator();

            ScaledCollectionIterator(
                typename IteratorType<TBaseCollection>::Type baseIterator,
                double scale
            );
        };
    }
}

////////// Specializations //////////

namespace opensolid
{
    template <class TBaseCollection>
    struct ScalingFunction<detail::ScaledCollection<TBaseCollection>>
    {
        detail::ScaledCollection<TBaseCollection>
        operator()(
            const detail::ScaledCollection<TBaseCollection>& scaledCollection,
            double scale
        ) const;
    };

    template <class TBaseCollection>
    struct TranslationFunction<detail::ScaledCollection<TBaseCollection>> :
        public TranslationFunction<SpatialCollection<detail::ScaledCollection<TBaseCollection>>>
    {
    };

    template <class TBaseCollection, int iNumResultDimensions>
    struct TransformationFunction<detail::ScaledCollection<TBaseCollection>, iNumResultDimensions>
    {
        template <class TMatrix>
        detail::TransformedCollection<TBaseCollection, iNumResultDimensions>
        operator()(
            const detail::ScaledCollection<TBaseCollection>& scaledCollection,
            const EigenBase<TMatrix>& matrix
        ) const;
    };
}
