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

#include <OpenSolid/Core/Function/ConcatenationFunction.hpp>

// Public headers
#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    ConcatenationFunction::ConcatenationFunction(
        const Function& firstOperand,
        const Function& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {
    }
    
    int ConcatenationFunction::numDimensions() const {
        return firstOperand().numDimensions() + secondOperand().numDimensions();
    }

    bool ConcatenationFunction::isDuplicate(const Function& function) const {
        return BinaryOperation::IsDuplicate(this, function, false);
    }

    Function ConcatenationFunction::deduplicated(std::vector<Function>& others) const {
        Function deduplicatedFirstOperand = firstOperand().deduplicated(others);
        Function deduplicatedSecondOperand = secondOperand().deduplicated(others);
        return new ConcatenationFunction(deduplicatedFirstOperand, deduplicatedSecondOperand);
    }
    
    void ConcatenationFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        ResultCacheXd& cache
    ) const {
        results.topRows(firstOperand().numDimensions()) =
            cache.results(firstOperand(), parameterValues);
        results.bottomRows(secondOperand().numDimensions()) =
            cache.results(secondOperand(), parameterValues);
    }
    
    void ConcatenationFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        ResultCacheXI& cache
    ) const {
        results.topRows(firstOperand().numDimensions()) =
            cache.results(firstOperand(), parameterBounds);
        results.bottomRows(secondOperand().numDimensions()) =
            cache.results(secondOperand(), parameterBounds);
    }
    
    Function ConcatenationFunction::derivative(int index) const {
        return firstOperand().derivative(index).concatenate(secondOperand().derivative(index));
    }
    
    Function ConcatenationFunction::components(int startIndex, int numComponents) const {
        int firstDimensions = firstOperand().numDimensions();
        if (startIndex + numComponents <= firstDimensions) {
            return firstOperand().components(startIndex, numComponents);
        } else if (startIndex >= firstDimensions) {
            return secondOperand().components(startIndex - firstDimensions, numComponents);
        } else {
            return new ConcatenationFunction(
                firstOperand().components(startIndex, firstDimensions - startIndex),
                secondOperand().components(0, startIndex + numComponents - firstDimensions)
            );
        }
    }
    
    Function ConcatenationFunction::compose(const Function& innerFunction) const {
        return firstOperand()(innerFunction).concatenate(secondOperand()(innerFunction));
    }
    
    void ConcatenationFunction::debug(std::ostream& stream, int indent) const {
        stream << "ConcatenationFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
