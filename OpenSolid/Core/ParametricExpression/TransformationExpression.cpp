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

#include <OpenSolid/Core/ParametricExpression/TransformationExpression.hpp>

#include <OpenSolid/Core/ParametricExpression/ExpressionImplementation.hpp>

namespace opensolid
{
    int
    TransformationExpression::numDimensionsImpl() const {
        return int(matrixXd().rows());
    }
    
    void
    TransformationExpression::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = matrixXd() * evaluator.evaluate(operand(), parameterValues);
    }
    
    void
    TransformationExpression::evaluateImpl(
        const MapXcI& parameterValues,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = matrixXd().cast<Interval>() * evaluator.evaluate(operand(), parameterValues);
    }

    void
    TransformationExpression::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = matrixXd() * evaluator.evaluateJacobian(operand(), parameterValues);
    }
    
    void
    TransformationExpression::evaluateJacobianImpl(
        const MapXcI& parameterValues,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = matrixXd().cast<Interval>() *
            evaluator.evaluateJacobian(operand(), parameterValues);
    }
    
    ExpressionImplementationPtr
    TransformationExpression::derivativeImpl(int parameterIndex) const {
        return matrixXd() * operand()->derivative(parameterIndex);
    }

    bool
    TransformationExpression::isDuplicateOfImpl(
        const ExpressionImplementationPtr& other
    ) const {
        MatrixXd otherMatrixXd = other->cast<TransformationExpression>()->matrixXd();
        return duplicateOperands(other) && (matrixXd() - otherMatrixXd).isZero();
    }

    ExpressionImplementationPtr
    TransformationExpression::scalingImpl(double scale) const {
        return (scale * matrixXd()) * operand();
    }

    ExpressionImplementationPtr
    TransformationExpression::transformationImpl(const MatrixXd& matrixXd) const {
        return (matrixXd * this->matrixXd()) * operand();
    }
    
    void
    TransformationExpression::debugImpl(std::ostream& stream, int indent) const {
        stream << "TransformationExpression" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    ExpressionImplementationPtr
    TransformationExpression::withNewOperandImpl(
        const ExpressionImplementationPtr& newOperand
    ) const {
        return matrixXd() * newOperand;
    }

    TransformationExpression::TransformationExpression(
        const MatrixXd& matrixXd,
        const ExpressionImplementationPtr& operand
    ) : UnaryOperation(operand),
        _matrixXd(matrixXd) {

        assert(matrixXd.cols() == operand->numDimensions());
    }
}
