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

#include <OpenSolid/Core/Transformation/CompoundTransformation.definitions.hpp>

#include <OpenSolid/Core/Transformation.hpp>

namespace opensolid
{
    namespace detail
    {
        template <class TFirst, class TSecond>
        CompoundTransformation<TFirst, TSecond>::CompoundTransformation(
            const TFirst& first,
            const TSecond& second
        ) : _first(first),
            _second(second) {
        }

        template <class TFirst, class TSecond>
        inline
        const TFirst&
        CompoundTransformation<TFirst, TSecond>::first() const {
            return _first;
        }

        template <class TFirst, class TSecond>
        inline
        const TSecond&
        CompoundTransformation<TFirst, TSecond>::second() const {
            return _second;
        }

        template <class TFirst, class TSecond>
        inline
        double
        CompoundTransformation<TFirst, TSecond>::scale() const {
            return first().scale() * second().scale();
        }

        template <class TFirst, class TSecond> template <class TTransformable>
        inline
        TTransformable
        CompoundTransformation<TFirst, TSecond>::transform(
            const TTransformable& transformable
        ) const {
            return second().transform(first().transform(transformable));
        }
    }
}
