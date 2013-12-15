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

#include <OpenSolid/Core/ParametricExpression/CrossProductExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    CrossProductExpression::numDimensionsImpl() const {
        return 3;
    }
    
    void
    CrossProductExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd firstValues = evaluator.evaluate(firstOperand(), parameterValues);
        MapXcd secondValues = evaluator.evaluate(secondOperand(), parameterValues);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = firstValues.col(i).head<3>().cross(secondValues.col(i).head<3>());
        }
    }
    
    void
    CrossProductExpression::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI firstBounds = evaluator.evaluate(firstOperand(), parameterBounds);
        MapXcI secondBounds = evaluator.evaluate(secondOperand(), parameterBounds);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = firstBounds.col(i).head<3>().cross(secondBounds.col(i).head<3>());
        }
    }

    void
    CrossProductExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        Vector3d firstValue = evaluator.evaluate(firstOperand(), parameterValues);
        Vector3d secondValue = evaluator.evaluate(secondOperand(), parameterValues);
        MapXcd firstJacobian = evaluator.evaluateJacobian(firstOperand(), parameterValues);
        MapXcd secondJacobian = evaluator.evaluateJacobian(secondOperand(), parameterValues);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = firstJacobian.col(i).head<3>().cross(secondValue) +
                firstValue.cross(secondJacobian.col(i).head<3>());
        }
    }
    
    void
    CrossProductExpression::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        Vector3I firstBounds = evaluator.evaluate(firstOperand(), parameterBounds);
        Vector3I secondBounds = evaluator.evaluate(secondOperand(), parameterBounds);
        MapXcI firstJacobian = evaluator.evaluateJacobian(firstOperand(), parameterBounds);
        MapXcI secondJacobian = evaluator.evaluateJacobian(secondOperand(), parameterBounds);
        for (int i = 0; i < results.cols(); ++i) {
            results.col(i) = firstJacobian.col(i).head<3>().cross(secondBounds) +
                firstBounds.cross(secondJacobian.col(i).head<3>());
        }
    }

    ExpressionImplementationPtr
    CrossProductExpression::derivativeImpl(int parameterIndex) const {
        return firstOperand()->derivative(parameterIndex)->cross(secondOperand())
            + firstOperand()->cross(secondOperand()->derivative(parameterIndex));
    }

    bool
    CrossProductExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other, false);
    }
    
    void
    CrossProductExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "CrossProductExpression" << std::endl;
        firstOperand()->debug(stream, indent + 1);
        secondOperand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    CrossProductExpression::withNewOperandsImpl(
        const ExpressionImplementationPtr& newFirstOperand,
        const ExpressionImplementationPtr& newSecondOperand
    ) const {
        return newFirstOperand->cross(newSecondOperand);
    }

    CrossProductExpression::CrossProductExpression(
        const ExpressionImplementationPtr& firstOperand,
        const ExpressionImplementationPtr& secondOperand
    ) : BinaryOperation(firstOperand, secondOperand) {

        assert(firstOperand->numDimensions() == 3 && secondOperand->numDimensions() == 3);
    }
}
