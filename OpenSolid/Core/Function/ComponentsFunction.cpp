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

#include <OpenSolid/Core/Function/ComponentsFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ComponentsFunction::ComponentsFunction(
        const Function& operand,
        int startIndex,
        int numComponents
    ) : UnaryOperation(operand),
        _startIndex(startIndex),
        _numComponents(numComponents) {

        assert(startIndex >= 0);
        assert(numComponents > 0);
        assert(startIndex + numComponents <= operand.numDimensions());
    }

    int ComponentsFunction::numDimensions() const {
        return numComponents();
    }

    bool ComponentsFunction::isDuplicate(const Function& function) const {
        const ComponentsFunction* other =
            dynamic_cast<const ComponentsFunction*>(function.implementation());
        if (other) {
            return this->startIndex() == other->startIndex() &&
                this->numComponents() == other->numComponents() &&
                this->operand().isDuplicate(other->operand());
        } else {
            return false;
        }
    }

    Function ComponentsFunction::deduplicated(std::vector<Function>& others) const {
        return new ComponentsFunction(
            operand().deduplicated(others),
            startIndex(),
            numComponents()
        );
    }
    
    void ComponentsFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& cache
    ) const {
        MapXcd operandValues = cache.results(operand(), parameterValues);
        results = operandValues.middleRows(startIndex(), numComponents());
    }
    
    void ComponentsFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& cache
    ) const {
        MapXcI operandBounds = cache.results(operand(), parameterBounds);
        results = operandBounds.middleRows(startIndex(), numComponents());
    }

    Function ComponentsFunction::derivative(int parameterIndex) const {
        return operand().derivative(parameterIndex).components(startIndex(), numComponents());
    }
    
    Function ComponentsFunction::components(int startIndex, int numComponents) const {
        assert(startIndex >= 0 && startIndex < this->numComponents());
        assert(numComponents <= this->numComponents());
        return operand().components(this->startIndex() + startIndex, numComponents);
    }
    
    Function ComponentsFunction::compose(const Function& innerFunction) const {
        return operand()(innerFunction).components(startIndex(), numComponents());
    }
    
    void ComponentsFunction::debug(std::ostream& stream, int indent) const {
        stream << "ComponentsFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
