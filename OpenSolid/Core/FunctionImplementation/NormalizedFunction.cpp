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

#include <OpenSolid/Core/FunctionImplementation/NormalizedFunction.hpp>

namespace opensolid
{
    NormalizedFunction::NormalizedFunction(const FunctionImplementationPtr& operand) :
        UnaryOperation(operand) {
    }
    
    int
    NormalizedFunction::numDimensionsImpl() const {
        return operand()->numDimensions();
    }

    bool
    NormalizedFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return UnaryOperation::IsDuplicate(this, function);
    }

    FunctionImplementationPtr
    NormalizedFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return new NormalizedFunction(operand()->deduplicated(deduplicationCache));
    }

    void
    NormalizedFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd operandValues = evaluator.evaluate(operand(), parameterValues);
        VectorXd squaredNorms = operandValues.colwise().squaredNorm();
        results = operandValues * squaredNorms.cwiseSqrt().cwiseInverse().asDiagonal();
    }

    void
    NormalizedFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterBounds);
        VectorXI squaredNorms = operandBounds.colwise().squaredNorm();
        results = operandBounds * squaredNorms.cwiseSqrt().cwiseInverse().asDiagonal();
    }

    FunctionImplementationPtr
    NormalizedFunction::derivativeImpl(int parameterIndex) const {
        FunctionImplementationPtr operandDerivative = operand()->derivative(parameterIndex);
        FunctionImplementationPtr operandNormalized = operand().normalized();
        return
            (operandDerivative - operandDerivative.dot(operandNormalized) * operandNormalized) /
            operand().norm();
    }
    
    FunctionImplementationPtr
    NormalizedFunction::norm() const {
        return FunctionImplementationPtr::Constant(1.0, numParameters());
    }
    
    FunctionImplementationPtr
    NormalizedFunction::normalized() const {
        return this;
    }
    
    FunctionImplementationPtr
    NormalizedFunction::squaredNorm() const {
        return FunctionImplementationPtr::Constant(1.0, numParameters());
    }
    
    void
    NormalizedFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "NormalizedFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }
}
