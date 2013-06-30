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

#include <OpenSolid/Core/FunctionImplementation/TempTransformationFunction.hpp>

namespace opensolid
{
    TempTransformationFunction::TempTransformationFunction(
        const MatrixXd& transformationMatrix,
        const FunctionImplementationPtr& operand
    ) : UnaryOperation(operand),
        _transformationMatrix(transformationMatrix) {

        assert(transformationMatrix.cols() == operand->numDimensions());
    }

    int
    TempTransformationFunction::numDimensionsImpl() const {
        return transformationMatrix().rows();
    }

    bool
    TempTransformationFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        const TempTransformationFunction* other =
            dynamic_cast<const TempTransformationFunction*>(function.implementation());
        if (other) {
            return this->transformationMatrix().rows() == other->transformationMatrix().rows() &&
                this->transformationMatrix().cols() == other->transformationMatrix().cols() &&
                (this->transformationMatrix() - other->transformationMatrix()).isZero() &&
                this->operand().isDuplicateOf(other->operand());
        } else {
            return false;
        }
    }

    FunctionImplementationPtr
    TempTransformationFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return new TempTransformationFunction(
            transformationMatrix(),
            operand()->deduplicated(deduplicationCache)
        );
    }
    
    void
    TempTransformationFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        results = transformationMatrix() *
            evaluator.evaluate(operand(), parameterValues);
    }
    
    void
    TempTransformationFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        results = transformationMatrix().cast<Interval>() *
            evaluator.evaluate(operand(), parameterBounds);
    }
    
    FunctionImplementationPtr
    TempTransformationFunction::derivativeImpl(int parameterIndex) const {
        return transformationMatrix() * operand()->derivative(parameterIndex);
    }
    
    FunctionImplementationPtr
    TempTransformationFunction::composeImpl(const FunctionImplementationPtr& innerFunction) const {
        return transformationMatrix() * operand()->compose(innerFunction);
    }

    FunctionImplementationPtr
    TempTransformationFunction::scaled(double value) const {
        return (value * transformationMatrix()) * operand();
    }

    FunctionImplementationPtr
    TempTransformationFunction::transformed(const MatrixXd& transformationMatrix) const {
        return (transformationMatrix * this->transformationMatrix()) * operand();
    }
    
    void
    TempTransformationFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "TempTransformationFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }
}
