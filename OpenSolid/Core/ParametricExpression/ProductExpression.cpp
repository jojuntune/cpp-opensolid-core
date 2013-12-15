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
************************************************************************************/

#include <OpenSolid/Core/ParametricExpression/ProductExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    ProductExpression::numDimensionsImpl() const {
        return secondOperand()->numDimensions();
    }
    
    void
    ProductExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd firstValues = evaluator.evaluate(firstOperand(), parameterValues);
        MapXcd secondValues = evaluator.evaluate(secondOperand(), parameterValues);
        results = secondValues * firstValues.topRows<1>().asDiagonal();
    }
    
    void
    ProductExpression::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI firstBounds = evaluator.evaluate(firstOperand(), parameterBounds);
        MapXcI secondBounds = evaluator.evaluate(secondOperand(), parameterBounds);
        results = secondBounds * firstBounds.topRows<1>().asDiagonal();
    }

    void
    ProductExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        double multiplierValue = evaluator.evaluate(firstOperand(), parameterValues).value();
        MapXcd multiplicandValue = evaluator.evaluate(secondOperand(), parameterValues);
        MapXcd multiplierJacobian = evaluator.evaluateJacobian(firstOperand(), parameterValues);
        MapXcd multiplicandJacobian = evaluator.evaluateJacobian(secondOperand(), parameterValues);
        results = multiplierValue * multiplicandJacobian + multiplicandValue * multiplierJacobian;
    }
    
    void
    ProductExpression::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        Interval multiplierBounds = evaluator.evaluate(firstOperand(), parameterBounds).value();
        MapXcI multiplicandValue = evaluator.evaluate(secondOperand(), parameterBounds);
        MapXcI multiplierJacobian = evaluator.evaluateJacobian(firstOperand(), parameterBounds);
        MapXcI multiplicandJacobian = evaluator.evaluateJacobian(secondOperand(), parameterBounds);
        results = multiplierBounds * multiplicandJacobian + multiplicandValue * multiplierJacobian;
    }

    ExpressionImplementationPtr
    ProductExpression::derivativeImpl(int parameterIndex) const {
        return firstOperand()->derivative(parameterIndex) * secondOperand()
            + firstOperand() * secondOperand()->derivative(parameterIndex);
    }

    bool
    ProductExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other, true);
    }
    
    void
    ProductExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "ProductExpression" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    ProductExpression::withNewOperandsImpl(
        const ExpressionImplementationPtr& newFirstOperand,
        const ExpressionImplementationPtr& newSecondOperand
    ) const {
        return newFirstOperand * newSecondOperand;
    }

    ProductExpression::ProductExpression(
        const ExpressionImplementationPtr& multiplier,
        const ExpressionImplementationPtr& multiplicand
    ) : BinaryOperation(multiplier, multiplicand) {

        assert(multiplier->numDimensions() == 1);
    }
}
