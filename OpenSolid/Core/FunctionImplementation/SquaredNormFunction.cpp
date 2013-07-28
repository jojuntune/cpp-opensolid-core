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

#include <OpenSolid/Core/FunctionImplementation/SquaredNormFunction.hpp>

#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{   
    int
    SquaredNormFunction::numDimensionsImpl() const {
        return 1;
    }
    
    void
    SquaredNormFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterValues).colwise().squaredNorm();
    }
    
    void
    SquaredNormFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterBounds).colwise().squaredNorm();
    }

    void
    SquaredNormFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd operandValue = evaluator.evaluate(operand(), parameterValues);
        MapXcd operandJacobian = evaluator.evaluateJacobian(operand(), parameterValues);
        results = 2.0 * operandValue.transpose() * operandJacobian;
    }
    
    void
    SquaredNormFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterBounds);
        MapXcI operandJacobian = evaluator.evaluateJacobian(operand(), parameterBounds);
        results = Interval(2.0) * operandBounds.transpose() * operandJacobian;
    }

    FunctionImplementationPtr
    SquaredNormFunction::derivativeImpl(int parameterIndex) const {
        return 2.0 * operand()->dot(operand()->derivative(parameterIndex));
    }

    bool
    SquaredNormFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    void
    SquaredNormFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "SquaredNormFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    SquaredNormFunction::withNewOperandImpl(const FunctionImplementationPtr& newOperand) const {
        return newOperand->squaredNorm();
    }

    SquaredNormFunction::SquaredNormFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {
    }
}
