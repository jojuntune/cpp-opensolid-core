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

#include <OpenSolid/Core/FunctionImplementation/CompositionFunction.hpp>

namespace opensolid
{   
    int
    CompositionFunction::numDimensionsImpl() const {
        return outerFunction()->numDimensions();
    }
    
    int
    CompositionFunction::numParametersImpl() const {
        return innerFunction()->numParameters();
    }

    void
    CompositionFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd innerValues = evaluator.evaluate(innerFunction(), parameterValues);
        results = evaluator.evaluate(outerFunction(), innerValues);
    }

    void
    CompositionFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI innerBounds = evaluator.evaluate(innerFunction(), parameterBounds);
        results = evaluator.evaluate(outerFunction(), innerBounds);
    }

    FunctionImplementationPtr
    CompositionFunction::derivativeImpl(int parameterIndex) const {
        FunctionImplementationPtr innerDerivative =
            innerFunction()->derivative(parameterIndex);

        FunctionImplementationPtr result =
            outerFunction()->derivative(0)->composed(innerFunction()) *
            innerDerivative->component(0);

        for (int i = 1; i < outerFunction()->numParameters(); ++i) {
            result = result + outerFunction()->derivative(i)->composed(innerFunction()) *
                innerDerivative->component(i);
        }

        return result;
    }

    bool
    CompositionFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        FunctionImplementationPtr otherOuterFunction =
            other->cast<CompositionFunction>()->outerFunction();
        FunctionImplementationPtr otherInnerFunction =
            other->cast<CompositionFunction>()->innerFunction();

        return outerFunction()->isDuplicateOf(otherOuterFunction) &&
            innerFunction()->isDuplicateOf(otherInnerFunction);
    }

    FunctionImplementationPtr
    CompositionFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        FunctionImplementationPtr deduplicatedOuterFunction = outerFunction()->deduplicated(deduplicationCache);
        FunctionImplementationPtr deduplicatedInnerFunction = innerFunction()->deduplicated(deduplicationCache);
        return new CompositionFunction(deduplicatedOuterFunction, deduplicatedInnerFunction);
    }
        
    FunctionImplementationPtr
    CompositionFunction::composedImpl(const FunctionImplementationPtr& innerFunction) const {
        return outerFunction()->composed(this->innerFunction()->composed(innerFunction));
    }
    
    void
    CompositionFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "CompositionFunction" << std::endl;
        outerFunction()->debug(stream, indent + 1);
        innerFunction()->debug(stream, indent + 1);
    }

    CompositionFunction::CompositionFunction(
        const FunctionImplementationPtr& outerFunction,
        const FunctionImplementationPtr& innerFunction
    ) : _outerFunction(outerFunction),
        _innerFunction(innerFunction) {

        assert(outerFunction->numParameters() == innerFunction->numDimensions());
    }
}
