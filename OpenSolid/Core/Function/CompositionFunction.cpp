/*************************************************************************************
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

#include <OpenSolid/Core/Function/CompositionFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    CompositionFunction::CompositionFunction(
        const Function& outerFunction,
        const Function& innerFunction
    ) : _outerFunction(outerFunction),
        _innerFunction(innerFunction) {

        assert(innerFunction.numDimensions() == outerFunction.numParameters());
    }
    
    int CompositionFunction::numDimensions() const {
        return outerFunction().numDimensions();
    }
    
    int CompositionFunction::numParameters() const {
        return innerFunction().numParameters();
    }

    Function CompositionFunction::deduplicated(std::vector<Function>& others) const {
        Function deduplicatedInnerFunction = _innerFunction.deduplicated(others);
        Function deduplicatedOuterFunction = _outerFunction.deduplicated(others);
        return deduplicatedOuterFunction(deduplicatedInnerFunction);
    }

    void CompositionFunction::evaluate(const MapXcd& parameterValues, MapXd& results) const {
        results = outerFunction()(innerFunction()(parameterValues));
    }

    void CompositionFunction::evaluate(const MapXcI& parameterBounds, MapXI& results) const {
        results = outerFunction()(innerFunction()(parameterBounds));
    }

    Function CompositionFunction::derivative(int index) const {
        Function innerDerivative = innerFunction().derivative(index);

        Function result = outerFunction().derivative(0)(innerFunction()) *
            innerDerivative.component(0);

        for (int i = 1; i < outerFunction().numParameters(); ++i) {
            Function outerDerivative = outerFunction().derivative(i);
            result = result + outerDerivative(innerFunction()) * innerDerivative.component(i);
        }

        return result;
    }
        
    Function CompositionFunction::compose(const Function& innerFunction) const {
        return outerFunction()(this->innerFunction()(innerFunction));
    }
    
    void CompositionFunction::debug(std::ostream& stream, int indent) const {
        stream << "CompositionFunction" << std::endl;
        innerFunction().debug(stream, indent + 1);
        outerFunction().debug(stream, indent + 1);
    }
}
