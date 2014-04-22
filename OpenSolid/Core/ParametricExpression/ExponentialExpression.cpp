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

#include <OpenSolid/Core/ParametricExpression/ExponentialExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{       
    int 
    ExponentialExpression::numDimensionsImpl() const {
        return 1;
    }

    bool
    ExponentialExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
        
    void
    ExponentialExpression::evaluateImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        evaluator.evaluate(operand(), parameterView).map(
            [] (double value) {
                return exp(value);
            },
            resultView
        );
    }

    void
    ExponentialExpression::evaluateImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        evaluator.evaluate(operand(), parameterView).map(
            [] (Interval value) {
                return exp(value);
            },
            resultView
        );
    }

    void
    ExponentialExpression::evaluateJacobianImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView *= exp(evaluator.evaluate(operand(), parameterView).value());
    }
    
    void
    ExponentialExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView *= exp(evaluator.evaluate(operand(), parameterView).value());
    }

    ExpressionImplementationPtr
    ExponentialExpression::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex) * self();
    }
        
    void
    ExponentialExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "ExponentialExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    ExponentialExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
        return exp(newOperand);
    }

    ExponentialExpression::ExponentialExpression(const ExpressionImplementationPtr& operand) :
        UnaryOperation(operand) {
        
        assert(operand->numDimensions() == 1);
    }
}
