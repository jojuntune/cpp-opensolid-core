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

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    CompositionFunction::CompositionFunction(
        const Function& outerFunction,
        const Function& innerFunction
    ) : BinaryOperation(outerFunction, innerFunction) {

        assert(outerFunction.numParameters() == innerFunction.numDimensions());
    }
    
    int CompositionFunction::numDimensions() const {
        return firstOperand().numDimensions();
    }
    
    int CompositionFunction::numParameters() const {
        return secondOperand().numParameters();
    }

    bool CompositionFunction::isDuplicate(const Function& function) const {
        return BinaryOperation::IsDuplicate(this, function, false);
    }

    Function CompositionFunction::deduplicated(std::vector<Function>& others) const {
        Function deduplicatedOuterFunction = firstOperand().deduplicated(others);
        Function deduplicatedInnerFunction = secondOperand().deduplicated(others);
        return new CompositionFunction(deduplicatedOuterFunction, deduplicatedInnerFunction);
    }

    void CompositionFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& cache
    ) const {
        MapXcd innerValues = cache.results(secondOperand(), parameterValues);
        results = cache.results(firstOperand(), innerValues);
    }

    void CompositionFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& cache
    ) const {
        MapXcI innerBounds = cache.results(secondOperand(), parameterBounds);
        results = cache.results(firstOperand(), innerBounds);
    }

    Function CompositionFunction::derivative(int index) const {
        Function innerDerivative = secondOperand().derivative(index);

        Function result = firstOperand().derivative(0).compose(secondOperand()) *
            innerDerivative.component(0);

        for (int i = 1; i < firstOperand().numParameters(); ++i) {
            result = result + firstOperand().derivative(i).compose(secondOperand()) *
                innerDerivative.component(i);
        }

        return result;
    }
        
    Function CompositionFunction::compose(const Function& innerFunction) const {
        return firstOperand().compose(secondOperand().compose(innerFunction));
    }
    
    void CompositionFunction::debug(std::ostream& stream, int indent) const {
        stream << "CompositionFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
