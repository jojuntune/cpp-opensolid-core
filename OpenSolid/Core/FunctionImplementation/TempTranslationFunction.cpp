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

#include <OpenSolid/Core/FunctionImplementation/TempTranslationFunction.hpp>

namespace opensolid
{
    TempTranslationFunction::TempTranslationFunction(
        const FunctionImplementationPtr& operand,
        const VectorXd& vector
    ) : UnaryOperation(operand),
        _vector(vector) {

        assert(vector.size() == operand->numDimensions());
    }
    
    int
    TempTranslationFunction::numDimensionsImpl() const {
        return operand()->numDimensions();
    }

    bool
    TempTranslationFunction::isDuplicateOfImpl(const FunctionImplementationPtr& other) const {
        const TempTranslationFunction* other =
            dynamic_cast<const TempTranslationFunction*>(function.implementation());
        if (other) {
            return (this->vector() - other->vector()).isZero() &&
                this->operand().isDuplicateOf(other->operand());
        } else {
            return false;
        }
    }

    FunctionImplementationPtr
    TempTranslationFunction::deduplicatedImpl(DeduplicationCache& deduplicationCache) const {
        return new TempTranslationFunction(deduplicationCache(operand()), vector());
    }
    
    void
    TempTranslationFunction::evaluateImpl(
        const MapXcd& parameterValues,
        MapXd& results,
        Evaluator& evaluator
    ) const {
        MapXcd operandValues = evaluator.evaluate(operand(), parameterValues);
        results = operandValues.colwise() + vector();
    }
    
    void
    TempTranslationFunction::evaluateImpl(
        const MapXcI& parameterBounds,
        MapXI& results,
        Evaluator& evaluator
    ) const {
        MapXcI operandBounds = evaluator.evaluate(operand(), parameterBounds);
        results = operandBounds.colwise() + vector().cast<Interval>();
    }
    
    FunctionImplementationPtr
    TempTranslationFunction::derivativeImpl(int parameterIndex) const {
        return operand()->derivative(parameterIndex);
    }
    
    FunctionImplementationPtr
    TempTranslationFunction::composeImpl(const FunctionImplementationPtr& innerFunction) const {
        return operand()->compose(innerFunction) + vector();
    }

    FunctionImplementationPtr
    TempTranslationFunction::translated(const VectorXd& vector) const {
        return operand() + (this->vector() + vector);
    }
    
    void
    TempTranslationFunction::debugImpl(std::ostream& stream, int indent) const {
        stream << "TempTranslationFunction" << std::endl;
        operand()->debug(stream, indent + 1);
    }
}
