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

#include <OpenSolid/Core/ParametricExpression/SineExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    SineExpression::numDimensionsImpl() const {
        return 1;
    }

    bool
    SineExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    void
    SineExpression::evaluateImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        evaluator.evaluate(operand(), parameterView).map(
            [] (double value) {
                return sin(value);
            },
            resultView
        );
    }
    
    void
    SineExpression::evaluateImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        evaluator.evaluate(operand(), parameterView).map(
            [] (Interval value) {
                return sin(value);
            },
            resultView
        );
    }

    void
    SineExpression::evaluateJacobianImpl(
        const ConstMatrixViewXxX& parameterView,
        MatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView *= cos(evaluator.evaluate(operand(), parameterView).value());
    }
    
    void
    SineExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXxX& parameterView,
        IntervalMatrixViewXxX& resultView,
        Evaluator& evaluator
    ) const {
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView *= cos(evaluator.evaluate(operand(), parameterView).value());
    }

    ExpressionImplementationPtr
    SineExpression::derivativeImpl(int parameterIndex) const {
        return cos(operand()) * operand()->derivative(parameterIndex);
    }
    
    void
    SineExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "SineExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    SineExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
        return sin(newOperand);
    }

    SineExpression::SineExpression(const ExpressionImplementationPtr& operand) :
        UnaryOperation(operand) {
        
        assert(operand->numDimensions() == 1);
    }
}
