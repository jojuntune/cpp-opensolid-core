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

#include <OpenSolid/Core/SpatialSet/FilteredSet.declarations.hpp>

#include <OpenSolid/Core/SpatialSet/SetData.declarations.hpp>
#include <OpenSolid/Core/SpatialSet/SetNode.declarations.hpp>

#include <boost/intrusive_ptr.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <stack>

namespace opensolid
{
    namespace spatialset
    {
        template <class TElement, class TBoundsPredicate>
        class FilteredSet
        {
        private:
            boost::intrusive_ptr<SetData<TElement>> _setData;
            TBoundsPredicate _boundsPredicate;
        public:
            typedef FilteredSetIterator<TElement, TBoundsPredicate> Iterator;

            FilteredSet(
                const boost::intrusive_ptr<SpatialSetData<TElement>>& setData,
                TBoundsPredicate boundsPredicate
            );

            FilteredSetIterator<TElement, TBoundsPredicate>
            begin() const;

            FilteredSetIterator<TElement, TBoundsPredicate>
            end() const;
        };

        template <class TElement, class TBoundsPredicate>
        class FilteredSetIterator :
            public boost::iterator_facade<
                FilteredSetIterator<TElement, TBoundsPredicate>,
                TElement,
                boost::forward_traversal_tag
            >
        {
        private:
            SetNode<TElement>* _node;
            TBoundsPredicate _boundsPredicate;
            std::stack<SetNode<TElement>*> _stack;

            friend class boost::iterator_core_access;

            void
            increment();

            bool
            equal(const FilteredSetIterator<TElement, TBoundsPredicate>& other) const;;

            const TElement&
            dereference() const;
        public:
            FilteredSetIterator();

            FilteredSetIterator(SetNode<TElement>* root, TBoundsPredicate boundsPredicate);

            FilteredSetIterator(const FilteredSetIterator<TElement, TBoundsPredicate>& other);

            FilteredSetIterator(FilteredSetIterator<TElement, TBoundsPredicate>&& other);

            void
            operator=(const FilteredSetIterator<TElement, TBoundsPredicate>& other);

            void
            operator=(FilteredSetIterator<TElement, TBoundsPredicate>&& other);
        };
    }
}
