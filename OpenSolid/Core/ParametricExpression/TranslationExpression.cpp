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

#include <OpenSolid/Core/ParametricExpression/TranslationExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    namespace detail
    {
        int
        TranslationExpression::numDimensionsImpl() const {
            return int(columnMatrix().numRows());
        }
        
        void
        TranslationExpression::evaluateImpl(
            const ConstMatrixViewXd& parameterView,
            MatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            resultView = evaluator.evaluate(operand(), parameterView);
            for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
                resultView.column(columnIndex) += columnMatrix();
            }
        }
        
        void
        TranslationExpression::evaluateImpl(
            const ConstIntervalMatrixViewXd& parameterView,
            IntervalMatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            resultView = evaluator.evaluate(operand(), parameterView);
            for (int columnIndex = 0; columnIndex < resultView.numColumns(); ++columnIndex) {
                resultView.column(columnIndex) += columnMatrix();
            }
        }

        void
        TranslationExpression::evaluateJacobianImpl(
            const ConstMatrixViewXd& parameterView,
            MatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            resultView = evaluator.evaluateJacobian(operand(), parameterView);
        }
        
        void
        TranslationExpression::evaluateJacobianImpl(
            const ConstIntervalMatrixViewXd& parameterView,
            IntervalMatrixViewXd& resultView,
            Evaluator& evaluator
        ) const {
            resultView = evaluator.evaluateJacobian(operand(), parameterView);
        }
        
        ExpressionImplementationPtr
        TranslationExpression::derivativeImpl(int parameterIndex) const {
            return operand()->derivative(parameterIndex);
        }

        bool
        TranslationExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
            return (
                duplicateOperands(other) &&
                (columnMatrix() - other->cast<TranslationExpression>()->columnMatrix()).isZero()
            );
        }

        ExpressionImplementationPtr
        TranslationExpression::translationImpl(const ColumnMatrixXd& columnMatrix) const {
            return operand() + (this->columnMatrix() + columnMatrix);
        }
        
        void
        TranslationExpression::debugImpl(std::ostream& stream, int indent) const {
            stream << "TranslationExpression" << std::endl;
            operand()->debug(stream, indent + 1);
        }

        ExpressionImplementationPtr
        TranslationExpression::withNewOperandImpl(
            const ExpressionImplementationPtr& newOperand
        ) const {
            return newOperand + columnMatrix();
        }

        TranslationExpression::TranslationExpression(
            const ExpressionImplementationPtr& operand,
            const ColumnMatrixXd& columnMatrix
        ) : UnaryOperation(operand),
            _columnMatrix(columnMatrix) {

            assert(columnMatrix.numComponents() == operand->numDimensions());
        }
    }
}
