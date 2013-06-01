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

#include <OpenSolid/Core/FunctionImplementation/UnaryOperation.hpp>

namespace opensolid
{
    class ComponentsFunction : public UnaryOperation
    {
    private:
        int _startIndex;
        int _numComponents;
    public:
        OPENSOLID_CORE_EXPORT ComponentsFunction(
            const Function& operand,
            int startIndex,
            int numComponents
        );
        
        int startIndex() const;
        int numComponents() const;
        
        OPENSOLID_CORE_EXPORT int numDimensions() const;

        OPENSOLID_CORE_EXPORT bool isDuplicateOf(const Function& other) const;
        OPENSOLID_CORE_EXPORT Function deduplicated(Deduplicator& deduplicator) const;
        
        OPENSOLID_CORE_EXPORT void evaluate(
            const MapXcd& parameterValues,
            MapXd& results,
            EvaluateCache<double>& cache
        ) const;
        
        OPENSOLID_CORE_EXPORT void evaluate(
            const MapXcI& parameterBounds,
            MapXI& results,
            EvaluateCache<Interval>& cache
        ) const;

        OPENSOLID_CORE_EXPORT Function derivative(int parameterIndex) const;
        
        OPENSOLID_CORE_EXPORT Function components(int startIndex, int numComponents) const;

        OPENSOLID_CORE_EXPORT Function compose(const Function& innerFunction) const;
        
        OPENSOLID_CORE_EXPORT void debug(std::ostream& stream, int indent) const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline int ComponentsFunction::startIndex() const {
        return _startIndex;
    }

    inline int ComponentsFunction::numComponents() const {
        return _numComponents;
    }
}
