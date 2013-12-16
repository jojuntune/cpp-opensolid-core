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

#include <OpenSolid/Core/SpatialCollection/MappedCollection.declarations.hpp>

#include <OpenSolid/Core/BoundsType.declarations.hpp>
#include <OpenSolid/Core/SpatialCollection.definitions.hpp>
#include <OpenSolid/Core/Transformable.declarations.hpp>

#include <boost/iterator/iterator_facade.hpp>

namespace opensolid
{
    template <class TBaseCollection, class TMappingFunction>
    struct BoundsType<detail::MappedCollection<TBaseCollection, TMappingFunction>> :
        public BoundsType<
            typename ItemType<detail::MappedCollection<TBaseCollection, TMappingFunction>>::Type
        >
    {
    };

    template <class TBaseCollection, class TMappingFunction>
    struct NumDimensions<detail::MappedCollection<TBaseCollection, TMappingFunction>> :
        public NumDimensions<
            typename ItemType<detail::MappedCollection<TBaseCollection, TMappingFunction>>::Type
        >
    {
    };

    template <class TBaseCollection, class TMappingFunction>
    struct ScaledType<detail::MappedCollection<TBaseCollection, TMappingFunction>> :
        public ScaledType<
            SpatialCollection<detail::MappedCollection<TBaseCollection, TMappingFunction>>
        >
    {
    };

    template <class TBaseCollection, class TMappingFunction>
    struct TranslatedType<detail::MappedCollection<TBaseCollection, TMappingFunction>> :
        public TranslatedType<
            SpatialCollection<detail::MappedCollection<TBaseCollection, TMappingFunction>>
        >
    {
    };

    template <class TBaseCollection, class TMappingFunction, int iNumResultDimensions>
    struct TransformedType<
        detail::MappedCollection<TBaseCollection, TMappingFunction>,
        iNumResultDimensions
    > : public TransformedType<
            SpatialCollection<detail::MappedCollection<TBaseCollection, TMappingFunction>>,
            iNumResultDimensions
        >
    {
    };

    template <class TBaseCollection, class TMappingFunction, int iNumResultDimensions>
    struct MorphedType<
        detail::MappedCollection<TBaseCollection, TMappingFunction>,
        iNumResultDimensions
    > : public MorphedType<
            SpatialCollection<detail::MappedCollection<TBaseCollection, TMappingFunction>>,
            iNumResultDimensions
        >
    {
    };

    template <class TBaseCollection, class TMappingFunction>
    struct IteratorType<detail::MappedCollection<TBaseCollection, TMappingFunction>>
    {
        typedef detail::MappedCollectionIterator<TBaseCollection, TMappingFunction> Type;
    };

    template <class TBaseCollection, class TMappingFunction>
    struct ItemType<detail::MappedCollection<TBaseCollection, TMappingFunction>>
    {
        typedef typename std::decay<
            typename std::result_of<
                TMappingFunction(typename ItemType<TBaseCollection>::Type)
            >::type
        >::type Type;
    };

    template <class TBaseCollection, class TMappingFunction>
    struct ItemReferenceType<detail::MappedCollection<TBaseCollection, TMappingFunction>> :
        public ItemType<detail::MappedCollection<TBaseCollection, TMappingFunction>>
    {
    };

    namespace detail
    {
        template <class TBaseCollection, class TMappingFunction>
        class MappedCollection :
            public SpatialCollection<MappedCollection<TBaseCollection, TMappingFunction>>
        {
        private:
            TBaseCollection _baseCollection;
            TMappingFunction _mappingFunction;
        public:
            MappedCollection(const MappedCollection<TBaseCollection, TMappingFunction>& other);

            MappedCollection(MappedCollection<TBaseCollection, TMappingFunction>&& other);

            MappedCollection(
                const TBaseCollection& baseCollection,
                TMappingFunction mappingFunction
            );

            MappedCollection(
                TBaseCollection&& baseCollection,
                TMappingFunction mappingFunction
            );

            MappedCollectionIterator<TBaseCollection, TMappingFunction>
            begin() const;

            MappedCollectionIterator<TBaseCollection, TMappingFunction>
            end() const;

            bool
            isEmpty() const;

            std::int64_t
            size() const;

            typename BoundsType<MappedCollection<TBaseCollection, TMappingFunction>>::Type
            bounds() const;
        };

        template <class TBaseCollection, class TMappingFunction>
        class MappedCollectionIterator :
            public boost::iterator_facade<
                MappedCollectionIterator<TBaseCollection, TMappingFunction>,
                typename ItemType<MappedCollection<TBaseCollection, TMappingFunction>>::Type,
                boost::forward_traversal_tag,
                typename ItemType<MappedCollection<TBaseCollection, TMappingFunction>>::Type
            >
        {
        private:
            typename IteratorType<TBaseCollection>::Type _baseIterator;
            const TMappingFunction* _mappingFunctionPtr;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(const MappedCollectionIterator<TBaseCollection, TMappingFunction>& other) const;

            typename ItemType<MappedCollection<TBaseCollection, TMappingFunction>>::Type
            dereference() const;
        public:
            MappedCollectionIterator();

            MappedCollectionIterator(
                typename IteratorType<TBaseCollection>::Type baseIterator,
                const TMappingFunction* mappingFunctionPtr
            );
        };
    }
    
    template <class TBaseCollection, class TMappingFunction>
    struct ScalingFunction<detail::MappedCollection<TBaseCollection, TMappingFunction>> :
        public ScalingFunction<
            SpatialCollection<detail::MappedCollection<TBaseCollection, TMappingFunction>>
        >
    {
    };

    template <class TBaseCollection, class TMappingFunction>
    struct TranslationFunction<detail::MappedCollection<TBaseCollection, TMappingFunction>> :
        public TranslationFunction<
            SpatialCollection<detail::MappedCollection<TBaseCollection, TMappingFunction>>
        >
    {
    };

    template <class TBaseCollection, class TMappingFunction, int iNumResultDimensions>
    struct TransformationFunction<
        detail::MappedCollection<TBaseCollection, TMappingFunction>,
        iNumResultDimensions
    > : public TransformationFunction<
            SpatialCollection<detail::MappedCollection<TBaseCollection, TMappingFunction>>,
            iNumResultDimensions
        >
    {
    };

    template <class TBaseCollection, class TMappingFunction, int iNumResultDimensions>
    struct MorphingFunction<
        detail::MappedCollection<TBaseCollection, TMappingFunction>,
        iNumResultDimensions
    > : public MorphingFunction<
            SpatialCollection<detail::MappedCollection<TBaseCollection, TMappingFunction>>,
            iNumResultDimensions
        >
    {
    };
}
