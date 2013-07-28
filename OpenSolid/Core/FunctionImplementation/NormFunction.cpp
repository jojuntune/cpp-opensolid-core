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

#include <OpenSolid/Core/FunctionImplementation/NormFunction.hpp>

#include <OpenSolid/Core/Error.hpp>
#include <OpenSolid/Core/FunctionImplementation.hpp>

namespace opensolid
{   
    int
    NormFunction::numDimensionsImpl() const {
        return 1;
    }

    bool
    NormFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other);
    }
    
    void
    NormFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterValues).colwise().norm();
    }
    
    void 
    NormFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = evaluator.evaluate(operand(), parameterBounds).colwise().norm();
    }

    void
    NormFunction::evaluateJacobianImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd operandValue = evaluator.evaluate(operand(), parameterValues);
        if (operandValue.isZero()) {
            throw PlaceholderError();
        }
        VectorXd operandNormalized = operandValue.normalized();
        MapXcd operandJacobian = evaluator.evaluateJacobian(operand(), parameterValues);
        results = operandNormalized.transpose() * operandJacobian;
    }
    
    void
    NormFunction::evaluateJacobianImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterBounds);
        if (operandBounds.isZero()) {
            throw PlaceholderError();
        }
        VectorXI operandNormalized = operandBounds.normalized();
        MapXcI operandJacobian = evaluator.evaluateJacobian(operand(), parameterBounds);
        results = operandNormalized.transpose() * operandJacobian;
    }

    FunctionImplementationPtr
    NormFunction::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex)->dot(operand()->normalized());
    }

    FunctionImplementationPtr
    NormFunction::normImpl() const {
        return this;
    }
    
    void
    NormFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "NormFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    NormFunction::withNewOperandImpl(const FunctionImplementationPtr& newOperand) const {
        return newOperand->norm();
    }

    NormFunction::NormFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {
    }
}
