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

#include <OpenSolid/Core/ParametricExpression/TranslationExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{   
    int
    TranslationExpression::numDimensionsImpl() const {
        return int(columnMatrixXd().rows());
    }
    
    void
    TranslationExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd operandValues = evaluator.evaluate(operand(), parameterValues);
        results = operandValues.colwise() + columnMatrixXd();
    }
    
    void
    TranslationExpression::evaluateImpl(
        const MapXcI& parameterValues,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterValues);
        results = operandBounds.colwise() + columnMatrixXd().cast<Interval>();
    }

    void
    TranslationExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluateJacobian(operand(), parameterValues);
    }
    
    void
    TranslationExpression::evaluateJacobianImpl(
        const MapXcI& parameterValues,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluateJacobian(operand(), parameterValues);
    }
    
    ExpressionImplementationPtr
    TranslationExpression::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex);
    }

    bool
    TranslationExpression::isDuplicateOfImpl(const ExpressionImplementationPtr& other) const {
        return duplicateOperands(other) &&
            (columnMatrixXd() - other->cast<TranslationExpression>()->columnMatrixXd()).isZero();
    }

    ExpressionImplementationPtr
    TranslationExpression::translationImpl(const ColumnMatrixXd& columnMatrixXd) const {
        return operand() + (this->columnMatrixXd() + columnMatrixXd);
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
        return newOperand + columnMatrixXd();
    }

    TranslationExpression::TranslationExpression(
        const ExpressionImplementationPtr& operand,
        const ColumnMatrixXd& columnMatrixXd
    ) : UnaryOperation(operand),
        _columnMatrixXd(columnMatrixXd) {

        assert(columnMatrixXd.size() == operand->numDimensions());
    }
}
