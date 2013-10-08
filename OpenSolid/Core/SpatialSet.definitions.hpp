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

#include <OpenSolid/Core/SpatialSet.declarations.hpp>

#include <OpenSolid/Core/Transformable.definitions.hpp>
#include <OpenSolid/Core/BoundsFunction.definitions.hpp>

#include <vector>

namespace opensolid
{
    template <class TElement>
    class SpatialSet :
        public Transformable<SpatialSet<TElement>>
    {
    private:
        struct Node
        {
            typename BoundsType<TElement>::Type bounds;
            const void* left;
            const void* right;
        };

        struct BoundsData
        {
            typename BoundsType<TElement>::Type bounds;
            const TElement* element;
        };

        std::vector<TElement> _elements;
        std::vector<Node> _nodes;

        Node*
        init(
            Node* node,
            BoundsData** begin,
            BoundsData** end,
            typename BoundsType<TElement>::Type& overallBounds,
            std::int64_t sortIndex
        );

        void
        init(const BoundsFunction<TElement>& boundsFunction);

        void
        copy(const SpatialSet<TElement>& otherSet);

        const Node*
        rootNode() const;
        
        template <class TPredicate, class TVisitor>
        void
        visit(
            const Node* node,
            const TPredicate& predicate,
            const TVisitor& visitor
        ) const;
    public:
        typedef typename std::vector<TElement>::const_iterator Iterator;

        SpatialSet();

        SpatialSet(const SpatialSet<TElement>& otherSet);

        SpatialSet(SpatialSet<TElement>&& otherSet);

        SpatialSet(
            const std::vector<TElement>& elements,
            BoundsFunction<TElement> boundsFunction = BoundsFunction<TElement>()
        );

        SpatialSet(
            std::vector<TElement>&& elements,
            BoundsFunction<TElement> boundsFunction = BoundsFunction<TElement>()
        );
        
        template <class TIterator>
        SpatialSet(
            TIterator begin,
            TIterator end,
            BoundsFunction<TElement> boundsFunction = BoundsFunction<TElement>()
        );

        Iterator
        begin() const;

        Iterator
        end() const;

        const TElement&
        front() const;

        const TElement&
        back() const;

        const TElement&
        operator[](std::int64_t index) const;

        void
        swap(SpatialSet<TElement>& otherSet);
        
        void
        operator=(const SpatialSet<TElement>& otherSet);
        
        void
        operator=(SpatialSet<TElement>&& otherSet);
        
        std::int64_t
        size() const;

        bool
        isEmpty() const;

        typename BoundsType<TElement>::Type
        bounds() const;

        void
        clear();

        template <class TVisitor>
        void
        forEachOverlapping(
            const typename BoundsType<TElement>::Type& predicateBounds,
            const TVisitor& visitor
        ) const;

        std::vector<TElement>
        overlapping(const typename BoundsType<TElement>::Type& predicateBounds) const;

        // TODO: filtered? mapped?
    };
    
    template <class TElement>
    std::ostream&
    operator<<(std::ostream& stream, const SpatialSet<TElement>& set);
}
    
////////// Specializations //////////

namespace opensolid
{
    template <class TElement>
    struct NumDimensions<SpatialSet<TElement>>
    {
        static const int Value = NumDimensions<TElement>::Value;
    };

    template <class TElement, int iNumResultDimensions>
    struct ChangeDimensions<SpatialSet<TElement>, iNumResultDimensions>
    {
        typedef SpatialSet<typename ChangeDimensions<TElement, iNumResultDimensions>::Type> Type;
    };

    template <class TElement>
    struct ScalingFunction<SpatialSet<TElement>>
    {
        SpatialSet<TElement>
        operator()(const SpatialSet<TElement>& set, double scale) const;
    };

    template <class TElement>
    struct TranslationFunction<SpatialSet<TElement>>
    {
        template <class TVector>
        SpatialSet<TElement>
        operator()(const SpatialSet<TElement>& set, const EigenBase<TVector>& vector) const;
    };

    template <class TElement, int iNumResultDimensions>
    struct TransformationFunction<SpatialSet<TElement>, iNumResultDimensions>
    {
        template <class TMatrix>
        SpatialSet<typename ChangeDimensions<TElement, iNumResultDimensions>::Type>
        operator()(const SpatialSet<TElement>& set, const EigenBase<TMatrix>& matrix) const;
    };

    template <class TElement, int iNumResultDimensions>
    struct MorphingFunction<SpatialSet<TElement>, iNumResultDimensions>
    {
        SpatialSet<typename ChangeDimensions<TElement, iNumResultDimensions>::Type>
        operator()(
            const SpatialSet<TElement>& set,
            const Function<iNumResultDimensions, NumDimensions<TElement>::Value>& function
        ) const;
    };

    template <class TElement>
    struct BoundsType<SpatialSet<TElement>>
    {
        typedef typename BoundsType<TElement>::Type Type;
    };
}
