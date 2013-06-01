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

#include <OpenSolid/Core/Function.hpp>

namespace opensolid
{
    TempScalingFunction::TempScalingFunction(double scale, const Function& operand) :
        UnaryOperation(operand),
        _scale(scale) {
    }

    int TempScalingFunction::numDimensions() const {
        return operand().numDimensions();
    }

    bool TempScalingFunction::isDuplicateOf(const Function& function) const {
        const TempScalingFunction* other =
            dynamic_cast<const TempScalingFunction*>(function.implementation());
        if (other) {
            return this->scale() == other->scale() && this->operand().isDuplicateOf(other->operand());
        } else {
            return false;
        }
    }

    Function TempScalingFunction::deduplicated(Deduplicator& deduplicator) const {
        return new TempScalingFunction(scale(), operand().deduplicated(others));
    }
    
    void TempScalingFunction::evaluate(
        const MapXcd& parameterValues,
        MapXd& results,
        EvaluateCache<double>& cache
    ) const {
        results = scale() * cache.results(operand(), parameterValues);
    }
    
    void TempScalingFunction::evaluate(
        const MapXcI& parameterBounds,
        MapXI& results,
        EvaluateCache<Interval>& cache
    ) const {
        results = Interval(scale()) * cache.results(operand(), parameterBounds);
    }
    
    Function TempScalingFunction::derivative(int index) const {
        return scale() * operand().derivative(index);
    }
    
    Function TempScalingFunction::compose(const Function& innerFunction) const {
        return scale() * operand().compose(innerFunction);
    }

    Function TempScalingFunction::scaled(double scale) const {
        return (scale * this->scale()) * operand();
    }

    Function TempScalingFunction::transformed(const MatrixXd& transformationMatrix) const {
        return (transformationMatrix * scale()) * operand();
    }
    
    void TempScalingFunction::debug(std::ostream& stream, int indent) const {
        stream << "TempScalingFunction" << std::endl;
        operand().debug(stream, indent + 1);
    }
}
