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

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    TempTranslationFunction::TempTranslationFunction(const Function& operand, const VectorXd& vector) :
        UnaryOperation(operand),
        _vector(vector) {

        assert(vector.size() == operand.numDimensions());
    }
    
    int TempTranslationFunction::numDimensions() const {
        return operand().numDimensions();
    }

    bool TempTranslationFunction::isDuplicateOf(const Function& function) const {
        const TempTranslationFunction* other =
            dynamic_cast<const TempTranslationFunction*>(function.implementation());
        if (other) {
            return (this->vector() - other->vector()).isZero() &&
                this->operand().isDuplicateOf(other->operand());
        } else {
            return false;
        }
    }

    Function TempTranslationFunction::deduplicated(Deduplicator& deduplicator) const {
        return new TempTranslationFunction(deduplicator(operand()), vector());
    }
    
    void TempTranslationFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        EvaluateCache<double>& cache
    ) const {
        MapXcd operandValues = cache.results(operand(), parameterValues);
        results = operandValues.colwise() + vector();
    }
    
    void TempTranslationFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        EvaluateCache<Interval>& cache
    ) const {
        MapXcI operandBounds = cache.results(operand(), parameterBounds);
        results = operandBounds.colwise() + vector().cast<Interval>();
    }
    
    Function TempTranslationFunction::derivative(int index) const {
        return operand().derivative(index);
    }
    
    Function TempTranslationFunction::compose(const Function& innerFunction) const {
        return operand().compose(innerFunction) + vector();
    }

    Function TempTranslationFunction::translated(const VectorXd& vector) const {
        return operand() + (this->vector() + vector);
    }
    
    void TempTranslationFunction::debug(std::ostream& stream, int indent) const {
        stream << "TempTranslationFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
