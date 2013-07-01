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

#include <OpenSolid/Core/FunctionImplementation/TempScalingFunction.hpp>

namespace opensolid
{
    int
    TempScalingFunction::numDimensionsImpl() const {
        return operand()->numDimensions();
    }
    
    void
    TempScalingFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = scale() * evaluator.evaluate(operand(), parameterValues);
    }
    
    void
    TempScalingFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = Interval(scale()) * evaluator.evaluate(operand(), parameterBounds);
    }
    
    FunctionImplementationPtr
    TempScalingFunction::derivativeImpl(int parameterIndex) const {
        return scale() * operand()->derivative(parameterIndex);
    }

    bool
    TempScalingFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        return duplicateOperands(other) &&
            this->scale() == other->cast<TempScalingFunction>()->scale();
    }

    FunctionImplementationPtr
    TempScalingFunction::scaledImpl(double scale) const {
        return (scale * this->scale()) * operand();
    }

    FunctionImplementationPtr
    TempScalingFunction::transformedImpl(const MatrixXd& transformationMatrix) const {
        return (transformationMatrix * scale()) * operand();
    }
    
    void
    TempScalingFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "TempScalingFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }

    FunctionImplementationPtr
    TempScalingFunction::withNewOperandImpl(const FunctionImplementationPtr& newOperand) const {
        return scale() * newOperand;
    }

    TempScalingFunction::TempScalingFunction(
        double scale,
        const FunctionImplementationPtr& operand
    ) : UnaryOperation(operand),
        _scale(scale) {
    }
}
