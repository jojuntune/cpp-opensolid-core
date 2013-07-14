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
*************************************************************************************/

#include <OpenSolid/Core/FunctionImplementation/MatrixMultiplicationFunction.hpp>

namespace opensolid
{
    int
    MatrixMultiplicationFunction::numDimensionsImpl() const {
        return matrix().rows();
    }
    
    void
    MatrixMultiplicationFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = matrix() * evaluator.evaluate(operand(), parameterValues);
    }
    
    void
    MatrixMultiplicationFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = matrix().cast<Interval>() * evaluator.evaluate(operand(), parameterBounds);
    }

    void
    MatrixMultiplicationFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = matrix() * evaluator.evaluateJacobian(operand(), parameterValues);
    }
    
    void
    MatrixMultiplicationFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = matrix().cast<Interval>() *
            evaluator.evaluateJacobian(operand(), parameterBounds);
    }
    
    FunctionImplementationPtr
    MatrixMultiplicationFunction::derivativeImpl(int parameterIndex) const {
        return matrix() * operand()->derivative(parameterIndex);
    }

    bool
    MatrixMultiplicationFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        MatrixXd otherMatrix = other->cast<MatrixMultiplicationFunction>()->matrix();
        return duplicateOperands(other) && (matrix() - otherMatrix).isZero();
    }

    FunctionImplementationPtr
    MatrixMultiplicationFunction::scalarMultiplicationImpl(double value) const {
        return (value * matrix()) * operand();
    }

    FunctionImplementationPtr
    MatrixMultiplicationFunction::matrixMultiplicationImpl(const MatrixXd& matrix) const {
        return (matrix * this->matrix()) * operand();
    }
    
    void
    MatrixMultiplicationFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "MatrixMultiplicationFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    MatrixMultiplicationFunction::withNewOperandImpl(
        const FunctionImplementationPtr& newOperand
    ) const {
        return matrix() * newOperand;
    }

    MatrixMultiplicationFunction::MatrixMultiplicationFunction(
        const MatrixXd& matrix,
        const FunctionImplementationPtr& operand
    ) : UnaryOperation(operand),
        _matrix(matrix) {

        assert(matrix.cols() == operand->numDimensions());
    }
}
