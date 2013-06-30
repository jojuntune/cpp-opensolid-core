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

#include <OpenSolid/Core/FunctionImplementation/ConcatenationFunction.hpp>

namespace opensolid
{
    int
    ConcatenationFunction::numDimensionsImpl() const {
        return firstOperand()->numDimensions() + secondOperand()->numDimensions();
    }
    
    void
    ConcatenationFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results.topRows(firstOperand()->numDimensions()) =
            evaluator.evaluate(firstOperand(), parameterValues);
        results.bottomRows(secondOperand()->numDimensions()) =
            evaluator.evaluate(secondOperand(), parameterValues);
    }
    
    void
    ConcatenationFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results.topRows(firstOperand()->numDimensions()) =
            evaluator.evaluate(firstOperand(), parameterBounds);
        results.bottomRows(secondOperand()->numDimensions()) =
            evaluator.evaluate(secondOperand(), parameterBounds);
    }
    
    FunctionImplementationPtr
    ConcatenationFunction::derivativeImpl(int parameterIndex) const {
        return firstOperand()->derivative(parameterIndex)->concatenated(
            secondOperand()->derivative(parameterIndex)
        );
    }

    bool
    ConcatenationFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other, false);
    }
    
    FunctionImplementationPtr
    ConcatenationFunction::componentsImpl(int startIndex, int numComponents) const {
        int firstDimensions = firstOperand()->numDimensions();
        if (startIndex + numComponents <= firstDimensions) {
            return firstOperand()->components(startIndex, numComponents);
        } else if (startIndex >= firstDimensions) {
            return secondOperand()->components(startIndex - firstDimensions, numComponents);
        } else {
            return new ConcatenationFunction(
                firstOperand()->components(startIndex, firstDimensions - startIndex),
                secondOperand()->components(0, startIndex + numComponents - firstDimensions)
            );
        }
    }
    
    void
    ConcatenationFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "ConcatenationFunction" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    ConcatenationFunction::withNewOperandsImpl(
        const FunctionImplementationPtr& newFirstOperand,
        const FunctionImplementationPtr& newSecondOperand
    ) const {
        return newFirstOperand->concatenated(newSecondOperand);
    }

    ConcatenationFunction::ConcatenationFunction(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {
    }
}
