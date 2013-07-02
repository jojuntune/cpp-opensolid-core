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

#include <OpenSolid/Core/FunctionImplementation/IdentityFunction.hpp>

#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{
    int
    IdentityFunction::numDimensionsImpl() const {
        return _numDimensions;
    }

    int
    IdentityFunction::numParametersImpl() const {
        return _numDimensions;
    }
    
    void
    IdentityFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator&
    ) const {
        results = parameterValues;
    }
    
    void
    IdentityFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator&
    ) const {
        results = parameterBounds;
    }

    FunctionImplementationPtr
    IdentityFunction::derivativeImpl(int parameterIndex) const {
        return new ConstantFunction(
            VectorXd::Unit(numDimensions(), parameterIndex),
            numDimensions()
        );
    }

    bool
    IdentityFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        // FunctionImplementation already checks that numbers of parameters/dimensions are equal
        return true;
    }

    FunctionImplementationPtr
    IdentityFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return this;
    }
    
    FunctionImplementationPtr
    IdentityFunction::composedImpl(const FunctionImplementationPtr& innerFunction) const {
        return innerFunction;
    }
    
    void
    IdentityFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "IdentityFunction" << std::endl;
    }

    IdentityFunction::IdentityFunction(int numDimensions) :
        _numDimensions(numDimensions) {

        assert(numDimensions > 0);
    }
}
