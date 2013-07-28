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

#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{   
    int
    QuotientFunction::numDimensionsImpl() const {
        return firstOperand()->numDimensions();
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

    void
    QuotientFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd dividendValues = evaluator.evaluate(firstOperand(), parameterValues);
        double divisorValue = evaluator.evaluate(secondOperand(), parameterValues).value();
        MapXcd dividendJacobian = evaluator.evaluateJacobian(firstOperand(), parameterValues);
        MapXcd divisorJacobian = evaluator.evaluateJacobian(secondOperand(), parameterValues);
        results = (dividendJacobian * divisorValue - dividendValues * divisorJacobian) / 
            (divisorValue * divisorValue);
    }
    
    void
    QuotientFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI dividendBounds = evaluator.evaluate(firstOperand(), parameterBounds);
        Interval divisorBounds = evaluator.evaluate(secondOperand(), parameterBounds).value();
        MapXcI dividendJacobian = evaluator.evaluateJacobian(firstOperand(), parameterBounds);
        MapXcI divisorJacobian = evaluator.evaluateJacobian(secondOperand(), parameterBounds);
        results = (dividendJacobian * divisorBounds - dividendBounds * divisorJacobian) / 
            divisorBounds.squared();
    }

    FunctionImplementationPtr
    QuotientFunction::derivativeImpl(int parameterIndex) const {
        FunctionImplementationPtr firstDerivative = firstOperand()->derivative(parameterIndex);
        FunctionImplementationPtr secondDerivative = secondOperand()->derivative(parameterIndex);
        return(firstDerivative * secondOperand() - firstOperand() * secondDerivative) /
            secondOperand()->squaredNorm();
    }

    bool
    QuotientFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other, false);
    }
    
    void
    QuotientFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "QuotientFunction" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    QuotientFunction::withNewOperandsImpl(
        const FunctionImplementationPtr& newFirstOperand,
        const FunctionImplementationPtr& newSecondOperand
    ) const {
        return newFirstOperand / newSecondOperand;
    }

    QuotientFunction::QuotientFunction(
        const FunctionImplementationPtr& firstOperand,
        const FunctionImplementationPtr& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(secondOperand->numDimensions() == 1);
    }
}
