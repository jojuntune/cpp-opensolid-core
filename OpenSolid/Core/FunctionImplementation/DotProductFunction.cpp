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

#include <OpenSolid/Core/FunctionImplementation/DotProductFunction.hpp>

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    DotProductFunction::DotProductFunction(
        const Function& firstOperand,
        const Function& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(firstOperand.numDimensions() == secondOperand.numDimensions());
    }
    
    int DotProductFunction::numDimensions() const {
        return 1;
    }

    bool DotProductFunction::isDuplicateOf(const Function& function) const {
        return BinaryOperation::IsDuplicate(this, function, true);
    }

    Function DotProductFunction::deduplicated(Deduplicator& deduplicator) const {
        Function deduplicatedFirstOperand = firstOperand().deduplicated(others);
        Function deduplicatedSecondOperand = secondOperand().deduplicated(others);
        return new DotProductFunction(deduplicatedFirstOperand, deduplicatedSecondOperand);
    }
    
    void DotProductFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        EvaluateCache<double>& cache
    ) const {
        MapXcd firstValues = cache.results(firstOperand(), parameterValues);
        MapXcd secondValues = cache.results(secondOperand(), parameterValues);
        results = firstValues.cwiseProduct(secondValues).colwise().sum();
    }
    
    void DotProductFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        EvaluateCache<Interval>& cache
    ) const {
        MapXcI firstBounds = cache.results(firstOperand(), parameterBounds);
        MapXcI secondBounds = cache.results(secondOperand(), parameterBounds);
        results = firstBounds.cwiseProduct(secondBounds).colwise().sum();
    }

    Function DotProductFunction::derivative(int index) const {
        return firstOperand().derivative(index).dot(secondOperand())
            + firstOperand().dot(secondOperand().derivative(index));
    }
    
    void DotProductFunction::debug(std::ostream& stream, int indent) const {
        stream << "DotProductFunction" << std::endl;
        firstOperand().debug(stream, indent + 1);
        secondOperand().debug(stream, indent + 1);
    }
}
