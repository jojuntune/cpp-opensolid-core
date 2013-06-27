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

#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{
    class ParameterFunction :
        public FunctionImplementation
    {
    private:
        int _parameterIndex;
        int _numParameters;
        
        OPENSOLID_CORE_EXPORT
        int
        numDimensionsImpl() const;
        
        OPENSOLID_CORE_EXPORT
        int
        numParametersImpl() const;
        
        OPENSOLID_CORE_EXPORT
        void evaluateImpl(
            const MapXcd& parameterValues,
            MapXd& results,
            Evaluator& evaluator
        ) const;
        
        OPENSOLID_CORE_EXPORT
        void
        evaluateImpl(
            const MapXcI& parameterBounds,
            MapXI& results,
            Evaluator& evaluator
        ) const;

        OPENSOLID_CORE_EXPORT
        bool
        isDuplicateOfImpl(const FunctionImplementationPtr& other) const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        deduplicatedImpl(DeduplicationCache& deduplicationCache) const;

        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        derivativeImpl(int parameterIndex) const;
        
        OPENSOLID_CORE_EXPORT
        FunctionImplementationPtr
        composeImpl(const FunctionImplementationPtr& innerFunction) const;
        
        OPENSOLID_CORE_EXPORT
        void
        debugImpl(std::ostream& stream, int indent) const;
    public:
        OPENSOLID_CORE_EXPORT ParameterFunction(int parameterIndex, int numParameters);
        
        int parameterIndex() const;
    };
}

////////// Implementation //////////

namespace opensolid
{
    inline int
    ParameterFunction::parameterIndex() const {
        return _parameterIndex;
    }
}
