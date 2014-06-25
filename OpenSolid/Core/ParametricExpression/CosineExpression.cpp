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

#include <OpenSolid/Core/ParametricExpression/CosineExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    namespace detail
    {
        int
        CosineExpression::numDimensionsImpl() const {
            return 1;
        }
        
        void
        CosineExpression::evaluateImpl(
            const ConstMatrixViewXd& parameterView,
            MatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            resultView.setMap(
                evaluator.evaluate(operand(), parameterView),
                [] (double value) {
                    return opensolid::cos(value);
                }            
            );
        }
        
        void
        CosineExpression::evaluateImpl(
            const ConstIntervalMatrixViewXd& parameterView,
            IntervalMatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            resultView.setMap(
                evaluator.evaluate(operand(), parameterView),
                [] (Interval value) {
                    return cos(value);
                }            
            );
        }

        void
        CosineExpression::evaluateJacobianImpl(
            const ConstMatrixViewXd& parameterView,
            MatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            resultView = evaluator.evaluateJacobian(operand(), parameterView);
            resultView *= -opensolid::sin(evaluator.evaluate(operand(), parameterView).value());
        }
        
        void
        CosineExpression::evaluateJacobianImpl(
            const ConstIntervalMatrixViewXd& parameterView,
            IntervalMatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            resultView = evaluator.evaluateJacobian(operand(), parameterView);
            resultView *= -sin(evaluator.evaluate(operand(), parameterView).value());
        }

        ExpressionImplementationPtr
        CosineExpression::derivativeImpl(int parameterIndex) const {
            return -sin(operand()) * operand()->derivative(parameterIndex);
        }

        bool
        CosineExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return duplicateOperands(other);
        }
        
        void
        CosineExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "CosineExpression" << std::endl;
            operand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        CosineExpression::withNewOperandImpl(const ExpressionImplementationPtr& newOperand) const {
            return cos(newOperand);
        }

        CosineExpression::CosineExpression(const ExpressionImplementationPtr& operand) :
            UnaryOperation(operand) {

            assert(operand->numDimensions() == 1);
        }
    }
}
