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

#include <OpenSolid/Core/SpatialSubset.definitions.hpp>

namespace opensolid
{
    namespace spatialset
    {
        template <class TElement, class TBoundsPredicate, class TElementPredicate>
        SpatialSubset<TElement, TBoundsPredicate, TElementPredicate>::SpatialSubset() {
        }

        template <class TElement, class TBoundsPredicate, class TElementPredicate>
        SpatialSubset<TElement, TBoundsPredicate, TElementPredicate>::SpatialSubset(
            const boost::intrusive_ptr<SpatialSetData<TElement>>& setData,
            TBoundsPredicate boundsPredicate = TBoundsPredicate(),
            TElementPredicate elementPredicate = TElementPredicate()
        ) : _setData(setData),
            _boundsPredicate(boundsPredicate),
            _elementPredicate(elementPredicate) {

        }

        template <class TArgument>
        inline
        bool
        NullPredicate::operator()(const TArgument& argument) const {
            return true;
        }

        template <class TFirstPredicate, class TSecondPredicate>
        CombinedPredicate<TFirstPredicate, TSecondPredicate>::CombinedPredicate(
            TFirstPredicate firstPredicate,
            TSecondPredicate secondPredicate
        ) : _firstPredicate(firstPredicate),
            _secondPredicate(secondPredicate) {
        }

        template <class TFirstPredicate, class TSecondPredicate> template <class TArgument>
        inline
        bool
        CombinedPredicate<TFirstPredicate, TSecondPredicate>::operator()(
            const TArgument& argument
        ) const {
            return _firstPredicate(argument) && _secondPredicate(argument);
        }
    }
}
