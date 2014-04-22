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

#include <OpenSolid/Core/ParametricExpression/TangentExpression.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    TangentExpression::numDimensionsImpl() const {
        return 1;
    }
    
    void
    TangentExpression::evaluateImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        evaluator.evaluate(operand(), parameterView).map(
            [] (double value) {
                return tan(value);
            },
            resultView
        );
    }
    
    void
    TangentExpression::evaluateImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        evaluator.evaluate(operand(), parameterView).map(
            [] (Interval value) {
                return tan(value);
            },
            resultView
        );
    }

    void
    TangentExpression::evaluateJacobianImpl(
        const ConstMatrixViewXd& parameterView,
        MatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        double operandValue = evaluator.evaluate(operand(), parameterView).value();
        double cosine = cos(operandValue);
        if (cosine == Zero()) {
            throw Error(new PlaceholderError());
        }
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView /= cosine * cosine;
    }
    
    void
    TangentExpression::evaluateJacobianImpl(
        const ConstIntervalMatrixViewXd& parameterView,
        IntervalMatrixViewXd& resultView,
        Evaluator& evaluator
    ) const {
        Interval operandValue = evaluator.evaluate(operand(), parameterView).value();
        Interval cosine = cos(operandValue);
        if (cosine == Zero()) {
            throw Error(new PlaceholderError());
        }
        resultView = evaluator.evaluateJacobian(operand(), parameterView);
        resultView /= cosine.squared();
    }

    ExpressionImplementationPtr
    TangentExpression::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex) / cos(operand())->squaredNorm();
    }

    bool
    TangentExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    void
    TangentExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "TangentExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    TangentExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
        return tan(newOperand);
    }

    TangentExpression::TangentExpression(const ExpressionImplementationPtr& operand) :
        UnaryOperation(operand) {
        
        assert(operand->numDimensions() == 1);
    }
}
