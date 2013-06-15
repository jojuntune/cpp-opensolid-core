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

#include <OpenSolid/Core/Function/Deduplicator.hpp>
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    FunctionImplementationPtr
    Deduplicator::deduplicate()(const FunctionImplementationPtr& functionImplementation) {
        // If a null pointer is passed, simply return it
        if (!functionImplementation) {
            return functionImplementation;
        }

        // Try to find a function implementation in the cache that is a duplicate of the given
        // function implementation
        auto iterator = std::find_if(
            _cache.begin(),
            _cache.end(),
            [&functionImplementation] (
                const FunctionImplementationPtr& cachedFunctionImplementation
            ) -> bool {
                return functionImplementation->isDuplicateOf(cachedFunctionImplementation);
            }
        );

        // Return the cached duplicate if one was found
        if (iterator < _cache.end()) {
            return *iterator;
        }

        // No matching function implementation was found: add a deduplicated copy of this
        // function implementation to the list, then return it
        FunctionImplementationPtr result = functionImplementation->deduplicated(*this);
        _cache.push_back(result);
        return result;
    }
}
