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

#include <OpenSolid/Core/FunctionImplementation/ScalarMultiplicationFunction.hpp>

#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{
    int
    ScalarMultiplicationFunction::numDimensionsImpl() const {
        return operand()->numDimensions();
    }
    
    void
    ScalarMultiplicationFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = scale() * evaluator.evaluate(operand(), parameterValues);
    }
    
    void
    ScalarMultiplicationFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = Interval(scale()) * evaluator.evaluate(operand(), parameterBounds);
    }

    void
    ScalarMultiplicationFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = scale() * evaluator.evaluateJacobian(operand(), parameterValues);
    }
    
    void
    ScalarMultiplicationFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = Interval(scale()) * evaluator.evaluateJacobian(operand(), parameterBounds);
    }
    
    FunctionImplementationPtr
    ScalarMultiplicationFunction::derivativeImpl(int parameterIndex) const {
        return scale() * operand()->derivative(parameterIndex);
    }

    bool
    ScalarMultiplicationFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other) &&
            this->scale() == other->cast<ScalarMultiplicationFunction>()->scale();
    }

    FunctionImplementationPtr
    ScalarMultiplicationFunction::scalarMultiplicationImpl(double scale) const {
        return (scale * this->scale()) * operand();
    }

    FunctionImplementationPtr
    ScalarMultiplicationFunction::matrixMultiplicationImpl(const MatrixXd& matrix) const {
        return (scale() * matrix) * operand();
    }
    
    void
    ScalarMultiplicationFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "ScalarMultiplicationFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    ScalarMultiplicationFunction::withNewOperandImpl(
        const FunctionImplementationPtr& newOperand
    ) const {
        return scale() * newOperand;
    }

    ScalarMultiplicationFunction::ScalarMultiplicationFunction(
        double scale,
        const FunctionImplementationPtr& operand
    ) : UnaryOperation(operand),
        _scale(scale) {
    }
}
