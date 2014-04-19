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
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcd firstValues = evaluator.evaluate(firstOperand(), parameterView);
        MapXcd secondValues = evaluator.evaluate(secondOperand(), parameterView);
        for (int i = 0; i < resultView.cols(); ++i) {
            resultView.col(i) = firstValues.col(i).head<3>().cross(secondValues.col(i).head<3>());
        }
    }
    
    void
    CrossProductExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        MapXcI firstBounds = evaluator.evaluate(firstOperand(), parameterView);
        MapXcI secondBounds = evaluator.evaluate(secondOperand(), parameterView);
        for (int i = 0; i < resultView.cols(); ++i) {
            resultView.col(i) = firstBounds.col(i).head<3>().cross(secondBounds.col(i).head<3>());
        }
    }

    void
    CrossProductExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        Eigen::Matrix<double, 3, 1> firstValue =
            evaluator.evaluate(firstOperand(), parameterView);
        Eigen::Matrix<double, 3, 1> secondValue =
            evaluator.evaluate(secondOperand(), parameterView);
        MapXcd firstJacobian = evaluator.evaluateJacobian(firstOperand(), parameterView);
        MapXcd secondJacobian = evaluator.evaluateJacobian(secondOperand(), parameterView);
        for (int i = 0; i < resultView.cols(); ++i) {
            resultView.col(i) = firstJacobian.col(i).head<3>().cross(secondValue) +
                firstValue.cross(secondJacobian.col(i).head<3>());
        }
    }
    
    void
    CrossProductExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        Eigen::Matrix<Interval, 3, 1> firstBounds =
            evaluator.evaluate(firstOperand(), parameterView);
        Eigen::Matrix<Interval, 3, 1> secondBounds =
            evaluator.evaluate(secondOperand(), parameterView);
        MapXcI firstJacobian = evaluator.evaluateJacobian(firstOperand(), parameterView);
        MapXcI secondJacobian = evaluator.evaluateJacobian(secondOperand(), parameterView);
        for (int i = 0; i < resultView.cols(); ++i) {
            resultView.col(i) = firstJacobian.col(i).head<3>().cross(secondBounds) +
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
