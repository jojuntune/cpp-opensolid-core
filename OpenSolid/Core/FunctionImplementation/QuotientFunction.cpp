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

#include <OpenSolid/Core/FunctionImplementation/QuotientFunction.hpp>

namespace opensolid
{
    QuotientFunction::QuotientFunction(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(secondOperand->numDimensions() == 1);
    }
    
    int
    QuotientFunction::numDimensionsImpl() const {
        return firstOperand()->numDimensions();
    }

    bool
    QuotientFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return BinaryOperation::IsDuplicate(this, function, false);
    }

    FunctionImplementationPtr
    QuotientFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        FunctionImplementationPtr deduplicatedFirstOperand = firstOperand()->deduplicated(deduplicationCache);
        FunctionImplementationPtr deduplicatedSecondOperand = secondOperand()->deduplicated(deduplicationCache);
        return new QuotientFunction(deduplicatedFirstOperand, deduplicatedSecondOperand);
    }
    
    void
    QuotientFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd firstValues = evaluator.evaluate(firstOperand(), parameterValues);
        MapXcd secondValues = evaluator.evaluate(secondOperand(), parameterValues);
        results = firstValues.array() / secondValues.replicate(numDimensions(), 1).array();
    }
    
    void
    QuotientFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI firstBounds = evaluator.evaluate(firstOperand(), parameterBounds);
        MapXcI secondBounds = evaluator.evaluate(secondOperand(), parameterBounds);
        results = firstBounds.array() / secondBounds.replicate(numDimensions(), 1).array();
    }

    FunctionImplementationPtr
    QuotientFunction::derivativeImpl(int parameterIndex) const {
        FunctionImplementationPtr firstDerivative = firstOperand()->derivative(parameterIndex);
        FunctionImplementationPtr secondDerivative = secondOperand()->derivative(parameterIndex);
        return(firstDerivative * secondOperand() - firstOperand() * secondDerivative) /
            secondOperand().squaredNorm();
    }
    
    void
    QuotientFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "QuotientFunction" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }
}
