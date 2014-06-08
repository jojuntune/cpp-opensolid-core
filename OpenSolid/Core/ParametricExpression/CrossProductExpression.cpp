/************************************************************************************
*                                                                                   *
*  OpenSolid is a generic library for the representation and manipulation of        *
*  geometric objects such as points, curves, surfaces, and volumes.                 *
*                                                                                   *
*  Copyright (C) 2007-2014 by Ian Mackenzie                                         *
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
#include <OpenSolid/Core/Vector.hpp>

namespace opensolid
{   
    int
    CrossProductExpression::numDimensionsImpl() const {
        return 3;
    }
    
    void
    CrossProductExpression::evaluateImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        ConstMatrixViewXd firstValues = evaluator.evaluate(firstOperand(), parameterView);
        ConstMatrixViewXd secondValues = evaluator.evaluate(secondOperand(), parameterView);
        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            Vector3d firstVector(firstValues.column(columnIndex));
            Vector3d secondVector(secondValues.column(columnIndex));
            resultView.column(columnIndex) = firstVector.cross(secondVector).components();
        }
    }
    
    void
    CrossProductExpression::evaluateImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        ConstIntervalMatrixViewXd firstValues =
            evaluator.evaluate(firstOperand(), parameterView);
        ConstIntervalMatrixViewXd secondValues =
            evaluator.evaluate(secondOperand(), parameterView);
        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            IntervalVector3d firstVector(firstValues.column(columnIndex));
            IntervalVector3d secondVector(secondValues.column(columnIndex));
            resultView.column(columnIndex) = firstVector.cross(secondVector).components();
        }
    }

    void
    CrossProductExpression::evaluateJacobianImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        Vector3d firstVector(evaluator.evaluate(firstOperand(), parameterView));
        Vector3d secondVector(evaluator.evaluate(secondOperand(), parameterView));

        ConstMatrixViewXd firstJacobian =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        ConstMatrixViewXd secondJacobian =
            evaluator.evaluateJacobian(secondOperand(), parameterView);

        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            Vector3d firstPartial(firstJacobian.column(columnIndex));
            Vector3d secondPartial(secondJacobian.column(columnIndex));
            resultView.column(columnIndex) =
                (firstPartial.cross(secondVector) + firstVector.cross(secondPartial)).components();
        }
    }
    
    void
    CrossProductExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {

        IntervalVector3d firstVector(evaluator.evaluate(firstOperand(), parameterView));
        IntervalVector3d secondVector(evaluator.evaluate(secondOperand(), parameterView));

        ConstIntervalMatrixViewXd firstJacobian =
            evaluator.evaluateJacobian(firstOperand(), parameterView);
        ConstIntervalMatrixViewXd secondJacobian =
            evaluator.evaluateJacobian(secondOperand(), parameterView);

        for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
            IntervalVector3d firstPartial(firstJacobian.column(columnIndex));
            IntervalVector3d secondPartial(secondJacobian.column(columnIndex));
            resultView.column(columnIndex) =
                (firstPartial.cross(secondVector) + firstVector.cross(secondPartial)).components();
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
