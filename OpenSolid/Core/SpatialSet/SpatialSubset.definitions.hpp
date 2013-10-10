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

#include <OpenSolid/Core/SpatialSubset.declarations.hpp>

#include <OpenSolid/Core/SpatialSetNode.definitions.hpp>

#include <boost/intrusive_ptr.hpp>

namespace opensolid
{
    namespace spatialset
    {
        template <class TElement, class TBoundsPredicate, class TElementPredicate>
        class SpatialSubset
        {
        private:
            boost::intrusive_ptr<SpatialSetData<TElement>> _setData;
            TBoundsPredicate _boundsPredicate;
            TElementPredicate _elementPredicate;
        public:
            SpatialSubset();

            SpatialSubset(
                const boost::intrusive_ptr<SpatialSetData<TElement>>& setData,
                TBoundsPredicate boundsPredicate = TBoundsPredicate(),
                TElementPredicate elementPredicate = TElementPredicate()
            );
        };

        struct NullPredicate
        {
            template <class TArgument>
            bool
            operator()(const TArgument& argument) const;
        };

        template <class TFirstPredicate, class TSecondPredicate>
        class CombinedPredicate
        {
        private:
            TFirstPredicate _firstPredicate;
            TSecondPredicate _secondPredicate;
        public:
            CombinedPredicate(TFirstPredicate firstPredicate, TSecondPredicate secondPredicate);

            template <class TArgument>
            bool
            operator()(const TArgument& argument) const;
        };
    }
}
